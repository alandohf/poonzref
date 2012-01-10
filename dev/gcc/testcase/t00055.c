/**
1.
http://publib.boulder.ibm.com/infocenter/iseries/v5r4/index.jsp?topic=%2Fapis%2Futime.htm
2.
	struct utimbuf {
	   time_t   actime;   
	   time_t   modtime; 
	   }
3.	   
 strftime format   :
 http://pubs.opengroup.org/onlinepubs/007908799/xsh/strftime.html 
4.	   
 http://pubs.opengroup.org/onlinepubs/009604599/functions/stat.html
#include <sys/stat.h>
int stat(const char *restrict path, struct stat *restrict buf);	   

5.utime(const char *path, const struct utimbuf *times)
6.
*1.http://stackoverflow.com/questions/4014827/best-way-to-switch-on-a-string-in-c
*2.time_t : http://www.delorie.com/gnu/docs/glibc/libc_433.html
*3. struct tm : http://www.daniweb.com/software-development/c/threads/335282
*4.http://linux.die.net/man/3/ctime
*5.time_t time(time_t *timer); // time_t -> long int 
*6.struct tm *localtime(const time_t *timer);
*7. time_t (time())-> struct tm (localtime())-> str (strftime())


¡ª Data Type: struct utimbuf
The utimbuf structure is used with the utime function to specify new access and modification times for a file. It contains the following members:

time_t actime
This is the access time for the file. 
time_t modtime
This is the modification time for the file.

http://www.gnu.org/software/libc/manual/html_node/File-Times.html

**/

#include <sys/stat.h>
#include <stdio.h>
#include <time.h>
#include <sys/utime.h>
 
const char *filename = "t00000.t";
 
int main() {
		  struct stat foo;
		  time_t mtime;
	
		  struct utimbuf new_times;
		  char strTime[20];
	
		  if (stat(filename, &foo) < 0) {
			perror(filename);
			return 1;
		  }
		  
		  mtime = foo.st_mtime; /* seconds since the epoch */
		 
		  new_times.actime = foo.st_atime; /* keep atime unchanged */
		  new_times.modtime = foo.st_mtime;    /* set mtime to current time */
		  strftime(strTime, 30, "%Y%m%d %H:%M:%S", localtime (&(new_times.actime)));
		  printf("file  actime: %s\n",strTime);
		  strftime(strTime, 30, "%Y%m%d %H:%M:%S", localtime (&(new_times.modtime)));
		  printf("file modtime: %s\n",strTime);
		 //	
		 //	if (utime(filename, &new_times) < 0) { // utime() --> update time 
		 //	  perror(filename);
		 //	  return 1;
		 //	}
		 //	
  return 0;
}
