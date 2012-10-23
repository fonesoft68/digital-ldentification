#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql.h"

database * createDatebase(char * name)
{
  database * db = (database *)calloc(1, sizeof(database));

  strcpy(db->name, name);
  
  return db;
}
