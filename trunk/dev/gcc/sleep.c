 #include <unistd.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 #include <string.h>
 
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

    typedef struct { char *key; int val; } t_symstruct;

    static t_symstruct lookuptable[] = {
        { "07:00", C0700 }, { "08:00", C0800 }, { "08:30", C0830 }, { "12:00", C1200 }
       ,{ "12:28", C1228 }, { "19:00", C1900 }, { "23:00", C2300 }, { "00:00", C0000 }
    };

    #define NKEYS (sizeof(lookuptable)/sizeof(t_symstruct))


 char* alert_time(void);
 int alert(char msg[]);
 char tm_buffer[SIZE];
 int keyfromstring(char *key);

 int main(){
//intialize msg
    switch (keyfromstring(alert_time())) {
    case C0700: 
		 	alert("day/same/ring");    	
    	break;
    case C0800: 
			alert("however,get/up! ");
 	    break;
    case C0830: 
			alert("however,go/out! ");
 	    break;
    case C1200: 
			alert("wave/same/interfaces.except/holidays!");
 	    break;
    case C1228: 
			alert("lunch!");
 	    break;
    case C1900: 
			alert("dinner!");
 	    break; 	     	     	    
    case C2300: 
			alert("however,sleep!");
 	    break; 	     	     	    
    case C0000: 
			alert("however,sleep!");
 	    break; 	     	     	    
    case BADKEY: printf("no jobs to be done!"); 
    }
/**    
	char *msg;
  if ( strcmp(alert_time(),"07:00") == 0 ) {
  msg = alert_time();
	strcat(msg, "传日接口/一致性检查/KPI彩铃");
 	alert(msg);
}
  
  if ( strcmp(alert_time(),"08:00") == 0 ) {
  msg = alert_time();
	strcat(msg, " however，该起床了! ");
 	alert(msg);
}

  if ( strcmp(alert_time(),"08:30") == 0 ) {
  msg = alert_time();
	strcat(msg, " however，该出门了! ");
 	alert(msg);
}


  if ( strcmp(alert_time(),"12:00") == 0 ) {
	strcat(msg, " 波动性/一致性/接口上传情况上报。实际假日除外!");
 	alert(msg);
}


  if ( strcmp(alert_time(),"12:28") == 0 ) {
	strcat(msg, " 吃饭时间！");
 	alert(msg);
}


  if ( strcmp(alert_time(),"19:00") == 0 ) {
	strcat(msg, " 吃饭时间！");
 	alert(msg);
}

  if ( strcmp(alert_time(),"23:00") == 0 ) {
	strcat(msg, " however，该睡觉了! ");
 	alert(msg);
}

  if ( strcmp(alert_time(),"00:00") == 0 ) {
	strcat(msg, " however，该睡觉了! ");
 	alert(msg);
}
 return 0;
 	**/

}

/*
*************************************************
*self defined functions
***************************************************
*/

char* alert_time(){
  time_t curtime;
  struct tm *loctime;
  /* Get the current time.  */
  curtime = time (NULL);
  /* Convert it to local time representation.  */
  loctime = localtime (&curtime);
  strftime(tm_buffer, SIZE, "%H:%M", loctime);
  return tm_buffer;
}


int alert(char msg[1000]){
	char cmd[2000];
	sprintf(cmd,"wscript ./alert.vbs %s %s",alert_time(),msg);
	system(cmd);
	return 0;
	}
	
int keyfromstring(char *key)
{
    int i;
    for (i=0; i < NKEYS; i++) {
        t_symstruct *sym = lookuptable + i;
        if (strcmp(sym->key, key) == 0)
            return sym->val;
    }
    return BADKEY;
}
      
/**
 	//char msg[100] = "abcd";

	while(i < 10){
	i++;
	printf("%d\n",i);
	sleep(1);
 }

	while(1){
	printf("%d\n",i);
	sleep(60);
 }
**/ 

