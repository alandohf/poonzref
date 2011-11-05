/**
name: restrict
purpose:  
dependence: 
compiler: tcc/dev-cpp
summary:

refs:
http://bbs.chinaunix.net/viewthread.php?tid=948963&page=3

原帖由 phoneix 于 2007-6-16 22:16 发表
我曾经读过一篇介绍 restrict 历史的文章，提出 restrict 的是某个在标准委员会中很有影响的大公司，他们设计的硬件体系和别人的有所不同，在他们的硬件上编译器可以很方便的实现 restrict 的功能，但是在其他的硬件平台上这个关键字毫无用处，所以当该公司把 restrict 提交到C++标准委员会的时候，被委员会毫不留情的拒绝了，而不知道是什么原因，在稍晚的ISO C99中却把 restrict 加入了标准。



ANSI 据绝的是noalias, 
为了提高 Cray机器上的效率, ANSI C委员会提出过一种称为noalias的机制来解决这个问题，
用它来说明某个C指针可以认为是没有别名, 只是这种机制不成熟，这件事激怒了Dennis Ritchie，
拿他对C的标准化过程做了唯一的一次干预。他写了一封公开信说“noalias必须靠边站，这一点是不能协商的。”  

后来Cray的Mike Holly又抓起了这个难题，向数值C语言扩充工作组和C++委员会提出了一种改进的反别名建议。
所建议的想法是允许程序员说明一个指针可以认为是没有别名的，采用的方式是将它说明为restrict。  
这个建议C99采纳了，但标准C++拒绝了。

g++ 实际上也可以通过 __restrict__ 或 __restrict  来识别 C99 中的这个特性

C Primer Plus 5e
The restrict keyword enhances computational support by giving the compiler permission to optimize certain kinds of code. It can be applied only to pointers, and it indicates that a pointer is the sole initial means of accessing a data object.

The keyword restrict has two audiences. One is the compiler, and it tells the compiler it is free to make certain assumptions concerning optimization. The other audience is the user, and it tells the user to use only arguments that satisfy the restrict requirements. In general, the compiler can't check whether you obey this restriction, but you flout it at your own risk.

**/


