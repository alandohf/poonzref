// -----------------------------------------------------------------------------
// -- Tree Drawing -------------------------------------------------------------
// -----------------------------------------------------------------------------
// --------------------------------- 22/12/11 ----------------------------------
// -----------------------------------------------------------------------------
// ------------------------------------------------------------------- By A4i --
// -----------------------------------------------------------------------------

#include <stdio.h>

void printTriangle(int width);
void printLine(int size);
void printBase(int size);
void printTree(int size);

int main(int argc, char *argv[])
{
	int arg, inCheck, size;

	if(argc == 2)
	{
		inCheck = sscanf(argv[1], "%d", &arg);

		if(inCheck && (arg > 0) && (arg <= 40))
		{
			size = arg;
		}
		else
		{
			goto Begin;
		}
	}
	else
	{
		Begin:

		puts("Welcome to the TreeDrawing program...\n");

		do
		{
			printf("Enter the width [0 < width <= 40] : ");
			inCheck = scanf("%d", &size);
			fflush(stdin);
		}
		while(!inCheck || (size < 0) || (size > 40));
	}

	printf("\n");

	printTree(size);

	printf("\n");
	getchar();
	return 0;
}

void printTriangle(int width)
{
	int i, n, size, tmp;

	for(n = 1; n <= width; n++)
	{
		tmp = (width - n);

		for(i = 0; i < tmp; i++)
		{
			printf(" ");
		}

		for(i = 0; i < n; i++)
		{
			printf("*");

			if(i < n - 1)
			{
				printf(" ");
			}
		}

		printf("\n");
	}
}

void printLine(int size)
{
	int i, j, tmp;

	tmp = (2 * size - 2) / 2;

	for(i = 0; i < (size / 2); i++)
	{
		for(j = 0; j < tmp; j++)
		{
			printf(" ");
		}

		printf("I");

		if(i != (size - 2) - 1)
		{
			printf("\n");
		}
	}
}

void printBase(int size)
{
	int i, tmp, width;

	width = size / 2;

	tmp = size - width;

	for(i = 0; i < tmp; i++)
	{
		printf(" ");
	}

	for(i = 0; i < width; i++)
	{
		printf("+");

		if(i != width - 1)
		{
			printf(" ");
		}
	}
}

void printTree(int size)
{
	printTriangle(size);
	printLine(size);
	printBase(size);
}
ShellExecute()