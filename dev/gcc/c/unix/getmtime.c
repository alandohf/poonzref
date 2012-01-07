#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
time_t get_mtime(const char *path)
{
   struct stat statbuf;
   if (stat(path, &statbuf) == -1) {
                perror(path);
                exit(1);
   }
   return statbuf.st_mtime;
}

int
time_print(time_t thetime){
    struct tm *ts;
    char       buf[80];
  
    /* Format and print the time, "ddd yyyy-mm-dd hh:mm:ss zzz" */
    ts = localtime(&thetime);
    strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", ts);
    printf("%s\n",buf);
return 0;
}




int main(int argc,char *argv[]){
	//get_mtime("/bassapp/bass2/panzw2/.profile");
	time_print(get_mtime("c:\\boot.ini"));
        return 0;
}
