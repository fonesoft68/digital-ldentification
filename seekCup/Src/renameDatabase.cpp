#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql.h"

int renameDatabase(char * oldName, char *newName)
{
	database *tmp_database = allDatabaseRoot;
	while (tmp_database) {
		if (strcmp(tmp_database->name, oldName) == 0) {
			strcpy(tmp_database->name, newName);
			return 0;
		}
		tmp_database = tmp_database->next;
	}

	return -1;
}
