/**
test strcpy(p,s)
summary: 
1. need to initailize p first. or strcpy will crash the program.
**/


int main(int argc,char *argv[]){
//char * p;strcpy(p,"def"); // illegal

char * p= "xxx";strcpy(p,"def"); // legal
char *p2 ;
p2="aaaaaaaaaa";

char s[10]="abc";

p = s;
printf("value:%p\n",&p);
printf("value:%p %p\n",p,&s);
printf("value:%s\n",p);
p="aaaaaaaaaa";
//p=p2;
printf("value:%p\t%p\n",p,p2);
printf("value:%s\t%s\n",p,p2);

printf("value:%s\t addr:%p\t%p\t%p\n",p,p,&p,&s);

strcpy(p,"def");
printf("value:%s\n",p);
return 0;

}
