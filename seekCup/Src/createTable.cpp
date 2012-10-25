#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql.h"

table * createTable(const char * str)
{
  table * tb = (table *)calloc(1, sizeof(table));
  
  if(tb == NULL){
    printf(ERROR);
    return NULL;
  }

  int i, j;
  int * p = (int *)malloc(sizeof(int));
  char * str2 = (char *)malloc(sizeof(char) * (strlen(str) + 1));
  
  strcpy(str2, str);
   char ** ch = split(str2, "," , p);
  for (i = 0;i < *p;++i) {
    TYPE t;
    char s[256];
    col * newCol = (col *)calloc(1, sizeof(col));
    sscanf(ch[i], "%s", s);
    newCol->next = tb->rootCol;
    tb->rootCol = newCol;
    newCol->name = (char *)malloc(sizeof(char) * 256);
    strcpy(newCol->name, s);
    if (strrchr(ch[i], ' ')) {
      if (strstr(ch[i], "int")) {
  	t = Int;
      }
      if (strstr(ch[i], "float")) {
  	t = Float;
      }
      if (strstr(ch[i], "text")) {
  	t = Text;
      }
    }
    else {
      t = None;
    }
    newCol->type = t;
    ++(tb->colCnt);
  }
 
  return tb;
}
