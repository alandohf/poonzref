#include <stdio.h>
//指定第N个元素值。其余默认初始化为0？
int
main()
{
  int i;
  int first_array[100] = { [90]=4, [0]=5, [98]=6 };
  double second_array[5] = { [3] = 1.01, [4] = 1.02 };

  printf("sure enough, first_array[90] == %d\n\n", first_array[90]);
  printf("sure enough, first_array[99] == %d\n\n", first_array[99]);

  for (i = 0; i < 5; i++)
    printf("value of second_array[%d] is %f\n", i, second_array[i]);

  return 0;
}

