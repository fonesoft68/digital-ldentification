#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql.h"

database *nowUsedDatabase = (database *)calloc(1, sizeof(database));
database *allDatabaseRoot = (database *)calloc(1, sizeof(database));
int databaseCnt = 0;
int main(int argc, char *argv[])
{

    allDatabaseRoot->next = NULL;
    if(!allDatabaseRoot) {
	printf("all is empty\n");
    }
    createDatabase("huzi");

    allDatabaseRoot->rootTable = createTable("  a int  , b float  , noe  ");
    allDatabaseRoot->rootTable->name = "a";
    allDatabaseRoot->rootTable->next = createTable(" c int , d float ");
    allDatabaseRoot->rootTable->next->name = "b";
    nowUsedDatabase = allDatabaseRoot;
    alter_parse("alter table b drop column c ");
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
