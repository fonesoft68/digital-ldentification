#include "ocr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cv.h>
#include <highgui.h>

#define maxImage 1000 * 1000
#define LENTH_OF_NUM 40

char* distinguishImage(unsigned char *res)
{
	char result[20];
	memset(result, 0, sizeof(result));

	int n = classifyImage(res, 8);
	char con[n + 2][widthOfImage];
	memset(con, 0, sizeof(con));

	for (int tag = 1; tag <= n; ++ tag) {
		for (int i = 0; i < widthOfImage * heightOfImage; ++ i) {
			if (res[i] == tag) {
				++ con[tag][i % widthOfImage];
			}
		}
	}

	int left = -2;
	int right = -1;
	int cnt = 0;
	for (int i = 0; i < widthOfImage; ++ i) {
		for (int tag = 1; tag <= n; ++ i) {
			if (left < right && con[tag][i] >= 1) {
				left = i;
			}

			if (left > right && con[tag][i] <= 1) {
				right = i;
				if (right - left  < LENTH_OF_NUM) {
					/*
					unsigned char *tm = (unsigned char*) malloc (sizeof(unsigned char) * (right - left + 4) * heightOfImage);
					memset(tm, 0, sizeof(unsigned char) * (right - left + 1 + 4) * heightOfImage);

					for (int k = 2; k <= right - left + 2; ++ k) {
						for (int x = 0; x < heightOfImage; ++ x) {
							tm[k + widthOfImage * x] = res[x * widthOfImage + k - 2 + left];
						}
					}
					*/

					for (int k = 0; k < heightOfImage; ++ k) {
						res[k * widthOfImage + right] = 1;
					}

					//result[cnt] = get(tm);
				}
				else {
					for (int k = left; k <= right; ++ k) {
						if (con[tag][k] <= 2) {
							for (int x = 2; x < heightOfImage; ++ x) {
								res[x * widthOfImage + k] = 1;
							}
						}
					}
				}
			}
		}
	}

	//outVisual(res);
	return result;
}


int main(int args, char *argv[])
{
	unsigned char *res;
	res = (unsigned char*) malloc (sizeof(unsigned char) * 1000 * 1000);
	char name[50] = "res/phone_num/1.png";
	if(args > 1) {
		int index = 0;
		for (int i = 0; argv[1][i]; ++ i) {
			index = index * 10 + (int)(argv[1][i] - '0');
		}
		memset(name, 0, strlen(argv[1]));
	}
	readImageFromFile(res, name);
	binaryImage(res);
	thinImage(res);
	printf("is ");
	//distinguishImage(res);

	return 0;
}
