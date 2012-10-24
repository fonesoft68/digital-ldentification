#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql.h"

database *nowUsedDatabase;
database *allDatabaseRoot;

int main(int argc, char *argv[])
{
  database * allDatabaseRoot = createDatabase("huzi");
  database *db = createDatabase("huzi");
  nowUsedDatabase = db;
  table * tb = createTable("ab");
  table * tc = createTable("ac");
  if (argc > 1) {
    if (memcmp(argv[1], "drop", strlen(argv[1])) == 0) {
      drop(argv[2]);
    }
    if (memcmp(argv[1], "kmp", strlen(argv[1])) == 0) {
      char *queryString;
      char *moduleString;
      queryString = (char *) calloc (100, sizeof(char));
      moduleString = (char *) calloc (10, sizeof(char));
      strcat(queryString, "select nimei selectselectsdfa safj selctsjadfkjl slectsdf slectasdfjlkajsdklfa selects");
      strcat(moduleString, "selects");

      int *p = go(moduleString);
			
      int *result = findString(queryString, moduleString, p);

      printf("%s\n ", queryString);
      printf("%s\n", moduleString);
      int i;
      printf("match for %d (s)\n", result[0]);
      for (i = 0; i < result[0]; ++ i) {
	printf("%d ", result[i + 1]);
      }
    }
    if (memcmp(argv[1], "toLowCase", strlen(argv[1])) == 0) {
      char *str = (char *)malloc (sizeof(char) * 100);
      scanf("%s", str);
      toLowCase(str);
      printf("%s\n", str);
    }
  }
  //  printf("%s %d\n", db->name, db->tableCnt);
  return 0;
}
