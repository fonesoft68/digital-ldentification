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
			showDatabase();
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
				showTableName(split_command[1]);
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

int printItem(item *i)
{
	switch(i->type) {
		case Int : {
						int *tmp_int = (int *) calloc (1, sizeof(int));
						memcpy(tmp_int, i->res, sizeof(int));
						printf("%d,", *tmp_int);
				   };break;
		case Float : {
						 float *tmp_float = (float *) calloc (1, sizeof(float));
						 memcpy(tmp_float, i->res, sizeof(float));
						 printf("%f,", *tmp_float);
	   				};break;
		case Text : {
						printf("%s,", i->res);
					};break;
		case None : {
						printf("#,");
					};break;
		default : {
					  printf(ERROR);
				  };
	}
	return 0;
}

int showItem(item *i)
{
	if (i->next) {
		showItem(i->next);
	}
	printItem(i);
	return 0;
}

int showCol(char *n)
{
	return 0;
}

int showTable(table *t)
{
	int rowCnt = 0;
	int colCnt = 0;
	col *tmp_col = t->rootCol->next;
	while (tmp_col) {
		++ colCnt;
		tmp_col = tmp_col->next;
	}
	item *tmp_item = t->rootCol->next->rootItem->next;
	while(tmp_item) {
		++ rowCnt;
		tmp_item = tmp_item->next;
	}

	int i,j;
	int r,c;
	for (i = rowCnt; i > 0; -- i) {
		for (j = colCnt; j > 0; -- j) {
			col *tmp_col = t->rootCol;
			for (r = 0; r < j; ++ r) {
				tmp_col = tmp_col->next;
			}
			item *tmp_item = tmp_col->rootItem;
			for (c = 0; c < i; ++ c) {
				tmp_item = tmp_item->next;
			}
			printItem(tmp_item);
		}
		printf("\b ");
		printf("\n");
	}
	
	return 0;
}

int showColName(col *c)
{
	if (c->next) {
		showColName(c->next);
	}
	printf("%s,", c->name);

	return 0;
}

int showTableN(char *tableName)
{
	if (!nowUsedDatabase) {
		printf(ERROR);
		return 0;
	}

	table *tmp_table = nowUsedDatabase->rootTable;
	while (tmp_table) {
		if (strcmp(tmp_table->name, tableName) == 0) {
			break;
		}
		tmp_table = tmp_table->next;
	}
	if (!tmp_table) {
		printf(ERROR);
		return 0;
	}

	col *tmp_col = tmp_table->rootCol;

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
