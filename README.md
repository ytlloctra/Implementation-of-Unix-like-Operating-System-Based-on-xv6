# 基于xv6的类Uinx操作系统实现

## 实现功能

- 系统启动：完成了该系统在启动过程中的配置，将进入保护模式后堆栈的起点设在0x7c00地址处，并且引导进入kernel程序。
- 系统调用：提供了用户态陷入内核态的软中断，设置中断号为64，实现了自定义系统调用myalloc、myfree等。
- 内存管理：通过编写物理页分配器，以链表管理所有空闲页帧，实现了对物理页帧的回收与分配；在xv6系统sbrk内存管理方式的基础上，添加了进程用户空间非连续分区的分配。
- 进程管理：添加了常见的IPC通信模块（共享内存、消息队列）；设计了自旋锁, 为用户进程提供互斥机制。以进程上下文切换为基础，实现了时间片轮转调度算法。

## 总结

![XV6总结](https://image-1312312327.cos.ap-shanghai.myqcloud.com/xv6%E7%B3%BB%E7%BB%9F.png)

## 运行

- 运行环境   ubuntu18.04   qemu   gcc
- 运行

```shell
make qemu
```

## 运行结果

### 01 自定义系统调用

查看运行进程的pid号

- 编写 pcpuid.c 代码
- 同样修改 Makefile，添加一行 pcpuid 即可， 系统启动以后直接输入 pcpuid  打印cpu号
- 在 syscall.h 中添加一行系统调用号 22 号
- 然后再增加用户态的进入接口，在 user.h 中添加一行 int getcpuid(void); （getcpuid函数在 pcpuid.c中调用了）
- 在 usys.S 中加入一行 SYSCALL(getcpuid) 以定义用户态的入口。将系统调用号保存在eax寄存器中 触发软中断 int 0x40（int 64）进入内核的中断处理函数



=======================================================================================================================================================================内核与应用层分割线==



- 在 syscall.c 中的分发函数表中添加 getcpuid 函数所对应的表项        [SYS_getcpuid] sys_getcpuid   （以eax及系统调用号 在 syscalls[]系统调用表中找到需要执行的代码）
- 然后修改 syscall.c，添加一行 sys_getcpuid 函数的声明                    extern int sys_getcpuid(void);
- 然后开始实现 sys_getcpuid 函数。在 sysproc.c 中添加 sys_getcpuid 的实现  

```cpp
sys_getcpuid(void) {
  return getcpuid();
}
```

- 在 proc.c 中实现内核态的 getcpuid 函数

```cpp
int getcpuid() {
  return cpunum();
}
```

- 最后在defs.h中加入 getcpuid 用作内核态代码调用 getcpuid()时的函数原型  （为了让sysproc.c中的sys_getcpuid()可以调用proc.c中的getcpuid()）

![image-20221113151208459](https://image-1312312327.cos.ap-shanghai.myqcloud.com/image-20221113151208459.png)

### 02 观察时间片调度过程

![image-20221113151404983](https://image-1312312327.cos.ap-shanghai.myqcloud.com/image-20221113151404983.png)

### 03 调整时间片长度

运行结果

  cprintf("slice left:%d ticks,%d %s %s", p->slot, p->pid, state, p->name);

输出4个参数    时间片剩余数  进程号  进程状态  进程名字 

![image-20221113151455361](https://image-1312312327.cos.ap-shanghai.myqcloud.com/image-20221113151455361.png)

### 04 信号量

![image-20221113151527291](https://image-1312312327.cos.ap-shanghai.myqcloud.com/image-20221113151527291.png)

### 05 IPC通信

共享内存

![image-20221113151603799](https://image-1312312327.cos.ap-shanghai.myqcloud.com/image-20221113151603799.png)

消息队列

![image-20221113151624919](https://image-1312312327.cos.ap-shanghai.myqcloud.com/image-20221113151624919.png)

### 06 内存分配myalloc

![image-20221113151657314](https://image-1312312327.cos.ap-shanghai.myqcloud.com/image-20221113151657314.png)

#### 遇见问题

![image-20221113151723278](https://image-1312312327.cos.ap-shanghai.myqcloud.com/image-20221113151723278.png)

解决：

![image-20221113151733613](https://image-1312312327.cos.ap-shanghai.myqcloud.com/image-20221113151733613.png)