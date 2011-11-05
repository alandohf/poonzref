/**
name: test strrchr()
purpose: 
dependence: <string.h>
compiler: tcc/dev-cpp
summary:
refs:
http://baike.baidu.com/view/1756792.htm
**/

#include <stdio.h>
#include <string.h>
int main(int argc,char *argv[]){
char location[100] = "/path/to/dir/program";
char *path;
printf("%s\n",location);
path=strrchr(location,'/'); /**       '/' not "/" **/
printf("%s\n",path);
path++;
printf("%s\n",path);
system("PAUSE");
return 0;
}

