#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql.h"

int main()
{
  database *db = createDataBase("huzi");
  printf("%s %d\n",db->name, db->tableCnt);
  return 0;
}
