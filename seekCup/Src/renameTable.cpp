#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql.h"

int renameTable(char *old_name, char *new_name)
{
	if (!nowUsedDatabase) {
		printf(ERROR);
		return 0;
	}
	table *tmp_table = nowUsedDatabase->rootTable->next;
	while (tmp_table) {
		if (strcmp(tmp_table->name, old_name) == 0) {
			break;
		}
	}
	if (!tmp_table) {
		printf(ERROR);
		return 0;
	}

	tmp_table->name = (char *) realloc (tmp_table->name, strlen(new_name) + 1);
	strcpy(tmp_table->name, new_name);

	return 0;
}
