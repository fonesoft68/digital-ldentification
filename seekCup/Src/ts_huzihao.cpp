#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql.h"

database *nowUsedDatabase;
database *allDatabaseRoot;

int main(int argc, char *argv[])
{
  database * allDatabaseRoot = createDatabase("huzi");
  nowUsedDatabase = allDatabaseRoot;
  if (argc > 1) {
    if (memcmp(argv[1], "createTable", strlen(argv[1])) == 0) {
      allDatabaseRoot->rootTable = createTable(" int a , float b , noe  ");
      // printf("%s %d", allDatabaseRoot->rootTable->rootCol->name, allDatabaseRoot->rootTable->rootCol->type);
      // printf("%s %d", allDatabaseRoot->rootTable->rootCol->next->name, allDatabaseRoot->rootTable->rootCol->next->type);
      // printf("%s %d", allDatabaseRoot->rootTable->rootCol->next->next->name, allDatabaseRoot->rootTable->rootCol->next->next->type);
      //      printf("%d************\n", allDatabaseRoot->rootTable->colCnt);
      }
    if (memcmp(argv[1], "drop", strlen(argv[1])) == 0) {
      printf("%d\n**************", drop(argv[2]));
      printf("argv[2] is %s", argv[2]);
    }
  }
}
