#include "ocr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxImage 1000 * 1000

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
			char name[50] = "res/hub_image/hub_image_1.jpeg";
 
			if (args > 2) {
				memcpy(name, argv[2], sizeof(argv[2]));
			}

			res = (unsigned char*) malloc (sizeof(unsigned char) * maxImage);
			memset(res, 0, sizeof(unsigned char) * maxImage);
			readImageFromFile(res, name);
			outPixel(res);


			return 0;
		}
                for(int i=0;i!=index;++i){
                  readImageFromDataBase(res, "res/database", i);
                  if (memcmp(argv[1], "is_Num1", strlen(argv[1]) *sizeof(char))==0) {
                    printf("test for least_square\n");
                    thinImage(res);
                    outImage(res);
                    printf("%d\n",isNun_1(res));
                }}
		if (memcmp(argv[1], "thinImage", strlen(argv[1]) * sizeof(char)) == 0) {
			printf("test for thinImage\n");
			thinImage(res);
			outImage(res);
		}
		if (memcmp(argv[1], "remoteNoise", strlen(argv[1]) * sizeof(char)) == 0) {
			printf("test for remoteNoise\n");
			remoteNoise(res);
			outPixel(res);
		}

		if (memcmp(argv[1], "smoothImage", strlen(argv[1])) == 0) {
			printf("test for smoothImage\n");
			smoothImage(res);
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
