#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql.h"

database * createDatebase(const char * name)
{
  database * db = (database *)calloc(1, sizeof(database));
  
  if(db == NULL){
    printf("memory error\n");
    return NULL;
  }

  strcpy(db->name, name);
  
  return db;
}
