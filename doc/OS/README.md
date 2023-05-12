#### xv6-riscv安装教程
主要参考：https://pdos.csail.mit.edu/6.S081/2021/tools.html

在WSL中：

```
$ sudo apt-get update && sudo apt-get upgrade

$ sudo apt-get install git build-essential gdb-multiarch qemu-system-misc gcc-riscv64-linux-gnu binutils-riscv64-linux-gnu

#Boot
make qemu
```

