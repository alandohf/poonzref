/**
test clock 
1.
http://baike.baidu.com/view/1516611.htm
这个函数返回从“开启这个程序进程”到“程序中调用clock()函数”时之间的CPU时钟计时单元（clock tick）数，在MSDN中称之为挂钟时间（wal-clock）；若挂钟时间不可取，则返回-1。
2.
在标准C/C++中，最小的计时单位是一毫秒。
3.
根据(finish - start) / CLOCKS_PER_SEC 这个公式，
CLOCKS_PER_SEC （在特定操作系统）是固定的，那么，CPU越强的，花的时间越小。
（finish - start ）也越小。
（finish - start ）越小，说明clock tick 的次数越小，
clock tick 的次数越小，说明每次clock tick处理的指令数越多。

4.
1000 clocks/s  then  1 clock_tick = 1/1000 s = 1ms 
所以，对于不同的机器，他们的区别可以认为是： 每 1ms 处理的指令的数量的差别。

5.
clock() 函数可以理解为：无论运动员（机器）用多大的速度“跑”，我始终用毫秒的表(clock tick)来计时。
跑得越快，毫秒数越小，时间越短！
6.
clock() 的局限性：
如果机器太快，而程序又很小，指令很少，不到1 tick 就跑完了，那么执行时间小于最小计时单位，那么时间就测不到了！！


7.
A tick is an arbitrary unit for measuring internal system time. There is usually an OS-internal counter for ticks; the current time and date used by various functions of the OS are derived from that counter.

How many milliseconds a tick represents depends on the OS, and may even vary between installations. Use the OS's mechanisms to convert ticks into seconds.


 * Number of clock ticks per second. A clock tick is the unit by which
 * processor time is measured and is returned by 'clock'.

#define	CLOCKS_PER_SEC	((clock_t)1000)
#define	CLK_TCK		CLOCKS_PER_SEC

CLOCKS_PER_SEC 每秒执行的时钟周期次数

8.因为这个clock() 的大小体现了cpu的处理速度，所以可以理解为进程的cpu时间。


9.
转汇编：
c:\Dev-Cpp\bin\gcc.exe -S t00073.c
汇编转exe:
c:\Dev-Cpp\bin\gcc.exe -c t00073.s
c:\Dev-Cpp\bin\gcc.exe -o my.exe  t00073.o


10.gcc 汇编注释：同c !

**/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int 
main(void)
{
	int abc = 999;
return -1;
}

