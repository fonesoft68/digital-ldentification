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

		if (memcmp(argv[1], "readImage", strlen(argv[1])) == 0) {
			printf("test for readImage from file\n");

			if (args > 2) {
				readImageFromFile(res, argv[2]);
			}
			else {
				readImageFromFile(res, "res/hub_image/hub_image_1.jpeg");
			}
			outPixel(res);
			exit(0);
		}

		readImageFromDataBase(res, "res/database", index);

		if (memcmp(argv[1], "thinImage", strlen(argv[1]) * sizeof(char)) == 0) {
			printf("test for thinImage\n");
			thinImage(res);
			outImage(res);
		}

		if (memcmp(argv[1], "smoothImage", strlen(argv[1])) == 0) {
			printf("test for smoothImage\n");
			smoothImage(res);
			outImage(res);
		}

		if (memcmp(argv[1], "remoteNoise", strlen(argv[1])) == 0) {
			printf("test for remoteNoise\n");
			remoteNoise(res);
			outImage(res);
		}

		if (memcmp(argv[1], "binaryImage", strlen(argv[1])) == 0) {
			printf("test for binarImage\n");
			binaryImage(res);
			outImage(res);
		}

		if (memcmp(argv[1], "readImage", strlen(argv[1])) == 0) {
			printf("test for binaryImage\n");
		}

	}

	return 0;
}
