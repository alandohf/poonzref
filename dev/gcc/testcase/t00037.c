/**
name: test how the array item arrange
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:
1.��ָ����м�1 �������õ�������һ��Ԫ�صĵ�ַ��������ԭ�е�ֱֵַ�Ӽ�1��
2.һ������ΪT ��ָ����ƶ�����sizeof(T) Ϊ�ƶ���λ

refs: 4.2.3 c in deep
**/

#include <stdio.h>

int main(int argc,char *argv[]){

int a[3][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};

int i=0,j=0;

for (i=0;i<3;i++){
    for(j=0;j<4;j++){
	    printf("%p\t%d\n",&a[i][j],a[i][j]);
	}
}

return 0;
}


