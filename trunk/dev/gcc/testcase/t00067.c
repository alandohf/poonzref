// crt_chmod.c
// This program uses _chmod to
// change the mode of a file to read-only.
// It then attempts to modify the file.
//

#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

// Change the mode and report error or success 
void set_mode_and_report(char * filename, int mask)
{
   // Check for failure 
   if( _chmod( filename, mask ) == -1 )
   {
      // Determine cause of failure and report. 
      switch (errno)
      {
         case EINVAL:
            fprintf( stderr, "Invalid parameter to chmod.\n");
            break;
         case ENOENT:
            fprintf( stderr, "File %s not found\n", filename );
            break;
         default:
            // Should never be reached 
            fprintf( stderr, "Unexpected error in chmod.\n" );
       }
   }
   else
   {
      if (mask == _S_IREAD)
        printf( "Mode set to read-only\n" );
      else if (mask & _S_IWRITE)
        printf( "Mode set to read/write\n" );
   }
   fflush(stderr);
}

int main( void )
{ 

   // Create or append to a file. 
   system( "echo first > crt_chmod.c_input" );

   // Set file mode to read-only: 
   set_mode_and_report("crt_chmod.c_input ", _S_IREAD );
   
   system( "echo second >> crt_chmod.c_input " );

   // Change back to read/write: 
   set_mode_and_report("crt_chmod.c_input ", _S_IWRITE );
 
   system( "echo third >> crt_chmod.c_input " ); 
   system("PAUSE");
} 
