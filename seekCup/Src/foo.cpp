#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sql.h"

//kmp失效函数
int* go(char *module)
{
	int m = strlen(module);
	int i;

	int *p = (int *) malloc (sizeof(int) * m);
	memset(p, 0, sizeof(p));
	p[0] = -1;
	int j = -1;
	
	for (i = 1; i < m; ++ i) {
		while (j > -1 && module[j + 1] != module[i]) {
			j = p[j];
		}

		if (module[j + 1] == module[i]) {
			++ j;
		}
		p[i] = j;
	}

	return p;
}

//kmp字符串查找算法
int * findString(char *query, char *module, int *go)
{
	int *res = (int *) malloc (sizeof(int));

	int j = -1;
	int i;
	int m = strlen(module);
	int n = strlen(query);
	int cnt = 0;

#ifdef DEBUG
	for (i = 0; i < m; ++ i)
	{
		printf("%d ", go[i]);
	}
#endif

	for (i = 0; i < n; ++ i) {
		while (j > -1 && module[j + 1] != query[i]) {
			j = go[j];
		}

		if (module[j + 1] == query[i]) {
			j ++;
		}

		if (j == m - 1) {
			res = (int *) realloc(res, sizeof(int) * (++ cnt + 1));
			res[cnt] = i - m + 1;
			j = -1;
		}
	}
	res[0] = cnt;

	return res;
}

int toLowCase(char *str)
{
	int i;
	for (i = 0; i < strlen(str); ++ i) {
		if (str[i] <= 'Z' && str[i] >= 'A') {
			str[i] = (char) ('a' + str[i] - 'A');
		}
	}

	return 0;
}



