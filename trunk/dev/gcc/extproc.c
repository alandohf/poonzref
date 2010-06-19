#include	<stdlib.h>
int sysrun(char *command);
int sysrun(char *command)
{
   return system(command);
}

