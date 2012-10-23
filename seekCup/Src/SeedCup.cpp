
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql.h"


int main(int argc, char *argv[])
{
	freopen("Src/Input.txt", "r", stdin);
	freopen("Src/Output.txt", "w", stdout);

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
		if (c == ';') {
			command[cnt + 1] = '\0';
			parseCommand(command);
			memset(command, 0, sizeof(char) * maxLenOfCmd);
			cnt = -1;
		}
		else {
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
	
	return 0;
}
