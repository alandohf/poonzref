/**
test perror()

��perror ( )�� �� �� �� һ �� �� �� �� �� �� �� �� ԭ �� �� �� �� �� ׼ �豸 (stderr) ������ s ��ָ���ַ������ȴ�ӡ��,�����ټ��ϴ���ԭ���ַ������˴���ԭ������ȫ�ֱ���error ��ֵ������Ҫ������ַ�����
�����ڿ⺯�����и�error������ÿ��errorֵ��Ӧ�����ַ�����ʾ�Ĵ������͡��������"ĳЩ"��������ʱ���ú����Ѿ�����������error��ֵ��perror����ֻ�ǽ��������һЩ��Ϣ�����ڵ�error����Ӧ�Ĵ���һ�������


**/
#include <stdio.h>


int main(int argc,char *argv[]){
//char * p;strcpy(p,"def"); // illegal
FILE *fp;
fp = fopen( "/root/noexitfile", "r+" );
if ( NULL == fp )
{
perror("/root/noexitfile");
}
extern error ;
error = -100;
while ( error < 100)
{
perror("test");
error++;
}
return 0;

}
