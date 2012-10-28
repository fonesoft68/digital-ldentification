#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sql.h"
#include "test.h"

#define ERROR "error\n"

int truncateTable(char *name)
{
	if (nowUsedDatabase == NULL) {
		printf(ERROR);
		printf("sdf");
		return 0;
	}
	table *tmp_table = findTable(name);
	if (tmp_table == NULL) {
		printf(ERROR);
		printf("sdf");
		return 0;
	}

	col *tmp_col = tmp_table->rootCol->next;
	while (tmp_col) {
		tmp_col->rootItem->next = 0;
		tmp_col = tmp_col->next;
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
