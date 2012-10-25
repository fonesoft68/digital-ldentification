#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sql.h"
#include "test.h"


int useDatabase(char *name)
{
	database *tmp_database = allDatabaseRoot;
	while (tmp_database != NULL) {
		if (strcmp(tmp_database->name, name) == 0) {
			nowUsedDatabase = tmp_database;
			printf("now used %s\n", nowUsedDatabase->name);
			return 0;
		}
		tmp_database = tmp_database->next;
	}
	
	return -1;
}
