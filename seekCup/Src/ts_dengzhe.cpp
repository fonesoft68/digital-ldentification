#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"sql.h"

database *nowUsedDatabase = (database *)calloc(1, sizeof(database));
database *allDatabaseRoot = (database *)calloc(1, sizeof(database));
int databaseCnt = 0;
int main()
{
	char a[11]="aksopdlkjl";
	char b[8]="ak?o*l*";
        char c[5]="1234";
	char d[10]="1000,1893";
	if(like(a,b)){
		printf("a like b");
	}else printf("a dislike b");
        if(between(c,d)){
	  printf("c is between d");
	}else printf("c is not between d");
	return 0;
}

