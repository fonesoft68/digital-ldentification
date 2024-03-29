#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sql.h"

#define WHERE "where "

#define EQUAL "=="
#define NOT_EQUAL "~="
#define GREATE_THAN ">"
#define LESS_THAN "<"
#define GREATE_THAN_EQUAL ">="
#define LESS_THAN_EQUEL "<="
#define BETWEEN " between"

int delete_parse(char *command)
{
	int *cnt = (int*) calloc (1, sizeof(int));
	char **split_command = split(command, WHERE, cnt);
	if (*cnt != 2) {
		printf(ERROR);
		return 0;
	}
	table *tmp_table = findTable(split_command[0]);
	char *where_condition = split_command[1];
	int *c = (int *) calloc (1, sizeof(int));
	char **split_c;
	char *table_name;
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
	int x;
	int i;
	for (i = colCnt; i > 0; -- i) {
		col *tmp_col = tmp_table->rootCol;
		for (x = 0; x < i; ++ x) {
			tmp_col = tmp_col->next;
		}
		int t = 0;
		for (j = index[0]; j > 0; -- j) {
			tmp_item = tmp_col->rootItem;
			for (x = 0; x < index[j]-1; ++ x) {
				tmp_item = tmp_item->next;
			}
			tmp_item->next = tmp_item->next->next;
		}
	}

	//showTableContext(findTable("person"));


	return 0;
}
