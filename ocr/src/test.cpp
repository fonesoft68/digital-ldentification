#include "ocr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int args, char *argv[])
{
	printf("test for c unit\n");
	unsigned char *res;
	res = (unsigned char *) malloc (sizeof(unsigned char) * 28 * 28);
	memset(res, 0, sizeof(unsigned char) * 28 * 28);
	if (args > 1) {
		int index = 0;
		if (args > 2) {
			for (int i = 0; argv[2][i]; ++ i) {
				index = index * 10 + (int) (argv[2][i] - '0');
			}
		}
		readImageFromDataBase(res, "res/database", index);
		if (memcmp(argv[1], "thinImage", strlen(argv[1]) * sizeof(char)) == 0) {
			printf("test fot thinImage\n");
			thinImage(res);
			outImage(res);
		}
	}

	return 0;
}
