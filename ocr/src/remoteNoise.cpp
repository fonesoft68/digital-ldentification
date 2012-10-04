#include "ocr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char * classifyImage(unsigned char *origin);

unsigned char * remoteNoise(unsigned char *origin)
{

	//实现部分，origin是原来的图片，res是处理过后的
	
	classifyImage(origin);
	
	return origin;
}

int find(unsigned char *origin, unsigned char *res, int index, int color)
{
	unsigned char queue_x[widthOfImage * heightOfImage];
	unsigned char queue_y[widthOfImage * heightOfImage];

	memset(queue_x, 0, sizeof(unsigned char) * widthOfImage * heightOfImage);
	memset(queue_y, 0, sizeof(unsigned char) * widthOfImage * heightOfImage);

	int head = 0;
	int tail = 1;
	char x[] = {0,0,1,1,1,-1,-1,-1};
	char y[] = {1,-1,0,1,-1,0,1,-1};
	queue_x[head] = index / widthOfImage;
	queue_y[head] = index % widthOfImage;

	while (head < tail) {
		res[queue_x[head] * widthOfImage + queue_y[head]] = color;
		origin[queue_x[head] * widthOfImage + queue_y[head]] = color;
		for (int i = 0; i < 8; ++ i) {
			int xx = queue_x[head] + x[i];
			int yy = queue_y[head] + y[i];
			if (xx >= 0 && xx < heightOfImage && yy >= 0 && yy < widthOfImage && res[xx * widthOfImage + yy] == 0) {
				if (origin[xx * widthOfImage + yy]) {
					queue_x[tail] = xx;
					queue_y[tail] = yy;
					res[xx * widthOfImage + yy] = color;

					++ tail;
				}
			}
		}
		
		++ head;
		
	}

	

	return 0;
}

unsigned char * classifyImage(unsigned char *origin)
{
	unsigned char *res;
	res = (unsigned char*) malloc (sizeof(unsigned char) * widthOfImage * heightOfImage);
	memset(res, 0, sizeof(unsigned char) * widthOfImage * heightOfImage);
	int color = 0;
	for (int i = 0; i < widthOfImage * heightOfImage; ++ i) {
		if (origin[i] && res[i] == 0) {
			find(origin, res, i, ++ color);
		}
	}

	printf("\nthe sum of color is %d\n", color);
	return origin;
}

