#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sql.h"

//失效函数
char * go(char *module, int *go)
{
	int m = strlen(module);
	int i;

	memset(go, 0, sizeof(go));
	go[0] = -1;
	j = -1;
	
	for (i = 1; i < m; ++ i) {
		while (j > -1 && module[j + 1] != module[i]) {
			j = go[j];
		}

		if (module[j + 1] == module[i]) {
			++ j;
		}
		go[i] = j;
	}

	return go;
}

int * findString(char *query, char *module, int *go)
{
	int *res;
	res = NULL;

	int j = -1;
	int i;
	int m = strlen(module);
	int cnt = -1;

	for (i = 0; i < n; ++ i) {
		while (j > -1 && module[j + 1] != query[i]) {
			j = go[j];
		}

		if (module[j + 1] == query[i]) {
			j ++;
		}

		if (j == m) {
			res[++ cnt] = i - m;
			j = go[j];
		}
	}

	return res;
}

