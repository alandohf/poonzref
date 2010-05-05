/*
 * =====================================================================================
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
#include <math.h>

int min2(int *arr);
int main()
{
     int *array = 0;
     int *arr2= 0;
     int  target ,num, i;

     printf("please input a integer : ");
     scanf("%d", &target);
     printf("please input the number of element: ");
     scanf("%d", &num);

     array = (int *)malloc(sizeof(int)*num);
     arr2 = (int *)malloc(sizeof(array));
     if (array == 0)             // 内存申请失败,提示退出
     {
         printf("out of memory,press any key to quit...\n");
         exit(0);             // 终止程序运行,返回操作系统
     }

      printf("please input %d elements: ", num);
      for (i = 0; i < num; i++)
        {
         scanf("%d", &array[i]);
//         printf("%d,", *(array+i));
// 	 *(arr2+i) = abs(target-*(array+i));
//         printf("%d,", *(array+i));
	}


     printf("%d elements are: \n", num);
     for (i = 0; i < num; i++)
	{
         *(arr2+i) = abs(target - *(array+i));
         printf("%d,", *(array+i));
         printf("%d,", *(arr2+i));
 	}
         printf("\n");

     printf("%d\n", min2(arr2));
     free(array);        // 释放由malloc函数申请的内存块
     free(arr2);        // 释放由malloc函数申请的内存块
     return 0;
}
 

int min2(int *arr)
{
 int min,len,i=0,sn;

 while(arr[i] != '\0' )  {
  len++;  
  i++;
}

for(i=0;i<len;i++)
 {
  if(min>arr[i]){min=arr[i];sn = i+1;}
 }
return min;
} 


