#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql.h"
#include "test.h"

database *nowUsedDatabase;
database *allDatabaseRoot;
int databaseCnt = 0;

int main(int argc, char *argv[])
{
	if (argc > 1) {
		if (memcmp(argv[1], "kmp", strlen(argv[1])) == 0) {
			char *queryString;
			char *moduleString;
			queryString = (char *) calloc (100, sizeof(char));
			moduleString = (char *) calloc (10, sizeof(char));
			strcat(queryString, "select nimei selectselectsdfa safj selctsjadfkjl slectsdf slectasdfjlkajsdklfa selects");
			strcat(moduleString, "selects");
			
			int *p = go(moduleString);
			
			int *result = findString(queryString, moduleString, p);
			
			printf("%s\n ", queryString);
			printf("%s\n", moduleString);
			int i;
			printf("match for %d (s)\n", result[0]);
			for (i = 0; i < result[0]; ++ i) {
				printf("%d ", result[i + 1]);
			}
		}
		if (memcmp(argv[1], "split", strlen(argv[1])) == 0) {
			char str[1000] = "int a, text sf , float sdf";
			char module[10] = ",";
			printf("\n%s\n%s\n", str, module);
			int *cnt = (int *) malloc (sizeof(int));
			*cnt = 0;
			char **result = split(str, module, cnt);
			int i;
			printf("****");
			for (i = 0; i < *cnt; ++ i) {
				printf("%s\n", result[i]);
			}
            
		}
		if (strcmp(argv[1], "showDatabase") == 0) {
			initTestDatabase();
			showDatabase();
		}
		if (strcmp(argv[1], "showTable") == 0) {
			initTestDatabase();
	
			showTestDatabase();
			showItem(nowUsedDatabase->rootTable->next->rootCol->next->rootItem->next);
			printf("\b ");
		}
		if (strcmp(argv[1], "toLowCase") == 0) {
			printf("test for toLowCase\n");
			char t[256] = "asdfHDFas   asdfsafasf\'sfSDF     FDDFd\'  asdfsadf         \' saf adsf DF asdf\'  DFSDF";
			printf("%s\n", t);
			toLowCase(t);
			printf("%s\n", t);
		}
		if (strcmp(argv[1], "tablecpy") == 0) {
			initTestDatabase();
			showTableContext(nowUsedDatabase->rootTable->next);
			table *t = tablecpy(nowUsedDatabase->rootTable->next);
			printf("\n");
			showTableContext(t);
		}
		if (strcmp(argv[1], "truncate") == 0) {
			initTestDatabase();
			showColName(nowUsedDatabase->rootTable->next->rootCol->next);
			showTableContext(nowUsedDatabase->rootTable->next);
			truncateTable("table_1");
			showColName(nowUsedDatabase->rootTable->next->rootCol->next);
			showTableContext(nowUsedDatabase->rootTable->next);
		
		}
		if (strcmp(argv[1], "xin") == 0) {
			while(1){
			char *a = (char *) calloc (256, sizeof(char));
			gets(a);
			a = add_black(a);
			toLowCase(a);
			printf("%s\n", a);
			}
		}
		
	}

	return 0;
}
