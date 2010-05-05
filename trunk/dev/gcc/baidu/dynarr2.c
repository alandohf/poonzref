/*
 c =====================================================================================
 *
 *       Filename:  dynarr.c
 *
 *    Description:  G
 *
 *        Version:  1.0
 *        Created:  05/04/2010 04:40:55 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

int main()
{
     int *array = 0, num = 0 , i ;
//     printf("please input the number of element: ");
//     scanf("%d", &num);

     array = (int *)malloc(sizeof(int)*100);
     if (array == 0)             // 内存申请失败,提示退出
     {
         printf("out of memory,press any key to quit...\n");
         exit(0);             // 终止程序运行,返回操作系统
     }

//      printf("please input %d elements: ", num);
      while (scanf("%d",&array[num]) != EOF )
       {
	 num++;
        }

     printf("there are %d elements : \n", num);
     for (i = 0; i < num; i++)
         printf("%d,", *(array+i));
//         printf("%d,", array[i]);

     printf("\b \n");    // 删除最后一个数字后的分隔符逗号
     free(array);        // 释放由malloc函数申请的内存块
     return 0;
}
