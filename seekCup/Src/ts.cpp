#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql.h"

int main()
{
  database * allDatabaseRoot = createDatabase("huzi");
  database *db = createDatabase("huzi");
  printf("%s %d\n",db->name, db->tableCnt);
  return 0;
}
