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
  // table * tb = createTable("ab");
  //  table * tc = createTable("ac");
  if (argc > 1) {
    if (memcmp(argv[1], "createTable", strlen(argv[1])) == 0) {
	createTable(" int a , node b  ");
      }
    if (memcmp(argv[1], "drop", strlen(argv[1])) == 0) {
      printf("%d\n**************", drop(argv[2]));
      printf("argv[2] is %s", argv[2]);
    }
  }
}
