/**
name: test  precompile
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:
refs:
**/

#include <stdio.h>
#include <stdlib.h>


#define PI 3.1415926
//#undef PI 3.1415926
#define NUM 1234
#define SUM(x) (x)*(x) // () is needed

#define X 3            //X,Y����˳�� 
#define Y X*2  //X,Y����˳�� 
#undef X
#define X 2  

int main(int argc,char *argv[]){
	printf("%f\n",PI);
	printf("%d\n",NUM);
	printf("%d\n",SUM(5));

	int z=Y;
	printf("%d\n",z);

	//printf("%s\n",_FILE_);  //not support @dev-cpp
	system("PAUSE");
return 0;
}
