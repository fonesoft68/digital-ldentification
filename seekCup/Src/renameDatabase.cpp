#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql.h"

int renameDatabase(char * name)
{
  strcpy(nowUsedDatabase->name, name);

  return 0;
}
