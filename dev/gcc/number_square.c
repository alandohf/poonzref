#include <stdio.h>

const int num_rows = 7;
const int num_columns = 5;

int
main()
{
  int box[num_rows][num_columns];
  int row, column;

  for(row = num_rows - 1; row >= 0 ; row--)
    for(column = num_columns-1; column >= 0; column--)
      box[row][column] = column + (row * num_columns);

  //for(row = 0; row < num_rows; row++)
  for(row = num_rows - 1; row >= 0 ; row--)
    {
    //  for(column = 0; column < num_columns; column++)
    for(column = num_columns - 1 ; column >= 0; column--)
        {
          printf("%4d+%d*%d=%2d", column,row,num_columns,box[row][column]);
        }
      printf("\n");
    }
  return 0;
}
