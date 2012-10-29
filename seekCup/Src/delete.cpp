#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sql.h"

#define WHERE "where "

int delete_parse(char *command)
{
	int *cnt = (int*) calloc (1, sizeof(int));
	char **split_c = split(command, WHERE, cnt);
	if (*cnt != 2) {
		printf(ERROR);
		return 0;
	}
	table *tmp_table = findTable(split_c[0]);



	return 0;
}
