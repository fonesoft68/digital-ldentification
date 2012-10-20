#include "ocr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isNun_4(unsigned char *res) {
	int judge = 0;

	//实现部分，返回1表示识别出，0表示识别不出
	int i;
	int j;
	unsigned char *cpy = (unsigned char *) malloc (sizeof(unsigned char) * widthOfImage * heightOfImage);
	memcpy(cpy, res, sizeof(unsigned) * widthOfImage * heightOfImage);
	
	//从右下角开始找第一个端点
	for (i = heightOfImage - 4; i > 0; -- i) {
		for (j = 4; j < widthOfImage - 2; ++ j) {
			if (res[i * widthOfImage + j]) {
				goto tag_1;
			}
		}
	}

tag_1:
	int x = i;
	int y = j;
	cpy[x * widthOfImage + y] = 0;

	//从下往上消除直线上的点
	while (1) {
		if (get_8_around(res, x, y) > 2) {
			break;
		}
		else if (res[(x - 1) * widthOfImage + y]) {
			-- x;
		}
		else if (res[(x - 1) * widthOfImage + y - 1]) {
			-- x;
			-- y;
		}
		else if (res[(x - 1) * widthOfImage + y + 1]) {
			-- x;
			++ y;
		}
		else {
			break;
		}
		cpy[x * widthOfImage + y] = 0;
	}

	//从右上角开始找第一个断点
	for (i = 1; i < heightOfImage - 1; ++ i) {
		for (j = widthOfImage - 1; j > 0; -- j) {
			if (res[i * widthOfImage + j]) {
				goto tag_2;
			}
		}
	}

tag_2:
	x = i;
	y = j;
	cpy[x * widthOfImage + y] = 0;


	//从上往下消除直线上的点
	while (1) {
		if (get_8_around(res, x, y) > 2) {
			break;
		}
		else if (res[(x + 1) * widthOfImage + y]) {
			++ x;
		}
		else if (res[(x + 1) * widthOfImage + y + 1]) {
			++ x;
			++ y;
		}
		else if (res[(x + 1) * widthOfImage + y - 1]) {
			++ x;
			-- y;
		}
		else {
			break;
		}
		cpy[x * widthOfImage + y] = 0;
	}

	outImage(cpy);

	//找消除直线以后左边的断点
	for (i = 1; i < heightOfImage - 1; ++ i) {
		for (j = 1; j < widthOfImage - 1; ++ j) {
			if (get_8_around(cpy, i, j) == 1 && cpy[i * widthOfImage + j]) {
				goto tag_3;
			}
		}
	}

tag_3:

	x = i;
	y = j;
	printf("(%d %d)\n", x, y);
	cpy[x * widthOfImage + y] = 0;

	//找消除直线以后右边的断点
	for (i = heightOfImage - 1; i > 0; -- i) {
		for (j = widthOfImage - 1; j > 0; -- j) {
			if (get_8_around(cpy, i, j) == 1 && cpy[i * widthOfImage + j]) {
				goto tag_4;
			}
		}
	}

tag_4:

	//消除这条弧
	i = x;
	j = y;
	printf("(%d %d)\n", i, j);
	int cnt = 0;

	while (1) {
		if (cpy[(x + 1) * widthOfImage + y]) {
			++ x;
		}
		else if (cpy[(x + 1) * widthOfImage + y + 1]) {
			++ x;
			++ y;
		}
		else if (cpy[(x + 1) * widthOfImage + y - 1]) {
			++ x;
			-- y;
		}
		else {
			break;
		}
		-- cnt;
	}
	printf("(%d %d)\n", x, y);
	j = y;

	while (1) {
		if (cpy[x * widthOfImage + y + 1]) {
			++ y;
		}
		else if (cpy[(x + 1) * widthOfImage + y + 1]) {
			++ x;
			++ y;
		}
		else if (cpy[(x - 1) * widthOfImage + y + 1]) {
			-- x;
			++ y;
		}
		else {
			break;
		}
		-- cnt;
	}

	for (int i = 0; i < widthOfImage * heightOfImage; ++ i) {
		if (cpy[i]) {
			++ cnt;
		}
	}

	if (cnt < 8 && abs(i - x) > 4 && abs(j - y) > 4) {
		return 1;
	}

	return judge;
}
