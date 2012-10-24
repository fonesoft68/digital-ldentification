#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql.h"

table * createTable(const char * str)
{
  table * tb = (table *)calloc(1, sizeof(table));
  
  if(tb == NULL){
    printf("memory error\n");
    return NULL;
  }

  int i, j;
  int * p = (int *)malloc(sizeof(int));
  char * str2 = (char *)malloc(sizeof(char) * (strlen(str) + 1));
  
  strcat(str2, str);
   char ** ch = split(str2, "," , p);
  for (i = 0;i < *p;++i) {
    char * s;
    TYPE t;

    col * newCol = (col *)calloc(1, sizeof(col));
    col * c = tb->rootCol;
    tb->rootCol = newCol;
    newCol->next = c;
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
      s = strrchr(ch[i], ' ');
      while (*s == ' '){
  	++s;
      }
      newCol->name = s;
    }
    else {
      t = None;
      newCol->name = ch[i];
    }
    newCol->type = t;
    ++(tb->colCnt);
  }
 
  return tb;
}
