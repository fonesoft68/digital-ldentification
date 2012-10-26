#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql.h"
#include "test.h"

int alterAdd(char *table_name, char *datatype)
{
    if (!nowUsedDatabase) {
		printf(ERROR);
		return 0;
    }

    table *tmp_table = nowUsedDatabase->rootTable->next;
    while (tmp_table) {
		if (strcmp(tmp_table->name, table_name) == 0) {
		    break;
		}
		tmp_table = tmp_table->next;
    }
    if (!tmp_table) {
		printf(ERROR);
		return 0;
    }
    int *cnt = (int *) malloc (sizeof(int));
    char **split_datatype = split(datatype, " ", cnt);
    if(*cnt != 1 && *cnt != 2) {
		printf(ERROR);
		return 0;
    }

    col *tmp_col = tmp_table->rootCol->next;
    while (tmp_col->next) {
		if (strcmp(tmp_col->name, split_datatype[0]) == 0) {
		    printf(ERROR);
		    return 0;
		}
		tmp_col = tmp_col->next;
    }
    if (strcmp(tmp_col->name, split_datatype[0]) == 0) {
		printf(ERROR);
		return 0;
    }
    int itemCnt = 0;
	item *tmp_item = tmp_col->rootItem->next;
	while (tmp_item) {
		++ itemCnt;
		tmp_item = tmp_item->next;
	}

    int i;
    item *rootItem = (item *) calloc (1, sizeof(item));
 	rootItem->type = None;


    TYPE type = None;
    if (*cnt == 2) {
		if (strcmp(split_datatype[1], "int") == 0) {
		    type = Int;
		}
		else if (strcmp(split_datatype[1], "float") == 0) {
		    type = Float;
		}
		else if (strcmp(split_datatype[1], "text") == 0) {
		    type = Text;
		}
		else {
		    printf(ERROR);
		    return 0;
		}
    }

    for (i = 0; i < itemCnt; ++ i) {
		item *tmp_item = (item *) calloc (1, sizeof(item));
		tmp_item->type = type;
		tmp_item->next = rootItem->next;
		rootItem->next = tmp_item;
    }
    col *newCol = (col *) calloc (1, sizeof(col));
    newCol->name  = (char *) malloc (sizeof(char) * (strlen(split_datatype[0]) + 1));
    strcpy(newCol->name, split_datatype[0]);
    newCol->type = type;
    newCol->rootItem = rootItem;
	
	newCol->next = tmp_table->rootCol->next;
	tmp_table->rootCol->next = newCol;
    (tmp_table->colCnt) ++ ;

	//showColName(nowUsedDatabase->rootTable->next->rootCol->next);
	//printf("\b \n");
				int *c = (int *) calloc (1, sizeof(int));
				char **str = showTableCol("person", c);
				outputForOrder(str, c, 0);

    return 0;
}

int alterRename(char * table_name, char * datatype) {
    if (!nowUsedDatabase) {
	printf(ERROR);
	return 0;
    }
  
    if (!nowUsedDatabase->rootTable) {
	printf(ERROR);
	return 0;
    }

    table *tmp_table = nowUsedDatabase->rootTable->next;
    while (tmp_table) {
	if (strcmp(table_name, tmp_table->name) == 0) {
	    break;
	}
	tmp_table = tmp_table->next;
    }
    if (!tmp_table) {
	printf(ERROR);
	return 0;
    }

    int *count = (int *) malloc (sizeof(int));
    char **split_datatype = split(datatype, " ", count);
    if (*count != 2) {
	printf(ERROR);
	return 0;
    }

    col *tmp_col = tmp_table->rootCol->next;
    while (tmp_col) {
	if (strcmp(tmp_col->name, split_datatype[0]) == 0) {
      
	    TYPE s = tmp_col->type;
	    if (strcmp(split_datatype[1], "int") == 0 && tmp_col->type == Float) {
		tmp_col->type = Int;
		item *tmp_item = tmp_col->rootItem->next;
		while (tmp_item) {
		    tmp_item->type = Int;
		    float *pf = (float *) malloc (sizeof(float));
		    int *pi = (int *) malloc (sizeof(int));
		    memcpy(pf, tmp_item->res, sizeof(float));
		    *pi = (int) *pf;
		    memcpy(tmp_item->res, pi, sizeof(int));
		    free(pf);
		    tmp_item = tmp_item->next;
		}
		return 0;
	    }
	    else if (strcmp(split_datatype[1], "text") == 0 && tmp_col->type == Float) {
		tmp_col->type = Text;
		item *tmp_item = tmp_col->rootItem->next;
		while (tmp_item) {
		    tmp_item->type = Text;
		    float *pf = (float *) malloc (sizeof(float));
		    char *ps = (char *) calloc (50, sizeof(char));
		    sprintf(ps, "%f", *pf);
			tmp_item->res = ps;
		    free(pf);
		    tmp_item = tmp_item->next;
		}
		return 0;
	    }
	    else if (strcmp(split_datatype[1], "float") == 0 && tmp_col->type == Int) {
		tmp_col->type = Float;
		item *tmp_item = tmp_col->rootItem->next;
		while (tmp_item) {
		    tmp_item->type = Float;
		    int *pi = (int *) malloc (sizeof(int));
		    float *pf = (float *) malloc (sizeof(float));
		    memcpy(pi, tmp_item->res, sizeof(int));
			*pf = (float) *pi;
		    memcpy(tmp_item->res, pf, sizeof(float));
		    free(pi);
		    tmp_item = tmp_item->next;
		}
		return 0;
	    }
	    else if (strcmp(split_datatype[1], "text") == 0 && tmp_col->type == Int) {
		tmp_col->type = Text;
		item *tmp_item = tmp_col->rootItem->next;
		while (tmp_item) {
		    tmp_item->type = Text;
		    int *pi = (int *) malloc (sizeof(int));
		    char *ps = (char *) calloc (20, sizeof(char));
		    sprintf(ps, "%d", *pi);
			tmp_item->res = ps;
		    free(ps);
		    tmp_item = tmp_item->next;
		}
		return 0;
	    }
	    else {
		printf(ERROR);
		return 0;
	    }
	}
	tmp_col = tmp_col->next;
    }
	printf(ERROR);
	return 0;
}
	

int alterDel(char * table_name, char * column_name)
{
    if (!nowUsedDatabase) {
	printf(ERROR);
	return 0;
    }
  
    table * tmp_table = nowUsedDatabase->rootTable->next;
    while (tmp_table) {
	if (strcmp(tmp_table->name, table_name) == 0) {
	    break;
	}
	tmp_table = tmp_table->next;
    }
    if (!tmp_table) {
	printf(ERROR);
	return 0;
    }

    col * tmp_col = tmp_table->rootCol;
	while (tmp_col->next) {
		if (strcmp(tmp_col->next->name, column_name) == 0) {
			tmp_col->next = tmp_col->next->next; 
			return 0;
		}
		tmp_col = tmp_col->next;
	}
    printf(ERROR);
    return -1;
}

#define ALTER_TABLE "alter table "
#define ADD "add "
#define DROP "drop column "
#define ALTER_COLUMN "column"

int alter_parse(char *command)
{
    int *cnt = (int *) malloc (sizeof(int));
    char **split_command = split(command, ALTER_TABLE, cnt);
    if (*cnt != 1) {
	printf(ERROR);
	return 0;
    }

    static int *p_add = go(ADD);
    static int *p_drop = go(DROP);
    static int *p_alter_column = go(ALTER_COLUMN);


    int *result_add = findString(split_command[0], ADD, p_add);
    int *result_drop = findString(split_command[0], DROP, p_drop);
    int *result_alter_column = findString(split_command[0], ALTER_COLUMN, p_alter_column);

    int i;

    if (result_add[0] == 1) {
	char **name_datatype = split(split_command[0], ADD, cnt);
	if (*cnt == 2) {
	    alterAdd(name_datatype[0], name_datatype[1]);
	    free(name_datatype[0]);
	    free(name_datatype[1]);
	    free(name_datatype);
		return 0;
	}
	else {
	    for (i = 0; i < *cnt; ++ i) {
		free(name_datatype[i]);
	    }
	    free(name_datatype);
		printf(ERROR);
		return 0;
	}
#ifdef DEBUG
	printf("$alter add :$\n");
#endif
    }

    if (result_drop[0] == 1) {
	char **name_datatype = split(split_command[0], DROP, cnt);
	if (*cnt == 2) {
	    alterDel(name_datatype[0], name_datatype[1]);
		showColName(nowUsedDatabase->rootTable->next->rootCol->next);
		printf("\b \n");
	    free(name_datatype[0]);
	    free(name_datatype[1]);
	    free(name_datatype);
		return 0;
	}
	else {
	    for (i = 0;i < *cnt; ++ i) {
		free(name_datatype[i]);
	    }
	    free(name_datatype);
		printf(ERROR);
		return 0;
	}
#ifdef DEBUG
	printf("$alter del :$\n");
#endif
    }
	
    if (result_alter_column[0] == 1) {
	char **name_datatype = split(split_command[0], ALTER_COLUMN, cnt);
	if (*cnt == 2) {
	    alterRename(name_datatype[0], name_datatype[1]);
	    free(name_datatype[0]);
	    free(name_datatype[1]);
	    free(name_datatype);
		return 0;
	}
	else {
	    for (i = 0;i < *cnt; ++ i) {
		free(name_datatype[i]);
	    }
	    free(name_datatype);
		printf(ERROR);
		return 0;
	}
#ifdef DEBUG
	    printf("$alter rename :$\n");
#endif
    }
	printf(ERROR);
	return 0;
}
