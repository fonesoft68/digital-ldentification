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
  
  int * p = (int *)malloc(sizeof(int));
  char * str2 = (char *)malloc(sizeof(char) * (strlen(str) + 1));
  strcat(str2, str);
  printf("%s \n", str2 );
    char ** ch = split(str2, "," , p);
  //  printf("%d*************\n", *p);
  //  printf("%s %s\n", ch[0], ch[1]);
  // for (int i = 0;i < *p;++i){
  //   for (int j = 0;ch[i][j]!='\0';++j){
  //     printf("%c ", ch[i][j]);
  //   }
  //   printf("\n");
  // }
  // tb->name = (char *)malloc(sizeof(char) * (strlen(name) + 1));
  // strcpy(tb->name, name);

  // table * t = nowUsedDatabase->rootTable;
  // nowUsedDatabase->rootTable = tb;
  // tb->next = t;
 
  return tb;
}

  
