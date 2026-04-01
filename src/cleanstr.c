#include <stdio.h>
#include <string.h>


#include "modify.h"

void cleanStr(char *str)
{
    int len = strlen(str);
    while ((len > 0) && (str[len - 1] == '\n' || str[len - 1] == '\r'))
    {
        str[len - 1] = '\0';
        len--;
    }
};

