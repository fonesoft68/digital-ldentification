#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql.h"

#define DELETE "delete from"

int deleteCol(const char *command) {
  if (!nowUsedDatabase) {
    printf(ERROR);
    return 0;
  }
  
  int *p = (int *) calloc (1, sizeof(int));
  char *command_copy = (char *) calloc (1, sizeof(char) * (strlen(command) + 1));
  strcpy(command_copy, command);
  char **split_command = split(command_copy, DELETE, p);
  if (*p != 1) {
    printf(ERROR);
    return 0;
  }
  
}
