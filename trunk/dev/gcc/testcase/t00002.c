/**
i++ and ++i 
http://zhidao.baidu.com/question/2414662.html?an=0&si=1
**/
int main(int argc,char *argv[]){
int a , b;
a = 0;
b = 0;
printf("a=%d,b=%d \n",a,b);
printf("a=%d,b=%d \n",a++,b++);
printf("a=%d,b=%d \n",a,b);
a++;
b++;
printf("a=%d,b=%d \n",a,b);
return 0;
}
