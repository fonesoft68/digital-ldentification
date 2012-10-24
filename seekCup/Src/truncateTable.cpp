#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sql.h"
#include "test.h"

#define ERROR "error\n"

int truncateTable(char *name)
{
	table *tmp_table = (table *) calloc (1, sizeof(table));
	if (nowUsedDatabase == NULL) {
		printf(ERROR);
		return 0;
	}
	tmp_table = nowUsedDatabase->rootTable;
	if (tmp_table == NULL) {
		printf("$\n");
		return 0;
	}

	while (tmp_table != NULL) {
		if (strcmp(tmp_table->name, name) == 0) {
			col *tmp_col = tmp_table->rootCol;
			while (tmp_col != NULL) {
				freeCol(tmp_col->next);
				tmp_col = tmp_col->next;
			}
		}
		tmp_table = tmp_table->next;
	}

	return 0;
}

int freeItem(item *i)
{
	if(i->next != NULL) {
		freeItem(i->next);
	}
	free(i->res);
	i = NULL;
	return 0;
}

int freeCol(col *c) {
	if (c->next != NULL) {
		freeCol(c->next);
	}
	freeItem(c->rootItem);
	free(c->name);
	c = NULL;
	return 0;
}

int freeTable(table *t)
{
	if (t->next != NULL) {
		freeTable(t->next);
	}
	freeCol(t->rootCol);
	free(t->name);
	t = NULL;
	return 0;
}

int freeDatabase(database *d)
{
	if(d->next != NULL) {
		freeDatabase(d->next);
	}
	freeTable(d->rootTable);
	free(d->name);
	d = NULL;
	return 0;
}
