#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql.h"

database * createDatabase(const char * name)
{
  database * db = (database *)calloc(1, sizeof(database));
  
  if(db == NULL){
    printf("memory error\n");
    return NULL;
  }

  db->name = (char *)malloc(sizeof(char) * (strlen(name) + 1));
  strcpy(db->name, name);
  db->next = allDatabaseRoot;
  allDatabaseRoot = db;
  return db;
}
