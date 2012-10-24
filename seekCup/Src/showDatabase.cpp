#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sql.h"

int showDadabase(char *name)
{
	table *tmp_table;
	if (name == NULL) {
		tmp_table = nowUsedDatabase->rootTable;
		if (tmp_table == NULL) {
			printf("$\n");
		}
		while (tmp_table != NULL) {
			printf("%s", tmp_table->name);
			tmp_table = tmp_table->next;
			if (tmp_table != NULL) {
				printf(",");
			}
			else {
				printf("\n");
			}
		}

	}
	else {
		database *tmp_database = allDatabaseRoot;
		if (tmp_database == NULL) {
			printf("$\n");
		}

		while (tmp_database != NULL) {
			if (strcmp(tmp_database->name, name) == 0) {
				break;
			}
			tmp_database = tmp_database->next;
		}

		tmp_table = tmp_database->rootTable;
		if(tmp_table == NULL) {
			printf("%$\n");
		}
		while (tmp_table != NULL) {
			printf("%s", tmp_table->name);
		}
	}

	return 0;
}
