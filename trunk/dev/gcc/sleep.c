 #include <unistd.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 #include <string.h>
 
#define SIZE 256


 int alert(char msg[]);
 char* alert_time(void);
 char tm_buffer[SIZE];

 int main(){
//intialize msg
	char *msg;
  if ( strcmp(alert_time(),"07:00") == 0 ) {
  msg = alert_time();
	strcat(msg, "传日接口/一致性检查/KPI彩铃");
 	alert(msg);
}
  
  if ( strcmp(alert_time(),"08:00") == 0 ) {
  msg = alert_time();
	strcat(msg, " 无论如何，该起床了! ");
 	alert(msg);
}

  if ( strcmp(alert_time(),"08:30") == 0 ) {
  msg = alert_time();
	strcat(msg, " 无论如何，该出门了! ");
 	alert(msg);
}


  if ( strcmp(alert_time(),"12:00") == 0 ) {
	strcat(msg, " 波动性-一致性-接口上传情况上报。实际假日除外!");
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
	strcat(msg, " 无论如何，该睡觉了! ");
 	alert(msg);
}

  if ( strcmp(alert_time(),"00:00") == 0 ) {
	strcat(msg, " 无论如何，该睡觉了! ");
 	alert(msg);
}
 return 0;
}

/*
*************************************************
*self defined functions
***************************************************
*/

int alert(char msg[1000]){
	char cmd[2000];
	sprintf(cmd,"wscript ./alert.vbs %s",msg);
	system(cmd);
	return 0;
	}

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
