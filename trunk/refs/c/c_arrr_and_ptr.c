#include <stdio.h>
// ָ�������֮�������ƥ�䡢��Ӧ��ϵ
int main(){
//1 dimention	
// ����ָ�� --  һά����	
int *p; 
int a[4] = {1,2,3,4} ; //initilize
p=a; // same type , a  is a pointer to int 
printf("%p\n",p);
// ==equals
printf("%p\n",a);
// ==equals 
printf("%p\n",&a);
// ==equals
printf("%p\n",&a[0]);
printf("-------------------\n");

//////////////////////////////
printf("%p\n",p+1);
//==equals
printf("%p\n",&(a+1));
printf("-------------------\n");

//////////////////////////////
printf("%p\n",&a+1);
//==equals
printf("%p\n",&p);  // why ?
printf("-------------------\n");
printf("%p\n",&a+2);
printf("%p\n",&a+3);
printf("-------------------\n");
printf("%p\n",&p+2);
printf("%p\n",&p+3);
printf("-------------------\n");
printf("%p\n",p+2);
printf("%p\n",p+3);
printf("-------------------\n");

int i ;
for (i = 0 ; i< 4 ; i++){
printf("%p\t%d\n",&a[i],a[i]);
}


printf("===================\n");

// ����ָ�� --  һά����	

//p=&a; // different type , (&a)  is a pointer to  an array of ints.
// so 
printf("-------------------\n");

int (*ap)[]; // define a pointer to an array 
ap=&a; // same type 

printf("%p\n",ap);
// ==equals
printf("%p\n",a);
// ==equals 
printf("%p\n",&a);
// ==equals
printf("%p\n",&a[0]);
printf("-------------------\n");

for (i = 0 ; i< 4 ; i++){
printf("%p\t%p\t%d\n",p+i,&a[i],a[i]);
}
//�����������Խ�����Ҳ������

// ��ά����

int arr_2d[3][4]={{1,2,3,4},{5,6,7,8},{9,10,11,12}};
printf("size:%d\n",(sizeof arr_2d)/(sizeof (int)));
p=arr_2d[0]; // agree ; pointer of int
p=&arr_2d[0][0]; //agree   ; pointer of int
// p ��������Ԫ��
int i ;
for (i = 0;i < (sizeof arr_2d)/(sizeof (int)) ; i++){
		printf("%d\n",*(p+i)); 
}

//p=arr_2d; //different type , arr_2d �� һ�� ����ָ�� ��ָ��һ����СΪ[4]������
//so :
int (*ap2)[4];
ap2=arr_2d; //same type ; 
printf("-------------------\n");

// ap2 ��������Ԫ��
int i , j;
for (i = 0;i < 3 ; i++){
	for (j=0;j<4;j++){
		printf("%d\n",(*(ap2+i))[j]); // ע�����ȼ� �� [] �� * ����
	}
}
//how about &arr_2d
int (*ap3)[3][4];
ap3=&arr_2d; // type agree!
printf("-------------------\n");

// ap3 ��������Ԫ��
int i , j;
for (i = 0;i < 3 ; i++){
	for (j=0;j<4;j++){
		printf("%d\n",(*ap3)[i][j]); // ע�����ȼ� �� [] �� * ����
	}
}
// ���� ap2 ��һ��һά����ָ�룻ap3��һ��2ά����ָ��. ����������arr_2d;
return 0;
}