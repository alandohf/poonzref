/*
**************************************************
*author panzhiwei
*http://stackoverflow.com/questions/4014827/best-way-to-switch-on-a-string-in-c
*v0.1 day alert
*v0.2 month alert 
*v0.3 suspend for n mins
*v0.4 week alert
1.
*compile methods:
*cmd>time 9:30 && date 2011-05-10
*D:\pzw\prj\poonzref\dev\gcc>\
*tcc alert_win.c -o alert.exe && time 9:30 && date 2011-05-10 &&  alert.exe
2.
*net start w32time
*w32tm /resync /nowait
3.
*2012-01-01 using gcc to compile:
*** C:\Dev-Cpp\bin\gcc.exe -pedantic -Os -c alert_win.c -o alert_win.o -std=c99
*** alert_win.c: In function `main':
*** alert_win.c:196: warning: implicit declaration of function `sleep'
-->
//use windows Sleep()
#include <windows.h>
#define sleep(n) Sleep(n)
4.
*** >C:\Dev-Cpp\bin\gcc.exe -pedantic -Os alert_win.c -o alert_win.exe
*** alert_win.c:29:1: warning: C++ style comments are not allowed in ISO C90
*** -->
*** >C:\Dev-Cpp\bin\gcc.exe -pedantic -Os alert_win.c -o alert_win.exe -std=c99
5.
rename alert_win.exe to alert.exe

**************************************************
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//use windows Sleep()
#include <windows.h>
#define sleep(n) Sleep(n)

//daily alert intervals 
#define SIZE 256
#define BADKEY -1
#define C0700 1
#define C0800 2
#define C0830 3
#define C1200 4
#define C1228 5
#define C1900 6
#define C2300 7
#define C0000 8
#define C0930 9
#define C1730 10
//monthly alert intervals 
#define D01 1
#define D02 2
#define D03 3
#define D04 4
#define D05 5
#define D06 6
#define D07 7
#define D08 8
#define D09 9
#define D10 10
#define D11 11
#define D12 12
#define D13 13
#define D14 14
#define D15 15
#define D27 27
#define D28 28
#define D29 29
#define D30 30
#define D31 31


typedef struct { char *key; int val; } t_symstruct;

static t_symstruct lookuptable_d[] = {
	 { "07:00", C0700 }
	,{ "08:00", C0800 }
	,{ "08:30", C0830 }
	,{ "12:00", C1200 }
	,{ "12:28", C1228 }
	,{ "19:00", C1900 }
	,{ "23:00", C2300 }
	,{ "00:00", C0000 }
	,{ "09:30", C0930 }
	,{ "17:30", C1730 }
};

static t_symstruct lookuptable_m[] = {
	 { "01", D01 }
	,{ "02", D02 }
	,{ "03", D03 }
	,{ "04", D04 }
	,{ "05", D05 }
	,{ "06", D06 }
	,{ "07", D07 }
	,{ "08", D08 }
	,{ "09", D09 }
	,{ "10", D10 }
	,{ "11", D11 }
	,{ "12", D12 }
	,{ "13", D13 }
	,{ "14", D14 }
	,{ "15", D15 }
	,{ "27", D27 }
	,{ "28", D28 }
	,{ "29", D29 }
	,{ "30", D30 }
	,{ "31", D31 }
};

#define NKEYS_D (sizeof(lookuptable_d)/sizeof(t_symstruct))
#define NKEYS_M (sizeof(lookuptable_m)/sizeof(t_symstruct))

/** global vars **/
struct tm *loctime;
char tm_buffer[SIZE];

/**prototype**/
//get current time 
struct tm *alert_time(void);
//take the alert action
int alert(char msg[]);
//get the index of hour/time
int keyfromstring(char *key,t_symstruct lookuptable[],int NKEYS );

 int main(){
	alert("program start...");

	while(1){ 
		   strftime(tm_buffer, SIZE, "%H:%M", alert_time());
		   //printf(tm_buffer);
	   switch (keyfromstring(tm_buffer,lookuptable_d,NKEYS_D)) {
		    case C0700: 
			alert("same_chk/day_interface");    	
			break;
		    case C0800: 
			alert("time ");
			break;
		    case C0830: 
			alert("wrkwrk");
			break;
		    case C1200: 
			alert("218report");
			break;
		    case C1228: 
			alert("lunch time!");
			break;
		    case C1730: 						
			// day 4 of week report
			if((*loctime).tm_wday == 4 ){
			   alert("week report");
			}
			break;
		    case C1900: 
			alert("dinner time!");
			break; 	     	     	    
		    case C2300: 
			alert("rest time!");
			break; 	     	     	    
		    case C0000: 
			alert("rest time!");
			break; 	     	     	    
		    case C0930: 
						strftime(tm_buffer, SIZE, "%d", alert_time());	
						// alert depend on date 
						switch (keyfromstring(tm_buffer,lookuptable_m,NKEYS_M)) {
						    case D01: 
							alert("#1.load_sample/bass1_lst#2.R107/108");    	
							break;
						    case D02: 
							alert("#3interface/upload");
							break;
						    case D03: 
							alert("#3interface_chk&#5interface/upload");
							break;
						    case D04: 
							alert("#5interface_chk&#8interface/upload");
							break;
						    case D05: 
							alert("#8interface_chk&#10interface/upload!");
							break;
						    case D06: 
							alert("#10interface_chk&#15interface/upload!!");
							break; 	     	     	    
						    case D07: 
							alert("05001/05002/all_month_interface_chk!");
							break; 	     	     	    
						    case D08: 
							alert("05001/05002/all_month_interface_chk!");
							break; 	     	     	    
						    case D09: 
							alert("05001/05002");
							break; 	     	     	    
						    case D10: 
							alert("zhanght.tcl");
							break; 	     	     	    
						    case D11: 
							alert("tbs chk/ftp down files");
							break; 	   
						    case D12: 
							alert("backup_tables/tbs_struct");
							break; 	   
						    case D27: 
						    case D28: 
						    case D29: 
						    case D30: 
						    case D31: 
							alert("LOAD_IMEI/91005");
							break; 	     	     	    
						    case BADKEY: 
							//do nothing 
							;
						} //inner switch end 
			break; 
		    case BADKEY: 
			//do nothing 
			; 
	} //outside switch end 
	
	sleep(59*1000);
	
	} //while end 
 
return 0;
	
} //main end



struct tm *alert_time(){
	time_t curtime;
	/* Get the current time.  */
	curtime = time (NULL);
	/* Convert it to local time representation.  */
	loctime = localtime (&curtime);
	//strftime(tm_buffer, SIZE, "%H:%M", loctime);
	return loctime;
}


int alert(char msg[1000]){
	char cmd[2000];
	FILE *fp;
	strftime(tm_buffer, SIZE, "%c", alert_time());
	sprintf(cmd,"wscript ./alert.vbs %s %s",tm_buffer,msg);
	//change the path if necessory
	if((fp=fopen("c:/Windows/Logs/alert.out","a"))==NULL){
		fprintf(stderr, " %s\n", strerror(errno));
		exit(1);
	}
	fprintf(fp, "%s %s\n", tm_buffer,msg); 
	fclose(fp);
	system(cmd);
	return 0;
	}

int keyfromstring(char *key,t_symstruct lookuptable[],int NKEYS )
{
	int i;
	for (i=0; i < NKEYS; i++) {
	t_symstruct *sym = lookuptable + i;
	if (strcmp(sym->key, key) == 0)
	    return sym->val;
	}
	return BADKEY;
}
