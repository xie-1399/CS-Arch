### 虚拟地址

------

##### 虚拟地址的作用：

```
程序、数据和堆栈的总大小是可以超过实际的物理内存的大小的，操作系统可以将程序中的一部分放在物理内存之中，而将其他的内容放到硬盘上，并在需要的时候在内存和硬盘之间交换程序片段
```

共享：比如共享printf函数

保护：即使两个程序使用同一个虚拟地址，他们也会对应到不同的物理地址

##### 优点

（1）让每个程序都有独立的地址空间，每个程序都认为自己拥有整个4GB的虚拟空间

（2）使用这种地址映射的机制，可以减少物理内存中的碎片，最大限度的利用容量有限的物理内存

（3）利用虚拟存储器，可以管理每一个页的访问权限

#### 地址转换

基于分页的虚拟存储器，虚拟地址的划分通常以页为单位，而在物理内存中就被称作frame，在页中有页偏移量和VPN（表示哪一个页），在Frame中也有偏移量和PFN，所以其实转化就是从VPN到PFN之间的转化（页是进行地址转换的最小单位）

https://github.com/xie-1399/RISCVZone/tree/main/doc/pic/VirtrualAddress/VirtrualAddress1.png

如果发现在物理内存中找不到这个页，那么MMU就会产生一个Page Fault的异常发给处理器，这时处理器就需要转到异常处理程序（其实就是操作系统的代码），这时也可能会出现脏数据的情况

https://github.com/xie-1399/RISCVZone/tree/main/doc/pic/VirtrualAddress/VirtrualAddress2.png

##### 单级页表

每个程序都有自己的页表，在处理器中包含一个页表寄存器，页表中存储的其实就是VPN到PFN的映射关系，注意页表的表项是有有效位的，如果有效位是0，代表这个虚拟地址对应的4KB（页表大小）还没有被映射到物理内存中，此时就需要操作系统从更下一级去搬移数据

https://github.com/xie-1399/RISCVZone/tree/main/doc/pic/VirtrualAddress/VirtrualAddress3.png

一个程序对应的页表，连同PC和通用寄存器一起，组成了程序的状态（操作系统通过将一个进程的状态加载到处理器上，就可以使这个进程进入活跃的状态），而进程进行状态保存的时候也不用保存整个的页表，只需要保存页表寄存器

不同的进程如果出现相同的虚拟地址，就需要操作系统将这些不同的进程分配到不同的地方

https://github.com/xie-1399/RISCVZone/tree/main/doc/pic/VirtrualAddress/VirtrualAddress4.png

##### 多级页表

将线性页表划分成若干个更小的页表，一级页表中记录了每个子页表在内存中的位置

https://github.com/xie-1399/RISCVZone/tree/main/doc/pic/VirtrualAddress/VirtrualAddress5.png

其实就是将线性页表分成了多少等份，这样就变成了二级页表，比如

比如一个32位的虚拟地址，可以利用前10位来索引第一级页表，使用中间10位 + 一级页表的基地址索引二级页表的页表项（PTE）

https://github.com/xie-1399/RISCVZone/tree/main/doc/pic/VirtrualAddress/VirtrualAddress6.png

这样当虚拟地址的p1部分变化的时候，操作系统在物理内存上创建一个新的第二级页表

显然这个一级页表的存储空间是不可避免的，而二级页表是否存在就需要根据程序中的虚拟地址的值来决定，随着处理器位数的增加，可以通过增加级数的方式来减少页表对于物理内存的占用

https://github.com/xie-1399/RISCVZone/tree/main/doc/pic/VirtrualAddress/VirtrualAddress7.png

但分页也会带来一些缺点，比如二级页表需要访问两次物理地址才能得到虚拟地址对应的物理地址

##### Page Fault

当出现Page Fault的时候通常处理过程是软件完成的

（1）可能需要替换一些最近不经常被使用的页，使用软件可以实现比较灵活的替换算法

（2）由于要访问硬盘，而异常处理程序也就几百条指令，相比于硬盘的访问时间是微乎其微的

操作系统会在硬盘上为一个进程的所有页开辟一块空间（swap），这时也会有一个存储进程所有页的一个类页表结构

为了帮助操作系统实现LRU算法对页表进行替换，可以在页表项中加入一个使用位，如果被访问了那么使用位就被置为1，并且操作系统可以周期性的将这一位进行清0操作

同时也还设置了脏位状态

https://github.com/xie-1399/RISCVZone/tree/main/doc/pic/VirtrualAddress/VirtrualAddress8.png

#### MMU

MMU时处理器中负责将虚拟地址转化为物理地址的功能单元

没有TLB的时候，并且没有分页的时候：

```
如果没有发生Page Fault的时候
（1）虚拟地址被送到MMU中
（2）根据VPN和页表寄存器寻找到访问的页表的地址，送到物理内存中
（3）将寻到的页表项返回给MMU
（4）这时会检查有效位，如果发现有效 ,PA={PFN,VA[11:0]}，也就是最后的物理地址
```

```
如果发生了Page Fault的时候
唯一有差别的是在（4）发现有效位无效，这时由MMU触发一个Page Fault的异常给处理器，同时这一步还会把Page Fault的虚拟地址保存到专用的寄存器中

需要注意异常处理程序需要替换某个页的时候，如果这个页的脏状态为1，表示这个页在以前被修改过，因此就需要首先将它从物理内存写到硬盘中，同时这个新的映射关系也会被写到页表中
```

https://github.com/xie-1399/RISCVZone/tree/main/doc/pic/VirtrualAddress/VirtrualAddress9.png

#### 程序保护

需要注意的几个问题：

（1）操作系统与用户进程之间的矛盾

（2）不同进程之间的保护（不能让其它的进程随便的修改自己的内存）

在ARM架构中，规定处理器可以工作在User、Priviledge模式下，并且直接规定了每个页的访问权限

https://github.com/xie-1399/RISCVZone/tree/main/doc/pic/VirtrualAddress/VirtrualAddress10.png

这样如果权限不符合规定的时候，就会产生一个异常来通知处理器，因此可以当作是在地址转换的过程中加入权限检查的过程

https://github.com/xie-1399/RISCVZone/tree/main/doc/pic/VirtrualAddress/VirtrualAddress11.png

当然如果在不同级的页表下设置的权限对应的粒度是不一样的

外设的地址当然是不会被Cache缓存的，又不是读数据（缓存有什么意义呢），因此不妨在处理器的存储器映射中选择一块区域是不可以被缓存的（这个属性可以在页表中进行标记，在访问页表得到物理地址时）





















