#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"sql.h"
int main()
{
	char a[11]="aksopdlkjl";
	char b[6]="ak?o*";
	if(Like(a,b)){
		printf("true");
    }
	return 0;
}

