#include <stdio.h>
  int swap (int *a, int *b);
int
main()
{

  int first = 12, second = 34;

  printf("f is %d and s is %d\n", first, second);

  swap(&first, &second);

  printf("f is %d and s is %d\n", first, second);

  return 0;
}
     
  int swap (int *a, int *b)
    {
      int c;

      c = *a;
      *a = *b; //a��ַ�ϵ�ֵ���ı�
      *b = c;  //b��ַ�ϵ�ֵ���ı�

      return 0;
    }
