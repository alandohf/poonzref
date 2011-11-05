// crt_getcwd.c
/* This program places the name of the current directory in the 
 * buffer array, then displays the name of the current directory 
 * on the screen. Specifying a length of _MAX_PATH leaves room 
 * for the longest legal path name.
 */

#include <direct.h>
#include <stdlib.h>
#include <stdio.h>

int main( int argc,char *argv[] )
{
   char buffer[_MAX_PATH];

   /* Get the current working directory: */
   if( _getcwd( buffer, _MAX_PATH ) == NULL )
      perror( "_getcwd error" );
   else
      printf( "%s\\%s\n", buffer,argv[1] );
}
