#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql.h"

database *nowUsedDatabase = (database *)calloc(1, sizeof(database));
database *allDatabaseRoot = (database *)calloc(1, sizeof(database));
int databaseCnt = 0;

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
    item *tmp = (item *) calloc (1, sizeof(item));
    tmp = tmp_item1;
    tmp_item1 = tmp_item2;
    tmp_item2 = tmp;
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

int main(int argc, char *argv[])
{

  //    allDatabaseRoot->next = NULL;
  allDatabaseRoot =  createDatabase("huzi");

    allDatabaseRoot->rootTable->next = createTable("  a int  , b float , c text   ");
    allDatabaseRoot->rootTable->next->name = "a";
    nowUsedDatabase = allDatabaseRoot;
    insert("insert into a values (2 , 3.5, 'how')");
    insert("insert into a values (1, 4.7, 'foo')");
    insert("insert into a values (3, 2.4, 'bar')");
    swap(allDatabaseRoot->rootTable->next, 0, 1);
    sort(allDatabaseRoot->rootTable->next, "b", ASC);
    //    insert("insert into a (b , c ) values (2.3, 'wuhan' )");
    //    alter_parse("alter table b drop column c ");
    if (argc > 1) {
	if (memcpy(argv[1], "drop", strlen(argv[1])) == 0) {
	    //    drop("huzi");
	    printf("%p ***\n", allDatabaseRoot);
	}
	if (memcmp(argv[1], "createTable", strlen(argv[1])) == 0) {
	    //allDatabaseRoot->rootTable = createTable(" int a , float b , noe  ");
	}
    }
}
