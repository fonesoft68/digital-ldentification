#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql.h"

database *allDatabaseRoot;
database *nowUsedDatabase;
int databaseCnt = 0;


int main(int argc, char *argv[])
{
	if (argc > 1) {
		if (!freopen(argv[1], "r", stdin)) {
			printf("invalid file path!\n");
			return 0;
		}
	}
	else { 
		if (!freopen("Src/Input.txt", "r", stdin)) {
			printf("invalid fiel path\n");
			return 0;
		}
	}
	if(!freopen("Output.txt", "w", stdout)) {
		printf("error while read Output.txx\n");
	}

	char c;
	int cnt = -1;
	int maxLenOfCmd = 1 << 10;
	char *command = (char *) malloc (sizeof(char) * maxLenOfCmd);
	memset(command, 0, sizeof(char) * maxLenOfCmd);

	if (command == NULL) {
		printf("memery error!\n");
		return 0;
	}

	while ((c = getchar()) != EOF) {
		if (c == '\n' || c == '\t') {
			c = ' ';
		}
		if (c == ';') {
			command[cnt + 1] = '\0';
			printf("********\n");
			initDatabaseCnt();
			parseCommand(command);
			memset(command, 0, sizeof(char) * maxLenOfCmd);
			cnt = -1;
		}
		else if (c != '\n' && c != '\t'){
			++ cnt;
			if (cnt > maxLenOfCmd - 1) {
				command = (char *) realloc (command, (maxLenOfCmd + 500) * sizeof(char));
				maxLenOfCmd += 500;
			}
			command[cnt] = c;
		}
	}


	fclose(stdin);
	fclose(stdout);
	if (argc == 3) {
		if(!freopen(argv[2], "w", stdout)) {
			printf("invalid file Path\n");
		}
		if (!freopen("Output.txt", "r", stdin)) {
			printf("invalid fiel path\n");
		}
		char a, b;
		while (1) {
			a = getchar();
			if (a == EOF) {
				fclose(stdin);
				fclose(stdout);
				return 0;
			}
			b = getchar();
			if (b == EOF) {
				putchar(a);
				fclose(stdin);
				fclose(stdout);
				return 0;
			}
			if (b == '\b') {
				a = getchar();
				continue;
			}
			putchar(a);
			putchar(b);
		}
	}
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}
