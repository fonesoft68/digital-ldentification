#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql.h"

int main(int argc, char *argv[])
{
<<<<<<< HEAD

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
	}

	return 0;
=======
  database *db = createDataBase("huzi");
  printf("%s %d\n",db->name, db->tableCnt);
  return 0;
>>>>>>> fd4b6ffaa69cb0476245e1fdaba7e0f5b1aed977
}
