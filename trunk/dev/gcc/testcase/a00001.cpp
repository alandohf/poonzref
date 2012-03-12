/**
*按行读取文件内容，文件缓冲区长度固定
**/

#include <stdio.h>
#include <string.h>

int main()
{
    char str[200];
    FILE *fp;

    fp = fopen("t00101.c", "r");
    if(!fp) return 1; // bail out if file not found
    while(fgets(str,sizeof(str),fp) != NULL)
    {
        // strip trailing '\n' if it exists
        int len = strlen(str)-1;
        if(str[len] == '\n')
            str[len] = 0;
        printf("\n%s", str);
    }
    fclose(fp);
	return 0;
}

