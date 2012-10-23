#include <stdio.h>
#include <stdlib.h>
#include <string.h>
<<<<<<< HEAD
#include "sql.h"

database * createDatebase(char * name)
{
  database * db = (database *)calloc(1, sizeof(database));

  strcpy(db->name, name);
  
  return db;
}
=======
#include "sql.h" 



database * creatDatabase(char *databaseName)
{

}


>>>>>>> 835d84a710f09c926d2afb41c343e2a0ed1635ac
