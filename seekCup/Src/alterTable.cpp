#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql.h"
<<<<<<< HEAD
#include "test.h"

//int altertable(const char * str)
//{
//  int * p = (int *)malloc(sizeof(int));
//  char * s = (char *)malloc(sizeof(char) * (strlen(str) + 1));
//
//  strcat(s, str);
//  char ** ch = split(s, " ", p);
//  if(*p == 5);
//}
int alterAdd(char *table_name, char *datatpye)
{
	if (!nowUsedDatabase) {
		printf(ERROR);
		return 0;
	}

	table *tmp_table = nowUsedDatabase->rootTable;
	while (tmp_table) {
		if (strcmp(tmp_table->name, table_name) == 0) {
			break;
		}
		tmp_table = tmp_table->next;
	}
	if (!tmp_table) {
		printf(ERROR);
		return 0;
	}
	int *cnt = (int *) malloc (sizeof(int));
	char **split_datatype = split(datatpye, " ", cnt);
	if(*cnt != 1 || *cnt != 2) {
		printf(ERROR);
		return 0;
	}

	col *tmp_col = tmp_table->rootCol;
	while (tmp_col->next) {
		if (strcmp(tmp_col->name, split_datatype[0]) == 0) {
			printf(ERROR);
			return 0;
		}
		tmp_col = tmp_col->next;
	}
	if (strcmp(tmp_col->name, split_datatype[0]) == 0) {
		printf(ERROR);
		return 0;
	}
	int itemCnt = tmp_col->itemCnt;
	int i;
	item *rootItem = (item *) calloc (1, sizeof(item));
	rootItem->type = None;

	TYPE type = None;
	if (*cnt == 2) {
		if (strcmp(split_datatype[1], "int") == 0) {
			type = Int;
		}
		else if (strcmp(split_datatype[1], "float" == 0)) {
			type = Float;
		}
		else if (strcmp(split_datatype[1], "text") == 0) {
			type = Text;
		}
		else {
			printf(ERROR);
			return 0;
		}
	}

	for (i = 0; i < itemCnt; ++ i) {
		item *tmp_item = (item *) calloc (1, sizeof(item));
		tmp_item->type = type;
		tmp_item->next = rootItem;
		rootItem = tmp_item;
	}
	col *newCol = (col *) calloc (1, sizeof(col));
	newCol->name  = (char *) malloc (sizeof(char) * (strlen(split_datatype[0]) + 1));
	strcpy(newCol->name, split_datatype[0]);
	newCol->type = type;
	newCol->rootItem = rootItem;
	tmp_col->next = newCol;
	(tmp_table->colCnt) ++ ;

	return 0;
}


#define ALTER_TABLE "alter table "
#define ADD "add "
#define DROP "drop column "
#define ALTER_COLUMN "alter column "

int alter_parse(char *command)
{
	int *cnt = (int *) malloc (sizeof(int));
	char **split_command = split(command, ALTER_TABLE, cnt);
	if (*cnt != 1) {
		printf(ERROR);
		return 0;
	}

	static int *p_add = go(ADD);
	static int *p_drop = go(DROP);
	static int *p_alter_column = go(ALTER_TABLE);

	int *result_add = findString(split_command[0], ADD, p_add);
	int *result_drop = findString(split_command[0], DROP, p_drop);
	int *result_alter_column = findString(split_command[0], ALTER_TABLE, p_alter_column);

	int i;

	if (result_add[0] == 1) {
		char **name_datatype = split(split_command[0], ADD, cnt);
		if (*cnt == 2) {
			alterAdd(name_datatype[0], name_datatype[1]);
			free(name_datatype[0]);
			free(name_datatype[1]);
			free(name_datatype);
		}
		else {
			for (i = 0; i < *cnt; ++ i) {
				free(name_datatype[i]);
			}
			free(name_datatype);
		}
#ifdef DEBUG
		printf("$alter add :$\n");
#endif
	}



	return 0;
=======

int altertable(const char * str)
{
  int * p = (int *)malloc(sizeof(int));
  char * s = (char *)malloc(sizeof(char) * (strlen(str) + 1));
  
  strcat(s, str);
  char ** ch = split(s, " ", p);
  if(*p == 5);
>>>>>>> ee5c4b6288fc5d05301f428f8b82622be18c00ac
}
