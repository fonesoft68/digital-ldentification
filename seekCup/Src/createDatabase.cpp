#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql.h"

database * createDatabase(char * name)
{
  database * db = (database *)calloc(1, sizeof(database));
  
  if(db == NULL){
    printf("memory error\n");
    return NULL;
  }

  char *tmp_name = (char *) malloc (sizeof(char) * strlen(name) + 1);
  strcpy(tmp_name, name);

  if (!nameCheck(tmp_name)) {
	  printf(ERROR);
	  return 0;
  }

  db->name = (char *)malloc(sizeof(char) * (strlen(name) + 1));
  strcpy(db->name, name);
  db->next = allDatabaseRoot;
  allDatabaseRoot = db;
  ++ databaseCnt;
  printf("%s\n", name);
  return allDatabaseRoot;
}
