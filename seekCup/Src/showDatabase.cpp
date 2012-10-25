#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sql.h"
#include "test.h"

int showDatabase()
{
	database *tmp_database = allDatabaseRoot;
	if (!tmp_database) {
		printf("$\n");
	}
	while (tmp_database) {
		printf("%s", tmp_database->name);
		tmp_database = tmp_database->next;
		if (tmp_database) {
			printf(",");
		}
		else {
			printf("\n");
		}
	}

	return 0;
}

int showTableName(char *name)
{
	table *tmp_table;
	if (name == NULL) {
		tmp_table = nowUsedDatabase->rootTable;
		if (tmp_table == NULL) {
			printf("$\n");
		}
		while (tmp_table != NULL) {
			printf("%s", tmp_table->name);
			tmp_table = tmp_table->next;
			if (tmp_table != NULL) {
				printf(",");
			}
			else {
				printf("\n");
			}
		}

	}
	else {
		database *tmp_database = allDatabaseRoot;
		if (tmp_database == NULL) {
			printf("$\n");
		}

		while (tmp_database != NULL) {
			if (strcmp(tmp_database->name, name) == 0) {
				break;
			}
			tmp_database = tmp_database->next;
		}

		tmp_table = tmp_database->rootTable;
		if(tmp_table == NULL) {
			printf("%$\n");
		}
		while (tmp_table != NULL) {
			printf("%s", tmp_table->name);
			tmp_table = tmp_table->next;
			if (tmp_table != NULL) {
				printf(",");
			}
			else {
				printf("\n");
			}
		}
	}

	return 0;
}


database *testDatabase;

int initTestDatabase()
{
	table *table_1 = (table *) calloc (1, sizeof(table));
	table_1->name = (char *) calloc (50, sizeof(char));
	strcpy(table_1->name, "table_1");

	col *col_1 = (col *) calloc (1, sizeof(col));
	col *col_2 = (col *) calloc (1, sizeof(col));
	col *col_3 = (col *) calloc (1, sizeof(col));

	col_1->rootItem = (item *) calloc (1, sizeof(item));
	col_2->rootItem = (item *) calloc (1, sizeof(item));
	col_3->rootItem = (item *) calloc (1, sizeof(item));


	int i;
	char text[5][50] = {"1_item1", "1_item2", "1_item3", "1_item4", "1_item5"};
	for (i = 0; i < 5; ++ i) {
		item *tmp_item = (item *) calloc (1, sizeof(item));
		tmp_item->res = (char *) calloc (50, sizeof(char));
		tmp_item->type = Text;
		strcpy(tmp_item->res, text[i]);
		tmp_item->next = col_1->rootItem->next;
		col_1->rootItem->next = tmp_item;
	}
	col_1->name = (char *) calloc (50, sizeof(char));
	strcpy(col_1->name, "col_1");

	char text_2[5][50] = {"2_item1", "2_item2", "2_item3", "2_item4", "2_item5"};
	memcpy(text, text_2,sizeof(text_2));
	for (i = 0; i < 5; ++ i) {
		item *tmp_item = (item*) calloc (1, sizeof(item));
		tmp_item->res = (char *) calloc (50, sizeof(char));
		tmp_item->type = Text;
		strcpy(tmp_item->res, text[i]);
		tmp_item->next = col_2->rootItem->next;
		col_2->rootItem->next = tmp_item;
	}
	col_2->name = (char *) calloc (50, sizeof(char));
	strcpy(col_2->name, "col_2");

	char text_3[5][50] = {"3_item1", "3_item2", "3_item3", "3_item4", "3_item5"};
	memcpy(text, text_3, sizeof(text));
	for (i = 0; i < 5; ++ i) {
		item *tmp_item = (item *)calloc (1, sizeof(item));
		tmp_item->res = (char *) calloc (50, sizeof(char));
		tmp_item->type = Text;
		strcpy(tmp_item->res, text[i]);
		tmp_item->next = col_3->rootItem->next;
		col_3->rootItem->next = tmp_item;
	}
	col_3->name = (char *) calloc (50, sizeof(char));
	strcpy(col_3->name, "col_3");

	table_1->rootCol = (col *) calloc (1, sizeof(col));

	
	col_1->next = table_1->rootCol->next;
	table_1->rootCol->next = col_1;
	col_2->next = table_1->rootCol->next;
	table_1->rootCol->next = col_2;
	col_3->next = table_1->rootCol->next;
	table_1->rootCol->next = col_3;

	testDatabase = (database *) calloc (1, sizeof(database));
	testDatabase->rootTable = (table *) calloc (1, sizeof(table));
	testDatabase->rootTable->next = table_1;
	nowUsedDatabase = (database *) calloc (1, sizeof(database));
	nowUsedDatabase = testDatabase;
	nowUsedDatabase->name = (char *) calloc (50, sizeof(char));
	strcpy(nowUsedDatabase->name, "testDatabase");

	return 0;
}

int showTestDatabase()
{
	table *tmp_table = nowUsedDatabase->rootTable->next;
	while (tmp_table != NULL) {
		printf("%s:\n", tmp_table->name);
		col *tmp_col = tmp_table->rootCol->next;
		while (tmp_col != NULL) {
			printf("%s: ", tmp_col->name);
			item *tmp_item = tmp_col->rootItem->next;
			while (tmp_item != NULL) {
				printf("%s ", tmp_item->res);
				tmp_item = tmp_item->next;
			}
			tmp_col = tmp_col->next;
			printf("\n");
		}
		tmp_table = tmp_table->next;
	}
	return 0;
}

