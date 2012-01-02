	#define SIZE_OF_SQUARE 4
#include <stdio.h>
int
main()
{
  int i, j;

  for(i = 0; i < SIZE_OF_SQUARE; i++)
  {
    for(j = 0; j < SIZE_OF_SQUARE; j++)
    {
      printf("*"); // print an asterisk for each column
    }

    printf("\n"); // and a newline at the end of each row
  }
}
