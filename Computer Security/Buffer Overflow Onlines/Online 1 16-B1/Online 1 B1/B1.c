#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef PARAM_1
#define PARAM_1 668
#endif

#ifndef PARAM_2
#define PARAM_2 1606
#endif

#ifndef PARAM_3
#define PARAM_3 1068
#endif

int bof(char *str)
{
    int arr[10];
    arr[5] = 7;
    {
		char buffer[PARAM_1];

		/* The following statement has a buffer overflow problem */ 
		strcpy(buffer, str);
		printf("%s",buffer);
    }
    return 1;
}

int foo(char *str)
{
    int arr[PARAM_2];
    arr[120] = 23;
    bof(str);
    return 1;
}

int secret()
{
    printf("Inside a Secret function\n");
}


int main(int argc, char **argv)
{
    char str[PARAM_3];
    FILE *badfile;
	
    bof("Normal Execution\n");
    badfile = fopen("badfile", "r");
    fread(str, sizeof(char),PARAM_3, badfile);
    foo(str);

    printf("Try Again\n");
    return 1;
}

