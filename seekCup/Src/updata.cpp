#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql.h"
#include "test.h"

#define WHERE "where"
#define ERROR "funckyou!\n"

#define EQUAL "=="
#define NOT_EQUAL "~="
#define GREATE_THAN ">"
#define LESS_THAN "<"
#define GREATE_THAN_EQUAL ">="
#define LESS_THAN_EQUEL "<="
#define BETWEEN " between"

int updata_parse(char *command)
{
	int *cnt = (int *) calloc (1, sizeof(int));
	char **split_command = split(command, " ", cnt);
	char *table_name = (char *) malloc (sizeof(char) * strlen(split_command[1]));
	strcpy(table_name, split_command[1]);

	int i;
	for (i = 0; i < *cnt; ++ i) {
		free(split_command[i]);
	}
	free(split_command);
	split_command = split(command, " set", cnt);
	if(*cnt!=2){
		printf(ERROR);
		return 0;
	}
	split_command = split(split_command[1], "=", cnt);
	char *column_set = split_command[0];
	split_command = split(split_command[1], "where ", cnt);
	char *value_set = split_command[0];
	split_command = split(command, "where ", cnt);
	char *where_condition = split_command[1];


	table *tmp_table = findTable(table_name);

#ifdef DEBUG
	printf("%s\n", column_set);
	printf("%s\n", value_set);
	printf("%s\n", where_condition);
#endif
	int *c = (int *) calloc (1, sizeof(int));
	char **split_c;
	split_c = split(where_condition, EQUAL, c);
	if (*c == 2) {
		table_name = split_c[0];
	}
	split_c = split(where_condition, NOT_EQUAL, c);
	if (*c == 2) {
		table_name = split_c[0];
	}
	split_c = split(where_condition, GREATE_THAN, c);
	if (*c == 2) {
		table_name = split_c[0];
	}
	split_c = split(where_condition, GREATE_THAN_EQUAL, c);
	if (*c == 2) {
		table_name = split_c[0];
	}
	split_c = split(where_condition, LESS_THAN, c);
	if (*c == 2) {
		table_name = split_c[0];
	}
	split_c = split(where_condition, LESS_THAN_EQUEL, c);
	if (*c == 2) {
		table_name = split_c[0];
	}
	split_c = split(where_condition, BETWEEN, c);
	if (*c == 2) {
		table_name = split_c[0];
	}

	col *tmp_col = tmp_table->rootCol->next;
	while (tmp_col) {
		if (strcmp(tmp_col->name, table_name) == 0) {
			break;
		}
		tmp_col = tmp_col->next;
	}
	if (!tmp_col) {
		printf(ERROR);
		return 0;
	}
	int *index = (int *) calloc (1, sizeof(int));
	index[0] = 0;
	item *tmp_item = tmp_col->rootItem->next;
	int cnt_1 = 0;
	while (tmp_item) {
		++ cnt_1;
		if (isSelect(tmp_col->type, tmp_item->res, where_condition) == 1) {
			++ index[0];
			index = (int *) realloc (index, (index[0] + 1) * sizeof(int));
			index[index[0]] = cnt_1;
		}
		tmp_item = tmp_item->next;
	}
	int j;
	int colCnt = 0;
	tmp_col = tmp_table->rootCol->next;
	while (tmp_col) {
		++ colCnt;
		tmp_col = tmp_col->next;
	}
	int *count = (int *) calloc (1, sizeof(int));
	int *cc  = (int *) calloc (1, sizeof(int));
	char **split_column = split(column_set, "(", count);
	split_column = split(split_column[0], ")", count);
	split_column = split(split_column[0], ",", count);
	char **split_value = split(value_set, "(", cc);
	split_value = split(split_value[0], ")", cc);
	split_value = split(split_value[0], ",", cc);
#ifdef DEBUG
	printf("**********%s %s*******\n", column_set, value_set);
#endif
	if (*cc != *count) {
#ifdef DUBUG
		printf("******%d  %d*************\n", *c, *count);
#endif
		return 0;
	}
	int x;
	for (i = colCnt; i > 0; -- i) {
		col *tmp_col = tmp_table->rootCol;
		for (x = 0; x < i; ++ x) {
			tmp_col = tmp_col->next;
		}
		int t = 0;
		for (t = 0; t < *count; ++ t) {
			if (strcmp(tmp_col->name, split_column[t]) == 0) {
				break;
			}
		}
		if (t == *count) {
			continue;
		}
		for (j = index[0]; j > 0; -- j) {
			tmp_item = tmp_col->rootItem;
			for (x = 0; x < index[j]; ++ x) {
				tmp_item = tmp_item->next;
			}
			if ((tmp_col->type == Int && isNum(split_value[t]))
					|| (tmp_col->type == Text && isText(split_value[t]))
					|| (tmp_col->type == Float && isFloat(split_value[t]))
					|| 1) {
				strcpy(tmp_item->res, split_value[t]);
			}
			else {
				printf(ERROR);
				return 0;
			}
		}
	}

	//showTableContext(tmp_table);
	return 0;
}

table *findTable(char *name)
{
	if(!nowUsedDatabase){
		return 0;
	}
	table *tmp_table = nowUsedDatabase->rootTable->next;
	while(tmp_table) {
		if (strcmp(tmp_table->name, name) == 0) {
			return tmp_table;
		}
		tmp_table = tmp_table->next;
	}
	return 0;
}


