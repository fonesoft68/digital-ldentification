#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sql.h"

#define DEBUG

#define CREATE_DATABASE "create database "
#define CREATE_TABLE "create table "
#define ALTER_TABLE "alter table "
#define TRUNCATE_TABLE "truncate table "
#define USE "use "
#define DROP "drop "
#define RENAME_TABLE "rename table "
#define RENAME_DATABASE "rename database "
#define SELECT "select "
#define UPDATA "updata "
#define DELETE "delete "
#define INSERT_INTO "insert into "
#define SHOW "show "

int parseCommand(char * command)
{

	char *command_cpy = (char *) malloc (sizeof(char) * strlen(command) + sizeof(char));
	memcpy(command_cpy, command, strlen(command));
	toLowCase(command);
#ifdef DEBUG
	printf("%s\n", command);
#endif


	static int *p_create_database = go(CREATE_DATABASE);
	static int *p_create_table = go(CREATE_TABLE);
	static int *p_alter_table = go(ALTER_TABLE);
	static int *p_truncate_table = go(TRUNCATE_TABLE);
	static int *p_use = go(USE);
	static int *p_drop = go(DROP);
	static int *p_rename_table = go(RENAME_TABLE);
	static int *p_rename_database = go(RENAME_DATABASE);
	static int *p_select = go(SELECT);
	static int *p_updata = go(UPDATA);
	static int *p_delete = go(DELETE);
	static int *p_insert_into = go(INSERT_INTO);
	static int *p_show = go(SHOW);

	int *result_create_database = findString(command, CREATE_DATABASE, p_create_database);
	int *result_create_table = findString(command, CREATE_TABLE, p_create_table);
	int *result_alter_table = findString(command, ALTER_TABLE, p_alter_table);
	int *result_truncate_table = findString(command, TRUNCATE_TABLE, p_truncate_table);
	int *result_use = findString(command, USE, p_use);
	int *result_drop = findString(command, DROP, p_drop);
	int *result_rename_table = findString(command, RENAME_TABLE, p_rename_table);
	int *result_rename_database = findString(command, RENAME_DATABASE, p_rename_database);
	int *result_select = findString(command, SELECT, p_select);
	int *result_updata = findString(command, UPDATA, p_updata);
	int *result_delete = findString(command, DELETE, p_delete);
	int *result_insert_into = findString(command, INSERT_INTO, p_insert_into);
	int *result_show = findString(command, SHOW, p_show);

	int i;
	int *cnt = (int *)malloc(sizeof(int));
	char **split_command;
	int begin_black = 0;
	int command_len = strlen(command);
	while (begin_black < command_len && (command[begin_black] == ' ' || command[begin_black] == '\t')) {
		++ begin_black;
	}

	if (result_create_database[0] == 1 && result_create_database[1] == begin_black) {
#ifdef DEBUG
		printf("$create database:%s$\n", command_cpy);
#endif
		split_command = split(command, CREATE_DATABASE, cnt);
		if  (*cnt == 1) {
			createDatabase(split_command[0]);
		}
		else {
			for (i = 0; i < *cnt; ++ i) {
				free(split_command[i]);
			}
			free(split_command);
			printf(ERROR);
			return 0;
		}
		free(split_command[0]);
		free(split_command);
		showDatabase();
		return 0;

	}
	if (result_create_table[0] == 1 && result_create_table[1] == begin_black) {
#ifdef DEBUG
		printf("$create table:%s$\n", command_cpy);
#endif
		split_command = split(command, CREATE_TABLE, cnt);
		if (*cnt == 1) {
			char **name_val = split(split_command[0], "(", cnt);
			if (*cnt == 2) {
				name_val[1][strlen(name_val[1]) - 1] = '\0';
				printf("%s\n %s\n", name_val[0], name_val[1]);
			}
			else {
				printf(ERROR);
			}
		}
		else {
			printf(ERROR);
		}

	}
	if (result_alter_table[0] == 1 && result_alter_table[1] == begin_black) {
#ifdef DEBUG
		printf("$alter table:%s$\n", command_cpy);
#endif
		alter_parse(command);
	}
	if (result_truncate_table[0] == 1) {
		printf("$truncate table:%s$\n", command_cpy);
	}
	if (result_use[0] == 1 && result_use[1] == begin_black) {
#ifdef DEBUG
		printf("$use:%s$\n", command_cpy);
#endif
		split_command = split(command, USE, cnt);
		if (*cnt == 1) {
			useDatabase(split_command[0]);
		}
		else {
			for (i = 0; i < *cnt; ++ i) {
				free(split_command[i]);
			}
			free(split_command);
			printf(ERROR);
			return 0;
		}
		free(split_command[0]);
		free(split_command);
		return 0;
	}
	if (result_drop[0] == 1) {
		printf("$drop:%s$\n", command_cpy);
	}
	if (result_rename_table[0] == 1) {
		printf("$rename table:%s$\n", command_cpy);
	}
	if (result_rename_database[0] == 1) {
		printf("$rename database:%s$\n", command_cpy);
	}
	if (result_select[0] == 1) {
		printf("$select:%s$\n", command_cpy);
	}
	if (result_updata[0] == 1) {
		printf("$updata:%s$\n", command_cpy);
	}
	if (result_delete[0] == 1) {
		printf("$delete:%s$\n", command_cpy);
	}
	if (result_insert_into[0] == 1) {
		printf("$insert into:%s$\n", command_cpy);
	}
	if (result_show[0] == 1) {
		printf("$show:%s$\n", command);
	}

	return 0;
}


int string_cut(char **str)
{
	int n = strlen(*str);
	int i = 0;
	int j = n - 1;
	int cnt = 0;

	while ((*str)[i] == ' ' && i <= j) {
		++ i;
	}
	while ((*str)[j] == ' ' && i <= j) {
		-- j;
	}

	int size = j - i + 1;
	if (size == 0) {
		return -1;
	}

	char *tmp = (char *) malloc (sizeof(char) * (size + 1));
	memset(tmp, 0, sizeof(char) * (size + 1));

	for (; i <= j; ++ i) {
		tmp[cnt] = (*str)[i];
		++ cnt;
	}

	*str = tmp;

	return 0;
}


char ** split(char *str, char *split, int *cnt)
{
	*cnt = 0;
	if (str == NULL) {
		return NULL;
	}
	else {
		for (int i = 0; i < strlen(str); ++ i) {
			if (str[i] == '\n') {
				str[i] = ' ';
			}
		}
	}

	if (split == NULL) {
		split = " ";
	}

	char **result;
	int *p = go(split);
	int *sp = findString(str, split, p);
	int i,j,k;

	result = (char **) malloc (sizeof(char *) * sp[0] + 1);

	int begin = 0;
	char *tmp_str;
	int size_tmp_str;
	int split_num = 0;
	int word_len = 0;
	for (i = 0; i < sp[0]; ++ i) {
		size_tmp_str = sp[i + 1] - begin + 1;
		if (size_tmp_str < 1) {
			begin = sp[i + 1] + strlen(split);
			continue;
		}
		tmp_str = (char *) malloc (sizeof(char) * size_tmp_str);
		word_len = 0;
		for (j = begin; j < sp[i + 1]; ++ j) {
			if (str[j] != '\n') {
				tmp_str[word_len] = str[j];
				++ word_len;
			}
			else{
				tmp_str[word_len] = ' ';
				++ word_len;
			}
		}
		tmp_str[word_len] = '\0';
		if (tmp_str == NULL || word_len == 0) {
			begin = sp[i + 1] + strlen(split);
			continue;
		}
		for (k = 0; k < strlen(tmp_str); ++ k) {
			if (tmp_str[k] != ' '){
				break;
			}
		}
		if (k == strlen(tmp_str)) {
			begin = sp[i + 1] + strlen(split);
			continue;
		}
		if (!string_cut(&tmp_str)) {
			result[split_num] = tmp_str;
			++ split_num;
			++ (*cnt);
		}

		begin = sp[i + 1] + strlen(split);
	}

	if (begin  < strlen(str)) {
		size_tmp_str = strlen(str) - begin + 1;
		if (size_tmp_str < 1) {
			return result;
		}
		word_len = 0;
		tmp_str= (char *) malloc (sizeof(char) * size_tmp_str);
		for (j = 0; j < size_tmp_str - 1; ++ j) {
			if (str[j + begin] != '\n') {
				tmp_str[word_len] = str[j + begin];
				++ word_len;
			}
			else {
				tmp_str[word_len] = ' ';
				++ word_len;
			}
		}
		tmp_str[word_len] = '\0';
		if (tmp_str == NULL || word_len == 0) {
			return result;
		}
		for (k = 0; k < strlen(tmp_str); ++ k) {
			if (tmp_str[k] != ' '){
				break;
			}
		}
		if (k == strlen(tmp_str)) {
			return result;
		}
		if (!string_cut(&tmp_str)) {
			result[split_num] = tmp_str;
			++ split_num;
			++ (*cnt);
		}
	}

	return result;
}
