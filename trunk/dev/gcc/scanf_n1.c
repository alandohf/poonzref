#include <stdio.h>
#include <stdlib.h>
int main()
{
    int v;  // value read from scanf
    int r;  // return value from scanf
    int e;  // error count
    e = 0;  // initialize to no errors
    do
    {
        r = scanf("%d", &v);   
        if (!r) e++;        // if error, count it
        printf("        %3d Read, return %d \n", v, r);
    } while ((v != 0) && (e < 4));
    system("PAUSE");
    return 0;
}

