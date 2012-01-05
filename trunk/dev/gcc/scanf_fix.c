#include <stdio.h>

void clean_stdin(void)
{
    int c;

    do
    {
        c = fgetc(stdin);
    }
    while (c != '\n' && c != EOF);
}

int main(void)
{
    int n;
    int rv;

    do
    {
        printf("Enter the number:\n");
        rv = scanf("%d", &n);
        clean_stdin();
    }
    while (rv != 1);

    printf("this is the number %d\n", n);
system("PAUSE");
    return 0;
}
