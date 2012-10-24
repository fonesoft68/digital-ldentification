#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql.h"

database *nowUsedDatabase;
database *allDatabaseRoot;

int main(int argc, char *argv[])
{
<<<<<<< HEAD
  database * allDatabaseRoot = createDatabase("huzi");
  database *db = createDatabase("huzi");
=======
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
		if (memcmp(argv[1], "toLowCase", strlen(argv[1])) == 0) {
			char *str = (char *)malloc (sizeof(char) * 100);
			scanf("%s", str);
			toLowCase(str);
			printf("%s\n", str);
		}
		if (memcmp(argv[1], "split", strlen(argv[1])) == 0) {
			char str[1000] = "asf l lldd sj fldds  jd\nkf        jldddsdf jkld dsdj fldd djsfl                      ";
			char module[10] = " ";
			printf("\n%s\n%s\n", str, module);
			int *cnt = (int *) malloc (sizeof(int));
			*cnt = 0;
			char **result = split(str, module, cnt);
			int i;
			for (i = 0; i < *cnt; ++ i) {
				printf("%s\n", result[i]);
			}
			
		}
	}

	return 0;
<<<<<<< HEAD
  database *db = createDatabase("huzi");
=======
  database *db = createDataBase("huzi");
>>>>>>> 77a60c039c8c5fcae60edb9ba4ac1377fd8ab7df
>>>>>>> f4aa3c097bfa655137f13a2c403aec2c730483df
  printf("%s %d\n",db->name, db->tableCnt);
  return 0;
}
