#include "ocr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cv.h>
#include <highgui.h>

#define maxImage 1000 * 1000


int getLength(char *cnt, int index) {
	int left, right;
	
	for (left = index; cnt[left] > 0; -- left);
	for (right = index; cnt[right] > 0; ++ right);


	return right - left;
}


char* distinguishImage(unsigned char *res)
{

	int left = 0;
	int right = 0;
	char cnt[widthOfImage];
	int sum[widthOfImage];
	int ct = 0;

	memset(sum, 0, sizeof(int) * widthOfImage);
	memset(cnt, 0, sizeof(cnt));

	for (int i = 2; i < widthOfImage - 2; ++ i) {
		for (int j = 2; j < heightOfImage - 2; ++ j) {
			if (res[j * widthOfImage + i] >= 1) {
				++ cnt[i];
			}
		}
		sum[i] = sum[i - 1] + cnt[i];
	}

	for (int i = 0; i < widthOfImage; ++ i) {
		printf("%d ", sum[i]);
	}

	int flag = 0;
	int count = 0;
	int sumOfWidth = 0;
	for (int i = 0; i < widthOfImage; ++ i) {
		if (cnt[i] > 0) {
			while (i < widthOfImage && cnt[i] > 0) {
				++ i;
				++ sumOfWidth;
			}
			++ count;
		}
	}

	const int MAX_OF_LEN = (int)((float)widthOfImage / 11 * 1.2);
	const int MIN_OF_LEN = (int)((float)widthOfImage / 11 * 0.2);
	const int MIN_OF_PIX = (int)((float)sum[widthOfImage - 3] / 11 * 0.4);
	const int MAX_OF_PIX = (int)((float)sum[widthOfImage - 3] / 11 * 1.2);


	for (int i = 0; i < widthOfImage; ++ i) {
		printf("(%d)%d ", i, cnt[i]);
	}

	printf("\npix: %d %d, len: %d %d\n", MIN_OF_PIX, MAX_OF_PIX, MIN_OF_LEN, MAX_OF_LEN);

	printf("\n");
	while(left < widthOfImage - 4 && right < widthOfImage - 4) {
		while (left < widthOfImage - 4 && cnt[left] == 0) {
			++ left;
		}
		
		right = left + 1;
		while (right < widthOfImage - 4 && cnt[right] > 0) {
			++ right;
		}

		int tm1[100];
		int tm2[100];
		int flag = 0;
		memset(tm1, 0, sizeof(tm1));
		memset(tm2, 0, sizeof(tm2));
		if (right - left > MAX_OF_LEN || sum[right] - sum[left] > MAX_OF_PIX) {

			for (int i = left; i < right; ++ i) {
				if (cnt[i] >= 1 && cnt[i] <= 1) {
					tm1[++ tm1[0]] = i;
				}
			}

			for (int i = left; i < right; ++ i) {
				if (cnt[i] == 2) {
					tm2[++ tm2[0]] = i;
				}
			}

			for (int i = 1; i <= tm1[0]; ++ i) {
				if (tm1[i] - left < MAX_OF_LEN && tm1[i] - left > MIN_OF_LEN && sum[tm1[i]] - sum[left] > MIN_OF_PIX && sum[tm1[i]] - sum[left] < MAX_OF_PIX) {
					flag = 1;
					printf("                      the tm1 is function\n");
					right = tm1[i];
				}
			}

			for (int i = 1; i <= tm2[0]; ++ i) {
				if (!flag && tm2[i] - left < MAX_OF_LEN && tm2[i] - left > MIN_OF_LEN && sum[tm2[i]] - sum[left] > MIN_OF_PIX && sum[tm2[i]] - sum[left] < MAX_OF_PIX) {
					flag = 1;
					printf("                      the tm2 is function\n");
					right = tm2[i];
				}
			}

		}

		if (right - left > MIN_OF_LEN || !flag)
		{

			for (int i = 0; i < heightOfImage; ++ i) {
				res[i * widthOfImage + right] = 1;
			}
			++ ct;
			printf("(%d):  nu: %d  (len: %d,pix: %d)\n", ct, right, right - left, sum[right] - sum[left]);
		}

		left = right + 1;
	}
	printf("the sum is %d\n", ct);
	outVisual(res);

	return NULL;
}


int main(int args, char *argv[])
{
	unsigned char *res;
	res = (unsigned char*) malloc (sizeof(unsigned char) * 1000 * 1000);
	char name[50] = "res/phone_num/1.png";
	if(args > 1) {
		strcpy(name, argv[1]);
	}
	printf("%s\n", name);
	readImageFromFile(res, name);
	binaryImage(res);
	outVisual(res);
	thinImage(res);
	outVisual(res);
	distinguishImage(res);

	return 0;
}
