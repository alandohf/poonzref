/**
test clock 
1.
http://baike.baidu.com/view/1516611.htm
����������شӡ��������������̡����������е���clock()������ʱ֮���CPUʱ�Ӽ�ʱ��Ԫ��clock tick��������MSDN�г�֮Ϊ����ʱ�䣨wal-clock����������ʱ�䲻��ȡ���򷵻�-1��
2.
�ڱ�׼C/C++�У���С�ļ�ʱ��λ��һ���롣
3.
����(finish - start) / CLOCKS_PER_SEC �����ʽ��
CLOCKS_PER_SEC �����ض�����ϵͳ���ǹ̶��ģ���ô��CPUԽǿ�ģ�����ʱ��ԽС��
��finish - start ��ҲԽС��
��finish - start ��ԽС��˵��clock tick �Ĵ���ԽС��
clock tick �Ĵ���ԽС��˵��ÿ��clock tick�����ָ����Խ�ࡣ

4.
1000 clocks/s  then  1 clock_tick = 1/1000 s = 1ms 
���ԣ����ڲ�ͬ�Ļ��������ǵ����������Ϊ�ǣ� ÿ 1ms �����ָ��������Ĳ��

5.
clock() �����������Ϊ�������˶�Ա���������ö����ٶȡ��ܡ�����ʼ���ú���ı�(clock tick)����ʱ��
�ܵ�Խ�죬������ԽС��ʱ��Խ�̣�
6.
clock() �ľ����ԣ�
�������̫�죬�������ֺ�С��ָ����٣�����1 tick �������ˣ���ôִ��ʱ��С����С��ʱ��λ����ôʱ��Ͳⲻ���ˣ���


7.
A tick is an arbitrary unit for measuring internal system time. There is usually an OS-internal counter for ticks; the current time and date used by various functions of the OS are derived from that counter.

How many milliseconds a tick represents depends on the OS, and may even vary between installations. Use the OS's mechanisms to convert ticks into seconds.


 * Number of clock ticks per second. A clock tick is the unit by which
 * processor time is measured and is returned by 'clock'.

#define	CLOCKS_PER_SEC	((clock_t)1000)
#define	CLK_TCK		CLOCKS_PER_SEC

CLOCKS_PER_SEC ÿ��ִ�е�ʱ�����ڴ���

8.��Ϊ���clock() �Ĵ�С������cpu�Ĵ����ٶȣ����Կ������Ϊ���̵�cpuʱ�䡣


9.
ת��ࣺ
c:\Dev-Cpp\bin\gcc.exe -S t00073.c
���תexe:
c:\Dev-Cpp\bin\gcc.exe -c t00073.s
c:\Dev-Cpp\bin\gcc.exe -o my.exe  t00073.o


10.gcc ���ע�ͣ�ͬc !

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

