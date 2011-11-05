/**
name: using struct to simulate a table structure
purpose: 
compiler: tcc/dev-cpp
summary:
must know sprintf(),strcat(),malloc() usage !!  var dest must have allocate some memory!!
**/

#include <stdio.h>
int main(int argc,char *argv[]){

typedef struct st_table {
int id;
char *name;
} *st_ptable ,st_table;
st_table tab[10];
int i=0;
for ( i = 0 ; i < 10;i++ ) {
tab[i].id = i ;
//char *dest = (char*)malloc(sizeof(char)*10);
//dest="member";
tab[i].name= (char*)malloc(sizeof(char)*10);
sprintf(tab[i].name,"%s","member");

char src[10] = "a";
sprintf(src,"%d",i);
//printf("%s\n",src); 
//printf("%s\n",dest); 
//tab[i].name = src;
//tab[i].name = "mem";
//char *dest=tab[i].name;
//printf("%s",dest);
//printf("%s\n",tab[i].name);
strcat(tab[i].name,src);
printf("%d\t%s\n",tab[i].id+1,tab[i].name);
free(tab[i].name);
}

//system("PAUSE");
return 0;
}







