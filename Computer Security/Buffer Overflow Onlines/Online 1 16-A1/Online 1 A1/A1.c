
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef PARAM_1
#define PARAM_1 35
#endif

#ifndef PARAM_2
#define PARAM_2 698
#endif

#ifndef PARAM_3
#define PARAM_3 913
#endif

int foo(char *str)
{
    int arr[PARAM_1];
    char buffer[PARAM_2];

    /* The following statement has a buffer overflow problem */ 
    strcpy(buffer, str);

    return 1;
}

int main(int argc, char **argv)
{
    char str[PARAM_3];
    FILE *badfile;

    badfile = fopen("badfile", "r");
    fread(str, sizeof(char), PARAM_3, badfile);
    foo(str);

    printf("Try Again\n");
    return 1;
}

