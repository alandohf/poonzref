/**
name:  test ÄÚ´æÔ½½ç
purpose:  test heap size
dependence: 
compiler: tcc/dev-cpp
summary:


refs: 
**/

#include <stdio.h>
char* fun(char *a,char *b);
int main(int argc,char *argv[]){
char *p1,*p2;
p1 = (char*)malloc(10);
//p2 = (char*)malloc(10000000000000000000);

//p2 = (char*)malloc(100000000000000000);
//printf("%p\n",p1);
printf("%p\n",p2); // overflow
free(p1);
//free(p2);

int i = 0;
int n = 1;
while(1){
i++;
n=i*1024*1024;
p2 = (char*)malloc(n);
printf("%p\t%d\n",p2,n); // overflow
if(NULL ==p2){
free(p2);
break;	
}
free(p2);
}
return 0;

}
