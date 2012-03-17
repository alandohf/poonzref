#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <Windows.h> ; not needed

int	fileSize		( char File[] );
void	fileNameExt		( char Name[], char Ext[], char File[] );

int main( int argc, char *argv[] )
{
	int i,j;
	char car = 0;
	FILE	*source, *destination;
	int	size, parts;
	char	name[100], ext[100], aux[100];

	if( argc < 3 )
	{
		printf( "There aren't enough args!\n" );
		system( "pause" );
		return 0;
	}

	fileNameExt( name, ext, argv[1] );
	parts = atoi( argv[2] );
	size = fileSize( argv[1] );
	if( (source = fopen(argv[1], "rb")) == NULL )
	{
		printf( "Error! Source file could not be open!\n" );
		system( "pause" );
		return 0;
	}

	for(  i = 0; i < parts; i++ )
	{
		sprintf( aux, "%s-%d%s", name, i , ext );
		printf( "Generating %s file! -- ", aux );

		if( (destination = fopen(aux, "wb")) == NULL )
		{
			printf( "Error! Destination file %s could not be created!\n", aux );
			system( "pause" );
			return 0;
		}

		//car = getc( source ); // move into for loop
		for(  j = 0; j < size/parts && !feof(source); j++ )
		{
			car = getc( source );
			putc( car, destination );
		}
		//当size不能整除时：
		while (  ( i == parts-1 )  ){ //&&  !feof(source)
			car = getc( source );
			if(feof(source)) break;
			putc( car, destination );
		}
		// 相同的效果：
		//~ while (  ( i == parts-1 ) && (car = getc( source )) && (!feof(source))  ){ //&&  !feof(source)
			//~ putc( car, destination );
		//~ }

		printf( "OK!\n" );
		fclose( destination );
	}

	fclose( source );
	system( "pause" );
	return 0;
}

int fileSize( char File[] )
{
    FILE *f;
	int sz = 0;
    if( (f = fopen(File,"rb")) == NULL )
    {
          printf( "Error! Source file could not be open!\n" );
	  system( "pause" );
          return 0;
    }

    fseek( f, 0,SEEK_END );
     sz = ftell(f);
    fclose( f );

    return sz;
}

void fileNameExt( char Name[], char Ext[], char File[] )
{
	int i;
	char *aux;
	if( (aux = strrchr(File, '\\')) == NULL )
	{
		if( (aux = strrchr( File, '/' )) == NULL)
		{
			aux = File;
		}
	}

	if( aux != File )
	{
		aux++;
	}

	for(  i = 0; *aux != '.'; i++, aux++ )
	{
		Name[i] = *aux;
		Name[i+1] = '\0';
	}

	for(  i = 0; *aux != '\0'; i++, aux++ )
	{
		Ext[i] = *aux;
		Ext[i+1] = '\0';
	}
}
