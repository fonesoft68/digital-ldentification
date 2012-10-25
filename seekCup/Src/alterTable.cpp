#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql.h"

int altertable(const char * str)
{
  int * p = (int *)malloc(sizeof(int));
  char * s = (char *)malloc(sizeof(char) * (strlen(str) + 1));
  
  strcat(s, str);
  char ** ch = split(s, " ", p);
  if(*p == 5);
}
