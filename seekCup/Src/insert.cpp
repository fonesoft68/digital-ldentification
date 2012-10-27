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
  if (end - start + 1 < 0) {
    return "";
  }
  else {
    strncpy(s, str + start, end - start + 1);
    return s;
  }
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
 
int isStr(char *str)
{
  int i;
  for (i = 0;i < strlen(str); ++ i) {
    if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_' || str[i] == ' ');
    else
    {
      return 0;
    }
  }
  return 1;
}

int insert(const char *command)
{
  if (!nowUsedDatabase) {
    printf(ERROR);
    return 0;
  }
  
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
  int m = 0, n = 1;
  while (*(values[1] + m) != '\0') {
    if (*(values[1] + m) == ',') {
      ++ n;
    }
    ++ m;
  }
  char * value[n];
  for (int i = 0;i < n;++ i) {
    value[i] = (char *) calloc (1, sizeof(char) * 256);
  }
  static int *r = go(",");
  int *result = findString(values[1], ",", r);
  for (int i = 0;i < n;++ i) {
    if (i == 0) {
      strncpy(value[0], values[1], result[1]);
    }
    else if (i == n - 1) {
      strcpy(value[n - 1], values[1] + result[n - 1] + 1);
    }
    else {
      strncpy(value[i], values[1] + result[i] + 1, result[i + 1] - result[i] - 1);
    }
  }
  if (strlen(s) == 0 && n == tmp_table->colCnt) {
    int count = n - 1;
    col *tmp_col = tmp_table->rootCol->next;
    while (tmp_col) {
      item *tmp_item = tmp_col->rootItem->next;
      item *tmp = (item *) calloc (1, sizeof(item));
      value[count] = cut(value[count], '(', ')');
      value[count] = cut(value[count], '\'', '\'');
      if (((tmp_col->type == Int) && (isNum(value[count]))) || ((tmp_col->type == Float) && (isFloat(value[count])))
	  || ((tmp_col->type == Text) && (isStr(value[count]))) || ((tmp_col->type == None) && strcmp(value[count], "") == 0));
      else {
	printf(ERROR);
	return 0;
      }
      tmp->res = (char *) calloc (1, sizeof(char) * 256);
      tmp->type = tmp_col->type;
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
	tmp->res = (char *) calloc (1, sizeof(char) * 256);
	for (int i = 0;i < *p;++ i) {
	  if (strcmp(tmp_col->name, column[i]) == 0) {
	    value[i] = cut(value[i], '(', ')');
	    value[i] = cut(value[i], '\'', '\'');
	    if (((tmp_col->type == Int) && (isNum(value[i]))) || ((tmp_col->type == Float) && (isFloat(value[i]))) || ((tmp_col->type == Text) && (isStr(value[i]))) || ((tmp_col->type == None) && strcmp(value[i], "") == 0));	  
	    else {
	      printf(ERROR);
	      return 0;
	    }
	    strcpy(tmp->res, value[i]);
	    break;
	  }
	}
	tmp->type = tmp_col->type;
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

void sort(table *tmp_table, char *name, int rule)
{
  col *tmp_col = find(tmp_table, name);
  if (!tmp_col) {
    printf(ERROR);
    return;
  }
  int j, k;
  for (j = 0;j < tmp_col->itemCnt;++ j) {
    for (k = tmp_col->itemCnt - 1;k > j;-- k) {
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
