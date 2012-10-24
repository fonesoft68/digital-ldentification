#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql.h"
#include "test.h"

#define DATABASE "database"
#define TABLE "table"
#define SHOW "show"
#define COLUMN "column"
#define ORDER "order"
#define BY "by"
#define DESC "desc"
#define INCR "incr"


int show_parse(char *command)
{
	int *cnt = (int *) calloc (1, sizeof(int));
	char **split_command = split(command, " ", cnt);
	if (strcmp(split_command[0], SHOW) == 0 && strcmp(split_command[1], DATABASE) == 0) {
		if (*cnt == 2) {
			showDatabase(NULL);
		}
	}
	else if (strcmp(split_command[0], SHOW) == 0 && strcmp(split_command[1], TABLE) == 0) {
		if (*cnt == 2) {
			showTable(NULL);
		}
	}
	else if (strcmp(split_command[0], SHOW) == 0 && strcmp(split_command[2], TABLE) == 0) {
		if (nameCheck(split_command[1])) {
			if (*cnt == 3) {
				showTable(split_command[1]);
			}
			else if (*cnt == 6 && strcmp(split_command[3], ORDER) == 0 && strcmp(split_command[4], BY) == 0) {
				if (strcmp(split_command[5], DESC) == 0) {
				}
				else if (strcmp(split_command[5], INCR) == 0) {
				}
			}
		}
	}
	else if (strcmp(split_command[0], SHOW) == 0 && strcmp(split_command[2], COLUMN) == 0) {
		if (nameCheck(split_command[1])) {
			if (*cnt == 3) {
				showCol(split_command[1]);
			}
			else if (*cnt == 6 && strcmp(split_command[3], ORDER) == 0 && strcmp(split_command[4], BY) == 0) {
				if (strcmp(split_command[5], DESC) == 0) {
				}
				else if (strcmp(split_command[5], INCR) == 0) {
				}
			}
		}
	}

	return 0;
}

int showTable(char *databaseName) 
{
	return 0;
}

int showCol(char *tableName)
{
	return 0;
}

int nameCheck(char *name) 
{
	char key_word[][50] = {"create", "database", "table", "column", "int", "float", "text", "like", "between", "and", "or", "alter", "add", "use", "truncate", "drop", "rename", "select", "updata", "delete", "show", "by", "desc", "order", "incr", "set"};
   
	int i;
	for (i = 0; i < 26; ++ i) {
		if (strcmp(key_word[i], name) == 0) {
			return 0;
		}
	}

	return 1;
}
