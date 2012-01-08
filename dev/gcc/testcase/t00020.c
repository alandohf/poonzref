/**
name: using struct ptr
purpose: 
compiler: tcc/dev-cpp
summary:
refs:
http://computer.howstuffworks.com/c31.htm
http://stackoverflow.com/questions/1543713/c-typedef-of-pointer-to-structure
1.17.2 shendupoxi
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char *argv[]){

	typedef struct st_table {
	int id;
	char *name;
	} *st_ptable ,st_table;

	st_ptable tab;

	// !!!!!!!
	tab  = (st_ptable)malloc(sizeof(st_table)); // if define st_ptable, then it must allocate some memory for the 'tab' instance.
	tab->id=1;
	tab->name= "jack";
	printf("%d\t%s\n",tab->id,tab->name);
	free(tab);

return 0;

}







