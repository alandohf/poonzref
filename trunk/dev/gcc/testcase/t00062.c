/**
name: restrict
purpose:  
dependence: 
compiler: tcc/dev-cpp
summary:

refs:
http://bbs.chinaunix.net/viewthread.php?tid=948963&page=3

ԭ���� phoneix �� 2007-6-16 22:16 ����
����������һƪ���� restrict ��ʷ�����£���� restrict ����ĳ���ڱ�׼ίԱ���к���Ӱ��Ĵ�˾��������Ƶ�Ӳ����ϵ�ͱ��˵�������ͬ�������ǵ�Ӳ���ϱ��������Ժܷ����ʵ�� restrict �Ĺ��ܣ�������������Ӳ��ƽ̨������ؼ��ֺ����ô������Ե��ù�˾�� restrict �ύ��C++��׼ίԱ���ʱ�򣬱�ίԱ���������ľܾ��ˣ�����֪����ʲôԭ���������ISO C99��ȴ�� restrict �����˱�׼��



ANSI �ݾ�����noalias, 
Ϊ����� Cray�����ϵ�Ч��, ANSI CίԱ�������һ�ֳ�Ϊnoalias�Ļ��������������⣬
������˵��ĳ��Cָ�������Ϊ��û�б���, ֻ�����ֻ��Ʋ����죬����¼�ŭ��Dennis Ritchie��
������C�ı�׼����������Ψһ��һ�θ�Ԥ����д��һ�⹫����˵��noalias���뿿��վ����һ���ǲ���Э�̵ġ���  

����Cray��Mike Holly��ץ����������⣬����ֵC�������乤�����C++ίԱ�������һ�ָĽ��ķ��������顣
��������뷨���������Ա˵��һ��ָ�������Ϊ��û�б����ģ����õķ�ʽ�ǽ���˵��Ϊrestrict��  
�������C99�����ˣ�����׼C++�ܾ��ˡ�

g++ ʵ����Ҳ����ͨ�� __restrict__ �� __restrict  ��ʶ�� C99 �е��������

C Primer Plus 5e
The restrict keyword enhances computational support by giving the compiler permission to optimize certain kinds of code. It can be applied only to pointers, and it indicates that a pointer is the sole initial means of accessing a data object.

The keyword restrict has two audiences. One is the compiler, and it tells the compiler it is free to make certain assumptions concerning optimization. The other audience is the user, and it tells the user to use only arguments that satisfy the restrict requirements. In general, the compiler can't check whether you obey this restriction, but you flout it at your own risk.

**/


