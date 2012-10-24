#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql.h"

int main(int argc, char *argv[])
{
  
  database *nowUsedDatabase = (database *)calloc(1, sizeof(database));
  database *allDatabaseRoot = (database *)calloc(1, sizeof(database));
  allDatabaseRoot->next = NULL;
  createDatabase("huzi");
  // while  (allDatabaseRoot) {
  //   printf("\n%s\n", allDatabaseRoot->name);
  //   allDatabaseRoot = allDatabaseRoot->next;
  // }

  // nowUsedDatabase = allDatabaseRoot;
  // drop("drop huzi");
  // printf("%s ***\n", allDatabaseRoot->name);
  // if (argc > 1) {
  //   if (memcpy(argv[1], "drop", strlen(argv[1])) == 0) {
  //     //    drop("huzi");
  //     printf("%p ***\n", allDatabaseRoot);
  //   }
  //   if (memcmp(argv[1], "createTable", strlen(argv[1])) == 0) {
  //     //allDatabaseRoot->rootTable = createTable(" int a , float b , noe  ");
  //   }
  // }
}
