#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql.h"

#define INSERT "insert into"
#define VALUES "values"

char * cut(char * str, char c1, char c2)
{
  int start = 0, end = strlen(str) - 1;
  char *s = (char *) calloc (1, sizeof(char) * strlen(str));
  while (*(str + start) == ' ' || *(str + start) == c1) {
    ++ start;
  }
  while (*(str + end) == ' ' || *(str + end) == c2) {
    --end;
  }
  strncpy(s, str + start, end - start + 1);
}

col * find(table * tb, char * str)
{
  col *tmp_col = tb->rootCol;
  while (tmp_col->next) {
    if (strcmp(tmp_col->next->name, str) == 0) {
      return tmp_col->next;
    }
    tmp_col = tmp_col->next;
  }
  if (!tmp_col) {
    printf(ERROR);
    return NULL;
  }
}
  
int insert(const char *command)
{
  int *p = (int *) malloc (sizeof(int));
  char *command_copy = (char *) calloc (1, sizeof(char) * strlen(command) + 1);
  strcpy(command_copy, command);
  char **split_command = split(command_copy, INSERT, p);
  if (*p != 1) {
    printf(ERROR);
    return 0;
  }
  
  char **values = split(split_command[0], VALUES, p);
  if (*p != 2) {
    printf(ERROR);
    return 0;
  }
  
  table *tmp_table = nowUsedDatabase->rootTable;
  while (tmp_table->next) {
    if (strstr(values[0], tmp_table->next->name)) {
      break;
    }
    tmp_table = tmp_table->next;
  }
  tmp_table = tmp_table->next;
  if (!tmp_table) {
    printf(ERROR);
    return 0;
  }
  char *s = (char *) calloc (1, sizeof(char) * strlen(values[0]));
  strcpy(s, values[0] + strlen(tmp_table->name));
  s = cut(s, '(', ')');
  char **value = split(values[1], ",", p);
  if (strlen(s) == 0 && *p == tmp_table->colCnt) {
    int count = *p - 1;
    col *tmp_col = tmp_table->rootCol->next;
    while (tmp_col) {
      item *tmp_item = tmp_col->rootItem->next;
      item *tmp = (item *) calloc (1, sizeof(item));
      value[count] = cut(value[count], '(', ')');
      value[count] = cut(value[count], '\'', '\'');
      tmp->res = (char *) malloc (sizeof(char) * 256);
      strcpy(tmp->res, value[count]);
      tmp_col->rootItem->next = tmp;
      tmp->next = tmp_item;
      -- count;
      ++ (tmp_col->itemCnt);
      tmp_col = tmp_col->next;
    }
  }
  else if (1){
    int *q = (int *) malloc (sizeof(int));
    char **column = split(s, ",", q);
    int cnt = 0;
    for (cnt = 0;cnt < *q;++cnt) {
      if (!find(tmp_table, column[cnt])) {
	printf(ERROR);
	return 0;
      }
    }
    if (*p == *q) {
      col *tmp_col = tmp_table->rootCol->next;
      while (tmp_col) {
	item *tmp_item = tmp_col->rootItem->next;
	item *tmp = (item *) calloc (1, sizeof(item));
      tmp->res = (char *) malloc (sizeof(char) * 256);
      for (int i = 0;i < *p;++ i) {
	if (strcmp(tmp_col->name, column[i]) == 0) {
	  value[i] = cut(value[i], '(', ')');
	  value[i] = cut(value[i], '\'', '\'');
	  strcpy(tmp->res, value[i]);
	  break;
	}
      }
      tmp_col->rootItem->next = tmp;
      tmp->next = tmp_item;
      ++ (tmp_col->itemCnt);
      tmp_col = tmp_col->next;
      }
    }
  }
  else {
    printf(ERROR);
    return 0;
  }
}

void swap(table *tmp_table, int i, int j)
{
  col *tmp_col = tmp_table->rootCol->next;
  while (tmp_col) {
    int cnt = 0;
    item *tmp_item1 = tmp_col->rootItem, *tmp_item2 = tmp_col->rootItem;
    while (cnt <= i) {
      tmp_item1 = tmp_item1->next;
      ++ cnt;
    }
    cnt = 0;
    while (cnt <= j) {
      tmp_item2 = tmp_item2->next;
      ++ cnt;
    }
    // item *tmp = (item *) calloc (1, sizeof(item));
    // tmp = tmp_item1;
    // tmp_item1 = tmp_item2;
    // tmp_item2 = tmp;
    char *tmp = (char *) calloc (1, sizeof(char) * 256);
    strcpy(tmp, tmp_item1->res);
    memset(tmp_item1->res, '\0', sizeof(char) * (strlen(tmp_item1->res) + 1));
    strcpy(tmp_item1->res, tmp_item2->res);
    memset(tmp_item2->res, '\0', sizeof(char) * (strlen(tmp_item2->res) + 1));
    strcpy(tmp_item2->res, tmp);
    tmp_col = tmp_col->next;
  }
}

#define ASC 1
#define DESC 2

table *sort(table *tmp_table, char *name, int rule)
{
  col *tmp_col = find(tmp_table, name);
  if (!tmp_col) {
    printf(ERROR);
    return 0;
  }
  int j, k;
  for (j = 0;j < tmp_table->colCnt;++ j) {
    for (k = tmp_table->colCnt - 1;k > j;-- k) {
      int cnt = 0;
	item *tmp_item = tmp_col->rootItem;
      while (cnt <= k - 1) {
	tmp_item = tmp_item->next;
	++ cnt;
      }
      if ((rule == ASC && resCmp(tmp_col->type, tmp_item->res, tmp_item->next->res) > 0) || (rule == DESC && resCmp(tmp_col->type, tmp_item->res, tmp_item->next->res) < 0)) {
	swap(tmp_table, k, k - 1);
      }
    }
  }
}
