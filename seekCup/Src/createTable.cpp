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
  
  if (!nameCheck(str)) {
	  printf(ERROR);
	  return 0;
  }
  
  table *tmp_table = allDatabaseRoot->rootTable->next;
  while (tmp_table) {
    if (!tmp_table->name) {
      break;
    }
	  if (strcmp(tmp_table->name, str) == 0) {
		  printf(ERROR);
		  return 0;
	  }
	  tmp_table = tmp_table->next;
  }


  int i, j;
  int * p = (int *)calloc(1, sizeof(int));
  char * str2 = (char *)calloc(1, sizeof(char) * (strlen(str) + 1));
  
  strcpy(str2, str);
  char ** ch = split(str2, "," , p);
  for (i = 0;i < *p;++ i) {
    int *q = (int *) calloc (1, sizeof(int));
    char **blank = split(ch[i], " ", q);
    if (*q > 2) {
      return 0;
    }
    char c[256];
    sscanf(ch[i], "%s", c);
    if ((strstr(ch[i], "int") && strcmp(c, "int")) || (strstr(ch[i], "float") && strcmp(c, "float")) || (strstr(ch[i], "text") && strcmp(c, "text")) || (!strstr(ch[i], " "))) ;
    else {
      return 0;
    }
  }
  for (i = 0;i < *p;++i) {
	item *rootItem = (item *) calloc (1, sizeof(item));
	rootItem->res = (char *) calloc (256, sizeof(item));
    TYPE t;
    char s[256];
    col * newCol = (col *)calloc(1, sizeof(col));
    sscanf(ch[i], "%s", s);
    newCol->next = tb->rootCol->next;
    tb->rootCol->next = newCol;
    newCol->name = (char *)calloc(1, sizeof(char) * 256);
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
	return 0;
      }
    }
    else {
      t = None;
    }
    newCol->type = t;
	rootItem->type = t;
    ++(tb->colCnt);
  }
  ++ (nowUsedDatabase->tableCnt);
  return tb;
}
