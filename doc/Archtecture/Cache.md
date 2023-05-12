### Cache基础

------

#### 一：基础内容

首先需要解决这样几个问题：

（1）存储中的地址如何分配到Cache中（即映射的关系）

（2）如何索引Cache块中的内容（通过索引加上TAG）

（3）如何判断当前Cache块中的内容有效（添加有效位）

##### 直接映射

![avatar](https://github.com/xie-1399/RISCVZone/blob/main/doc/pic/Cache/Cache1.png)

上面是存储地址和Cache中的映射关系，直接映射会比较简单

![avatar](https://github.com/xie-1399/RISCVZone/blob/main/doc/pic/Cache/Cache2.png)

而如何索引Cache块中的内容，上图也有表示，通过valid表示有效位，TAG使用高位进行表示，而索引的时候直接通过低数据位去索引

块大小和失效率之前，增加块容量可以通过挖掘局部性，但是随着块容量的增加，更严重的问题会是失效所带来的损失。当出现失效的情况时，需要控制器的协调，对于顺序的流水线来说如果出现缺失的情况时会停止流水线，但并不适用于乱序发射的情况。（**但是需要注意这个时候PC的值应该取多少？**，可能每一个阶段都有对应的PC）

##### Cache处理写操作

写直通：保持Cache和主存具有一致性，总是将数据写回内存和Cache中（每次写操作都会引起写主存的操作）

写返回：发生写操作的时候，只会被写入到Cache中，被替换出来的时候才会被写到下一级（带上的标记位也被称为脏状态）

当然由于Cache块的容量大多数情况下并不是只有1个，比如如果一个块具有四个字节的时候，可能对应如下图：（注意这里的字节偏移量是可以定位到字节的）

![avatar](https://github.com/xie-1399/RISCVZone/blob/main/doc/pic/Cache/Cache3.png)

常见的两种搭配是：

```
写直通 + 写不分配
写回法 + 写分配
```

如果采用的是写直通的方法：

![avatar](https://github.com/xie-1399/RISCVZone/blob/main/doc/pic/Cache/Cache4.png)

如果采用的是写回的方法：

![avatar](https://github.com/xie-1399/RISCVZone/blob/main/doc/pic/Cache/Cache5.png)

#### 二：性能改进

性能改进的方案主要通过两种方式进行改善：

（1）减少两个不同的内存块争夺同一个缓存位置的发生概率（映射方式）

（2）添加额外的一个存储层次来减少失效的代价（多级缓存）

Cache的平均存储访问时间 = 命中时间 + 失效率 * 失效代价

全相联映射也就是说数据块是可以存放在Cache中的任意表项，而介于全相联和直接映射之间的就是组相联

##### 组相联映射

注意组相联的每一个Cache块都有一个TAG位

**基本思路：Cache分成若干个组，每个组中有n个数据块，如果一个数据块索引到了对应的组，那么这个数据块是可以存放在组中所有数据块中的！（n路组相联）**

![avatar](https://github.com/xie-1399/RISCVZone/blob/main/doc/pic/Cache/Cache6.png)

提高相连度可以降低失效率但是会增加命中时间

![avatar](https://github.com/xie-1399/RISCVZone/blob/main/doc/pic/Cache/Cache7.png)

Cacxhe替换的策略最常用的可能就是LRU，但是可能也可以尝试使用随即替换的方法，也许也能得到比较好的效果

##### （1）写缓存

其实就是将数据写到下级存储器的时间进行隐藏

```
对于写回法：当一个脏状态的CacheLine被替换的时候，先放到写缓存里面去，然后就可以正常到下级存储器中读数据

对于写直通：每次数据写到DCache的同时也不会写到下级的存储器中
```

##### （2）对DCache的写操作进行流水线处理

![avatar](https://github.com/xie-1399/RISCVZone/blob/main/doc/pic/Cache/Cache8.png)

但是需要注意这里可能会出现冲突问题需要去解决

##### （3）多级结构

![avatar](https://github.com/xie-1399/RISCVZone/blob/main/doc/pic/Cache/Cache9.png)

有Inclusive和Exclusive两种形式（现代大多数处理器都是Inclusive的）

##### （4）Victim Cache

其实就是可以保存最近被踢出Cache的数据，通常采用全相连的方式（比如存储4~16个数据）

![avatar](https://github.com/xie-1399/RISCVZone/blob/main/doc/pic/Cache/Cache10.png)

这样处理器如果在Cache中没有找到想要的数据，但是在VC中找到了，这样也相当于命中了（和Cache交换数据）

或者使用filter Cache提高利用率（可以当成是在前面而不是在后面）

##### （5）预取

##### 替换策略

如果一个CacheSet里面的CacheLine满了，那么就需要进行替换，一般来说可以使用LRU或者随即替换

（LRU可以考虑使用一个计数器来进行随机选择）

#### 三：虚拟存储

（1）允许多个程序之间高效安全的共享内存

（2）允许单用户程序使用超过内存容量的内存

一个进行页表查找的例子：

![avatar](https://github.com/xie-1399/RISCVZone/blob/main/doc/pic/Cache/Cache11.png)

可以简单的理解为一个虚拟页会被映射到一个物理页，同时需要注意每个进程都有各自的页表，通过页表寄存器可以找到对应进程的页表所在的位置，注意物理页的地址可能在物理存储器或者磁盘中

![avatar](https://github.com/xie-1399/RISCVZone/blob/main/doc/pic/Cache/Cache12.png)

为了实现大虚拟地址空间，实际上的页表是分级的结构，并且页表的写必须是使用写回的策略（不然时间会非常顶长）

##### TLB（块表）

其实就是虚拟地址的Cache，由于页表是存在内存里的，为了获得物理地址需要访问页表，为了减少这次访存请求使用了快表的结构，在TLB中多采用全相连的结构

![avatar](https://github.com/xie-1399/RISCVZone/blob/main/doc/pic/Cache/Cache13.png)

从上面的图可以很清晰的看出：

![avatar](https://github.com/xie-1399/RISCVZone/blob/main/doc/pic/Cache/Cache14.png)

#### 四：超标量中的Cache结构

在超标量处理器中对于ICache而言，需要能够每周期读取多条指令

##### 1：流水访问Cache结构

可以使用并行和串行两种方式访问Cache

![avatar](https://github.com/xie-1399/RISCVZone/blob/main/doc/pic/Cache/Cache15.png)

并行访问可同时访问TAG SRAM和Data SRAM

![avatar](https://github.com/xie-1399/RISCVZone/blob/main/doc/pic/Cache/Cache16.png)

串行访问可以用于提高时钟频率，但是增加了Load的开销

##### 2：多端口Cache

待补充
