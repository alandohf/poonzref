#include <stdio.h>
int main(void)
{
//        printf("hello world!\n");
//        getch();
//        scanf();
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

          int iVar1;
          int iVar2;
	  int ivar_a[10];
          int *p;
	  iVar1 = 99;
	  iVar2 = 100;
          p=&iVar1;
	  //p=&a[0];
	  p=ivar_a;
          printf("%p\t%d\t%p\n",&iVar1,*(&iVar1),&(*(&iVar1)));
          printf("%p\t%d\t%p\n",&iVar2,*(&iVar2),&(*(&iVar2)));
          int i ;
          for(i=0;i<10;i++)
	  {
          *(p+i)=i;
          printf("%p\t%p\t%d\t%d\t%d\t%d\t%p\t%d\n"
		  ,p
		  ,p+i
		  ,sizeof (p+i)
		  ,sizeof (void *)
		  ,sizeof (char *) /*size of pointer*/
		  ,*p  /*value of p*/
		  ,&p  /*address of p*/
		  ,*(p+i)
		);
          }
    return 0;
}
