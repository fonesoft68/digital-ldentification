#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql.h"

table * createTable(char * str)
{
  table * tb = (table *)calloc(1, sizeof(table));
  col *rootCol = (col *) calloc (1, sizeof(col));
  tb->rootCol = rootCol;
  
  if(tb == NULL){
    printf(ERROR);
    return NULL;
  }
  if (!nowUsedDatabase) {
	  printf(ERROR);
	  return 0;
  }
  
<<<<<<< HEAD
  if (!nameCheck(str)) {
	  printf(ERROR);
	  return 0;
  }
  
  table *tmp_table = nowUsedDatabase->rootTable->next;
=======
  table *tmp_table = allDatabaseRoot->rootTable->next;
>>>>>>> 788c3b3e5f2e10deb1362e06a99ac9c0c952efc0
  while (tmp_table) {
	  if (strcmp(tmp_table->name, str) == 0) {
		  printf(ERROR);
		  return 0;
	  }
	  tmp_table = tmp_table->next;
  }


  int i, j;
  int * p = (int *)malloc(sizeof(int));
  char * str2 = (char *)malloc(sizeof(char) * (strlen(str) + 1));
  
  strcpy(str2, str);
   char ** ch = split(str2, "," , p);
  for (i = 0;i < *p;++i) {
	item *rootItem = (item *) calloc (1, sizeof(item));
	rootItem->res = (char *) calloc (256, sizeof(item));
    TYPE t;
    char s[256];
    col * newCol = (col *)calloc(1, sizeof(col));
    sscanf(ch[i], "%s", s);
    newCol->next = tb->rootCol->next;
    tb->rootCol->next = newCol;
    newCol->name = (char *)malloc(sizeof(char) * 256);
	newCol->rootItem = rootItem;
    strcpy(newCol->name, s);
    if (strrchr(ch[i], ' ')) {
      if (strstr(ch[i], "int")) {
  	t = Int;
      }
      else if (strstr(ch[i], "float")) {
  	t = Float;
      }
      else if (strstr(ch[i], "text")) {
  	t = Text;
      }
      else {
	printf(ERROR);
      }
    }
    else {
      t = None;
    }
    newCol->type = t;
	rootItem->type = t;
    ++(tb->colCnt);
  }
 
  return tb;
}
