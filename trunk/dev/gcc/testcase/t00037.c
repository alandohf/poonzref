/**
name: test how the array item arrange
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:
1.����Ԫ�شӵ͵�ַ��ߵ�ַ����
2.�ڲ����鰴����˳����������
a[0],[a1]..������������飻
Ҫ�����С���ڲ�����Ԫ�أ���Ҫ����ά�Ȳ���a[i][j]��
3.ά��Խ��[][][]..������Ԫ��Խϸ������Խ�֡�
refs: 4.2.3 c in deep
**/

#include <stdio.h>

int main(int argc,char *argv[]){

int a[3][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};

int i=0,j=0;

for (i=0;i<3;i++){
    for(j=0;j<4;j++){
	    printf("a[%d][%d]\t%p\t%d\ta[%d]=%d\n"
				,i,j,&a[i][j],a[i][j],i,*(a[i]));
	}
}

return 0;

}
