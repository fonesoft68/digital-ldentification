#include "ocr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int args, char *argv[])
{
	unsigned char *res;
	res = (unsigned char*) malloc (sizeof(unsigned char) * 28 * 28);
	if(args > 1) {
		int index = 0;
		for (int i = 0; argv[1][i]; ++ i) {
			index = index * 10 + (int)(argv[1][i] - '0');
		}
		readImageFromDataBase(res, "res/database", index);
	}
	else {
		readImageFromDataBase(res, "res/database", 0);
	}

	return 0;
}
