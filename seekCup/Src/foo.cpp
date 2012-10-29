#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sql.h"

//kmp失效函数
int* go(char *module)
{
	int m = strlen(module);
	int i;

	int *p = (int *) malloc (sizeof(int) * m);
	memset(p, 0, sizeof(p));
	p[0] = -1;
	int j = -1;
	
	for (i = 1; i < m; ++ i) {
		while (j > -1 && module[j + 1] != module[i]) {
			j = p[j];
		}

		if (module[j + 1] == module[i]) {
			++ j;
		}
		p[i] = j;
	}

	return p;
}

//kmp字符串查找算法
int * findString(char *query, char *module, int *go)
{
	int *res = (int *) malloc (sizeof(int));

	int j = -1;
	int i;
	int m = strlen(module);
	int n = strlen(query);
	int cnt = 0;

#ifdef EBUG
	for (i = 0; i < m; ++ i)
	{
		printf("%d ", go[i]);
	}
#endif

	for (i = 0; i < n; ++ i) {
		while (j > -1 && module[j + 1] != query[i]) {
			j = go[j];
		}

		if (module[j + 1] == query[i]) {
			j ++;
		}

		if (j == m - 1) {
			res = (int *) realloc(res, sizeof(int) * (++ cnt + 1));
			res[cnt] = i - m + 1;
			j = -1;
		}
	}
	res[0] = cnt;

	return res;
}

int toLowCase(char *str)
{
	int left = 0;
	int right = strlen(str) - 1;
	while  (left < right && str[left]==' ') ++ left;
	while (right > left && str[right]==' ') --right;
	for (int i = left; i <= right; ++ i) {
		str[i - left] = str[i];
	}
	str[right - left + 1] = '\0';
	int i;
	char *str_cpy = (char *) calloc (strlen(str) + 1, sizeof(char));
	int cnt = -1;
	for (i = 0; i < strlen(str); ++ i) {
		if (str[i] <= 'Z' && str[i] >= 'A') {
			str_cpy[++cnt] = (char) ('a' + str[i] - 'A');
		}
		else if (str[i] == ' ') {
			str_cpy[++cnt] = ' '; 
			while (i + 1 < strlen(str) && str[i + 1] == ' ') {
				++ i;
			}
		}
		else if (str[i] == '\'') {
			str_cpy[++cnt] = '\'';
			++ i;
			while (i < strlen(str) && str[i] != '\'') {
				str_cpy[++cnt] = str[i];
				++ i;
			}
			if (i >= strlen(str)) {
				printf(ERROR);
				return 0;
			}
			str_cpy[++cnt] = '\'';
		}
		else{
			str_cpy[++cnt] = str[i];
		}
	}
	str_cpy[++cnt] = '\0';
	strcpy(str, str_cpy);

	return 0;
}

int min(int a, int b){
	return a > b ? b : a;
}

int strCmp(char *str_1, char *str_2)
{
	int len_1 = strlen(str_1);
	int len_2 = strlen(str_2);
	int len = min(len_1, len_2);
	int i;
	for (i = 0; i < len; ++ i) {
		if (str_1[i] != str_2[i]) {
			return str_1[i] - str_2[i];
		}
	}
	if (len_1 == len_2) {
		return 0;
	}
	else if (len_1 < len_2) {
		return -1;
	}
	else {
		return 1;
	}
}

int isNum(char *str)
{
	int i;
	for (i = 0; i < strlen(str); ++ i) {
		if (str[i] < '0' || str[i] > '9') {
			return 0;
		}
	}
	return 1;
}

int isFloat(char *str)
{
	int i;
	for (i = 0; i < strlen(str); ++ i) {
	  if ((str[i] < '0' || str[i] > '9') && str[i] != '.') {
			return 0;
		}
	}
	return 1;
}
int isText(char *str)
{
  int i, x = 0 ,y = 0, z = 0, flag1 = 1, flag2 = 1, flag3 = 1;
  if (str[0] != '\'' || str[strlen(str) - 1] != '\'') {
    return 0;
  }
  for (i = 1;i < strlen(str) - 1;++ i) {
    if ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_' || str[i] == ' ') {
      if (flag1 && ((str[i] >= '0' && str[i] <= '9'))) {
	flag1 = 0;
	x = i;
	continue;
      }
      if (flag2 && ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))) {
	flag2 = 0;
	y = i;
	continue;
      }
      if (flag3 && str[i] == '_') {
	flag3 = 0;
	z = i;
	continue;
      }
    }
    else {
      return 0;
    }
  }
  if (x < y && x < z) {
    return 0;
  }
  char *tmp_str = (char *) calloc (strlen(str) - 1, sizeof(char));
  for (int i = 1;i < strlen(str) - 1;++ i) {
    tmp_str[i - 1] = str[i];
  }
  strcpy(str, tmp_str);
  return 1;
}

// int isText(char *str)
// {
// 	int i;
// 	if (str[0] != '\'' || str[strlen(str) - 1] != '\'') {
// 		return 0;
// 	}
// 	for (i = 1; i < strlen(str) - 1; ++ i) {
// 		if (!(str[i] >= 'a' && str[i] <= 'z') || !(str[i] >= 'A' && str[i] <= 'Z') || str[i] != '_' || str[i] != ' ') {
// 			return 0;
// 		}
// 	}
// 	char *tmp_str = (char *) calloc (strlen(str) - 1, sizeof(char));
// 	for (int i = 1; i < strlen(str) - 1; ++ i) {
// 		tmp_str[i - 1] = str[i];
// 	}
// 	strcpy(str, tmp_str);
// 	return 1;
// }

//char *getRes(TYPE type, char *str)
//{
//	char *val;
//	if (type == Int && isNum(str)) {
//		val = (char *) calloc (4, sizeof(char));
//		int tmp_i;
//		sscanf(str, "%d", &tmp_i);
//		memcpy(val, &tmp_i, sizeof(int));
//	}
//	else if (type == Float && isFloat(str)) {
//		val = (char *) calloc (4, sizeof(char));
//		float tmp_f;
//		sscanf(str, "%s", &tmp_f);
//		memcpy(val, &tmp_f, sizeof(float));
//	}
//	else if (type == Text && isText(str)) {
//		val = (char *) calloc (strlen(str) - 1, sizeof(char));
//		strcpy(val, str);
//	}
//	else {
//		return 0;
//	}
//	return val;
//}

//char resCmp(TYPE type, char *res_1, char *res_2)
//{
//	if (type == Int) {
//		int tmp_1 = 0, tmp_2 = 0;
//		memcpy(&tmp_1, res_1, sizeof(int));
//		memcpy(&tmp_2, res_2, sizeof(int));
//		return tmp_1 - tmp_2;
//	}
//	if (type == Float) {
//		float tmp_1 = 0;
//		float tmp_2 = 0;
//		memcpy(&tmp_1, res_1, sizeof(float));
//		memcpy(&tmp_2, res_2, sizeof(float));
//		return tmp_1 - tmp_2;
//	}
//	if (type == Text) {
//		return strCmp(res_1, res_2);
//	}
//}
//
int resCmp(TYPE type, char *a, char *b)
{
	if(type == Int) {
		int a_i;
		int b_i;
		sscanf(a, "%d", &a_i);
		sscanf(b, "%d", &b_i);
		return a_i - b_i;
	}
	if (type == Float) {
		float a_i;
		float b_i;
		sscanf(a, "%f", &a_i);
		sscanf(b, "%f", &b_i);
		return a_i - b_i;
	}
	if (type = Text) {
		int i;
		if (a[0] == '\'') {
			for (i = 1; i < strlen(a) - 1; ++ i) {
				a[i - 1] = a[i];
			}
			a[strlen(a) - 1 - 1] = '\0';
		}
		if (b[0] == '\'') {
			for (i = 1; i < strlen(b) - 1; ++ i) {
				b[i - 1] = b[i];
			}
			b[strlen(b) - 1 - 1] = '\0';
		}
		return strCmp(a, b);
	}
}

item *itemcpy(item *i)
{
	if (!i) {
		return NULL;
	}
	item *item_cpy = (item *) calloc (1, sizeof(item));
	item_cpy->res = (char *) calloc (256, sizeof(char));
	if (!i->res) {
		item_cpy->res = (char *) calloc (256, sizeof(char));
		i->res = (char *) calloc (256, sizeof(char));
	}
	else {
		strcpy(item_cpy->res, i->res);
	}
	item_cpy->type = i->type;
	if (i->next) {
		item_cpy->next = itemcpy(i->next);
	}
	return item_cpy;
}

col *colcpy(col *c)
{
	if (!c) {
		return NULL;
	}
	col *col_cpy = (col *) calloc (1, sizeof(col));
	col_cpy->rootItem = itemcpy(c->rootItem);
	col_cpy->type = c->type;
	col_cpy->name = (char *) calloc (256, sizeof(col));
	if (c->name) {
		strcpy(col_cpy->name, c->name);
	}
	if (c->next) {
		col_cpy->next = colcpy(c->next);
	}
	return col_cpy;
}

table *tablecpy(table *t)
{
	if (!t) {
		return NULL;
	}
	table *table_cpy = (table *) calloc (1, sizeof(table));
	table_cpy->name = (char *) calloc (256, sizeof(char));
	if (t->name) {
		strcpy(table_cpy->name, t->name);
	}
	table_cpy->rootCol = colcpy(t->rootCol);
	if (t->next) {
		table_cpy = tablecpy(t->next);
	}
	return table_cpy;
}

#define EQUAL "=="
#define NOT_EQUAL "~="
#define GREATE_THAN ">"
#define LESS_THAN "<"
#define GREATE_THAN_EQUAL ">="
#define LESS_THAN_EQUEL "<="
#define BETWEEN " between"
#define LIKE " like "

int isSelect(TYPE type, char *res , char *condition)
{
	char **split_c;
	int *cnt = (int *) calloc (1, sizeof(int));

	split_c = split(condition, EQUAL, cnt);
	if (*cnt == 2) {
		if(resCmp(type, res, split_c[1]) == 0) {
			return 1;
		}
		return 0;
	}
	free(split_c);

	split_c = split(condition, NOT_EQUAL, cnt);
	if (*cnt == 2) {
		if (resCmp(type, res, split_c[1]) != 0) {
			return 1;
		}
		return 0;
	}
	free(split_c);
	

	split_c = split(condition, GREATE_THAN, cnt);
	if (*cnt == 2) {
		if (resCmp(type, res, split_c[1]) > 0) {
			return 1;
		}
		return 0;
	}
	free(split_c);
	

	split_c = split(condition, LESS_THAN, cnt);
	if (*cnt == 2) {
		if (resCmp(type, res, split_c[1]) < 0) {
			return 1;
		}
		return 0;
	}
	free(split_c);

	split_c = split(condition, GREATE_THAN_EQUAL, cnt);
	if (*cnt == 2) {
		if (resCmp(type, res, split_c[1]) >= 0) {
			return 1;
		}
		return 0;
	}
	free(split_c);

	split_c = split(condition, LESS_THAN_EQUEL, cnt);
	if (*cnt == 2) {
		if (resCmp(type, res, split_c[1]) <= 0) {
			return 1;
		}
		return 0;
	}
	free(split_c);
	
	split_c = split(condition, BETWEEN, cnt);
	if (*cnt == 2) {
		int *c = (int *) calloc (1, sizeof(int));
		char ** split_b = split(split_c[1], "[", c);
		split_b = split(split_b[0], "]", c);
		split_b = split(split_b[0], ",", c);
		if (*c == 2 && resCmp(type,split_b[0], res)<0 && resCmp(type, split_b[1], res)>0) {
			return 1;
		}
		return 0;
	}
	free(split_c);

	split_c = split(condition, LIKE, cnt);
	if (*cnt == 2) {
		int *c = (int *) calloc (1, sizeof(int));
	}
}

table *where(table *query_table, char *condition)
{
	int *c = (int *) calloc (1, sizeof(int));
	char **split_c;
	char *table_name;
	split_c = split(condition, EQUAL, c);
	if (*c == 2) {
		table_name = split_c[0];
	}
	split_c = split(condition, NOT_EQUAL, c);
	if (*c == 2) {
		table_name = split_c[0];
	}
	split_c = split(condition, GREATE_THAN, c);
	if (*c == 2) {
		table_name = split_c[0];
	}
	split_c = split(condition, GREATE_THAN_EQUAL, c);
	if (*c == 2) {
		table_name = split_c[0];
	}
	split_c = split(condition, LESS_THAN, c);
	if (*c == 2) {
		table_name = split_c[0];
	}
	split_c = split(condition, LESS_THAN_EQUEL, c);
	if (*c == 2) {
		table_name = split_c[0];
	}
	split_c = split(condition, BETWEEN, c);
	if (*c == 2) {
		table_name = split_c[0];
	}

	table *result_table = (table *) calloc (1, sizeof(table));
	col *tmp_col = query_table->rootCol->next;
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
	int cnt = 0;
	while (tmp_item) {
		++ cnt;
		if (isSelect(tmp_col->type, tmp_item->res, condition) == 1) {
			++ index[0];
			index = (int *) realloc (index, (index[0] + 1) * sizeof(int));
			index[index[0]] = cnt;
		}
		tmp_item = tmp_item->next;
	}
	int i,j;
	int colCnt = 0;
	tmp_col = query_table->rootCol->next;
	while (tmp_col) {
		++ colCnt;
		tmp_col = tmp_col->next;
	}
	result_table->rootCol = (col *) calloc (1, sizeof(col));
	int x;
	for (i = colCnt; i > 0; -- i) {
		col *tmp_col = query_table->rootCol;
		for (x = 0; x < i; ++ x) {
			tmp_col = tmp_col->next;
		}
		item *newItem = (item *) calloc (1, sizeof(item));
		newItem->res = (char *) calloc (256, sizeof(char));
		col *newCol = (col*) calloc (1, sizeof(col));
		newCol->rootItem = newItem;
		newCol->name = (char *) calloc (256, sizeof(char));
		strcpy(newCol->name, tmp_col->name);
		for (j = index[0]; j > 0; -- j) {
			item *tmp_item = tmp_col->rootItem;
			for (x = 0; x < index[j]; ++ x) {
				tmp_item = tmp_item->next;
			}
			item *cpy = itemcpy(tmp_item);
			cpy->next = newCol->rootItem->next;
			newCol->rootItem->next = cpy;
		}
		newCol->next = result_table->rootCol->next;
		result_table->rootCol->next = newCol;
	}
	return result_table;
}



char **getBetweenStr(char *query, char *left, char *right, int *cnt)
{
	char **result;
	int *p_left = go(left);
	int *p_right = go(right);
	int *result_left = findString(query, left, p_left);
	int *result_right = findString(query, right, p_right);


	return result;
}

int initItemCnt(col *c)
{
	item *tmp_item = c->rootItem->next;
	int cnt = 0;
	while (tmp_item) {
		++ cnt;
		tmp_item = tmp_item->next; 
	}
	c->itemCnt = cnt;
	return 0;
}
int initColCnt(table *t)
{
	col *tmp_col = t->rootCol->next;
	int cnt = 0;
	while (tmp_col) {
		initItemCnt(tmp_col);
		++ cnt;
		tmp_col = tmp_col->next;
	}
	t->colCnt = cnt;
	return 0;
}
int initTableCnt(database *d)
{
	table *tmp_table = d->rootTable->next;
	int cnt = 0;
	while (tmp_table) {
		initColCnt(tmp_table);
		++ cnt;
		tmp_table = tmp_table->next;
	}
	d->tableCnt = cnt;
	return 0;
}
int initDatabaseCnt()
{
	database *tmp_database = allDatabaseRoot;
	while(tmp_database) {
		initTableCnt(tmp_database);
		tmp_database = tmp_database->next;
	}
	return 0;
}

col *findCol(table *t, char *name)
{
	col *tmp_col = t->rootCol->next;
	while (tmp_col) {
		if (strcmp(tmp_col->name, name) == 0) {
			return tmp_col;
		}
		tmp_col = tmp_col->next;
	}
	return NULL;
}

item *findItem(col *c, int index)
{
	item *tmp_item = c->rootItem->next;
	while (tmp_item) {
		-- index;
		if (index == 0) {
			return tmp_item;
		}
		tmp_item = tmp_item->next;
	}
}

int getItemNum(col *c)
{
	item *tmp_item = c->rootItem->next;
	int cnt = 0;
	while (tmp_item) {
		++ cnt;
		tmp_item = tmp_item->next;
	}
	return cnt;
}
int getColNum(table *t)
{
	col *tmp_col = t->rootCol->next;
	int cnt = 0;
	while(tmp_col) {
		++ cnt;
		tmp_col = tmp_col->next;
	}
	return cnt;
}
#define SELECT "select"
#define FROM "from "

int foo(char *command) 
{
	int *cnt = (int *) calloc (1, sizeof(int));
	char **split_command = split(command, SELECT, cnt);
	if (*cnt != 1) {
		printf(ERROR);
		return 0;
	}
	split_command = split(split_command[0], FROM, cnt);
	if (*cnt != 2) {
		printf(ERROR);
		return 0;
	}
	char *column_set = split_command[0];
	split_command = split(split_command[1], " ", cnt);
	char *name_table = split_command[0];
	table *tmp_table = findTable(name_table);
	table *new_table = tablecpy(tmp_table);
	int colNum = getColNum(tmp_table);
//	if (strcmp("*", column_set) == 0) {
//	} 
//	else {
//		int *c = (int *) calloc (1, sizeof(int));
//		char **split_col = split(column_set, ",", c);
//		col *tmp_col = new_table->rootCol;
//		while (tmp_col) {
//			col *t_col = tmp_col->next;
//			while (t_col) {
//				int flag = 0;
//				for (int i = 0; i < *c; ++ i) {
//					if (strcmp(split_col[i], t_col->name) == 0) {
//						flag = 1;
//					}
//					if (flag) break;
//				}
//				if  (flag) break;
//				t_col = t_col->next;
//			}
//			tmp_col->next = t_col;
//			tmp_col = t_col;
//		}
//	}
	char **where_condition = split(command, " where ", cnt);
	if (*cnt == 2) {
		where_condition = split(where_condition[1], " order by ", cnt);
		new_table = where(new_table, where_condition[0]);
	}
	if (strcmp("*", column_set) == 0) {
	} 
	else {
		int *c = (int *) calloc (1, sizeof(int));
		char **split_col = split(column_set, ",", c);
		col *tmp_col = new_table->rootCol;
		while (tmp_col) {
			col *t_col = tmp_col->next;
			while (t_col) {
				int flag = 0;
				for (int i = 0; i < *c; ++ i) {
					if (strcmp(split_col[i], t_col->name) == 0) {
						flag = 1;
					}
					if (flag) break;
				}
				if  (flag) break;
				t_col = t_col->next;
			}
			tmp_col->next = t_col;
			tmp_col = t_col;
		}
	}
	showTableContext(new_table);
	printf("********");
	return 0;
}

char *add_black(char * command) 
{
	int *go_xin =  go("*");
	int *result_xin = findString(command, "*", go_xin);

	int n = strlen(command);
	int cnt = 0;
	char *command_cpy = (char *) calloc (n + 1 + result_xin[0] * 2, sizeof(char));
	for (int i = 0; i < result_xin[0] * 2 + n; ++ i) {
		if(command[cnt] == '*') {
			command_cpy[i] =' ';
			command_cpy[++i] = '*';
			command_cpy[++i] = ' ';
			cnt ++;
		}
		else {
			command_cpy[i] = command[cnt];
			++ cnt;
		}
	}
	command_cpy[n + result_xin[0] * 2] = '\0';
	return command_cpy;
}

#define P_1 "> ="
#define P_2 "< ="
#define P_3 "~ ="
#define P_4 "= ="

char *pre_process(char *command)
{
	int *p_1 = go(P_1);
	int *p_2 = go(P_2);
	int *p_3 = go(P_3);
	int *p_4 = go(P_4);

	int *result_1 = findString(command, P_1, p_1);
	int *result_2 = findString(command, P_2, p_2);
	int *result_3 = findString(command, P_3, p_3);
	int *result_4 = findString(command, P_4, p_3);

	int flag = 0;
	if (result_1[0] == 1) {
		flag = result_1[1];
	}
	if (result_2[0] == 1) {
		flag = result_2[1];
	}
	if (result_3[0] == 1) {
		flag = result_3[1];
	}
	if (result_4[0] == 1) {
		flag = result_4[1];
	}

	char *command_cpy = (char *) calloc (strlen(command) + 1, sizeof(char));
	strcpy(command_cpy, command);
	if (flag) {
		int i = 0;
		for (; i <= flag; ++ i) {
			command_cpy[i] = command[i];
		}

		for (;i < strlen(command) - 1; ++ i) {
			command_cpy[i] = command[i + 1];
		}
		command_cpy[i] = '\0';
	}

	return command_cpy;
}


