#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql.h"

table * createTable(char * name)
{
  table * tb = (table *)calloc(1, sizeof(table));
  
  if(tb == NULL){
    printf("memory error\n");
    return NULL;
  }
  
  tb->name = (char *)malloc(sizeof(char) * (strlen(name) + 1));
  strcpy(tb->name, name);

  table * t = nowUsedDatabase->rootTable;
  nowUsedDatabase->rootTable = tb;
  tb->next = t;
 
  return tb;
}
