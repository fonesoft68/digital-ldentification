#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql.h"
#include "test.h"

#define WHERE "where"

int parse_updata(char *command)
{
	char *command_cpy = (char *) malloc (sizeof(char) * strlen(command));
	strcpy(command_cpy, command);
	toLowCase(command);
	int *cnt = (int *) calloc (1, sizeof(int));
	char **split_command = split(command, " ", cnt);
	char *table_name = (char *) malloc (sizeof(char) * strlen(split_command[1]));
	strcpy(table_name, split_command[1]);

	int i;
	for (i = 0; i < *cnt; ++ i) {
		free(split_command[i]);
	}
	free(split_command);
	free(cnt);

	int *p_left_bracket = go("(");
	int *p_right_bracket = go(")");
	int *left_bracket = findString(command, "(", p_left_bracket);
	int *rigth_bracke = findString(command, ")", p_right_bracket);
	free(p_left_bracket);
	free(p_right_bracket);

	if (left_bracket[0] != 2 || rigth_bracke[0] != 2) {

		return 0;
	}

	int size_col_str = rigth_bracke[1] - left_bracket[1] + 1;
	char *col_str = (char *) calloc (size_col_str + 1, sizeof(char));
	for (i = 0; i < size_col_str; ++ i) {
		col_str[i] = command_cpy[i + left_bracket[1]];
	}
	int size_val_str = rigth_bracke[2] - left_bracket[2] + 1;
	char *val_str = (char *) calloc (size_val_str + 1, sizeof(char));
	for (i = 0; i < size_val_str; ++ i) {
		val_str[i] = command_cpy[left_bracket[2] + i];
	}

	split_command = split(command, WHERE, cnt);
	if (*cnt != 2) {
		return 0;
	}


	return 0;
}
