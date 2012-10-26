#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql.h"

database * createDatabase(char * name)
{
  database * db = (database *)calloc(1, sizeof(database));
  
  item *rootItem = (item *) calloc (1, sizeof(item));
  col *rootCol = (col *) calloc (1, sizeof(col));
  rootCol->rootItem = rootItem;
  table *rootTable = (table *) calloc (1, sizeof(table));
  rootTable->rootCol = rootCol;

  
  if(db == NULL){
    printf("memory error\n");
    return NULL;
  }


  if (!nameCheck(name)) {
	  printf(ERROR);
	  return 0;
  }

  database *tmp_database = allDatabaseRoot;
  while (tmp_database) {
    if (!tmp_database->name) {
      break;
    }
	  if (strcmp(tmp_database->name, name) == 0) {
		  printf(ERROR);
		  return 0;
	  }
	  tmp_database = tmp_database->next;
  }

  db->name = (char *)malloc(sizeof(char) * (strlen(name) + 1));
  db->rootTable = rootTable;
  strcpy(db->name, name);
  db->next = allDatabaseRoot;
  allDatabaseRoot = db;
  ++ databaseCnt;
  return allDatabaseRoot;
}
