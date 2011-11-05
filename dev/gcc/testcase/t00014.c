/**
test structure 
1.
struct x1 { ... }; --> struct x1 a;
2.
typedef struct { ... } x2;  --> x2 b;
equal to : typedef struct  struct_tag { ... } x2;  --> x2 b;

3. C is not C++. Typedef names are not automatically generated for structure tags.

Why doesn't

struct x { ... };
x thestruct;
work?


**/

#include <stdio.h>
void testempty(void);
void testsize(void);
int main(int argc,char *argv[]){

testempty();
testsize();	
return 0;
}


void testempty(void){
typedef struct student {
//int i ;
//char c;
} stu;

printf(" size: %d \n", sizeof( stu));

}


void testsize(void){
typedef  struct student {
int i ;
char c;
} stu;

printf(" size: %d \n", sizeof(stu));
struct stu s1;
}





