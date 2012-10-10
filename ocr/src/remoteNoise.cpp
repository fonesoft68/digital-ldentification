#include "ocr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int classifyImage(unsigned char *origin, int liantong);
int findCircle(unsigned char *origin);
int find(unsigned char *origin, unsigned char *res, int index, int color, int liantong);

unsigned char * remoteNoise(unsigned char *origin)
{

	//实现部分，origin是原来的图片，res是处理过后的
	
	classifyImage(origin, 8);
	
	return origin;
}

int findCircle(unsigned char *origin)
{
	for (int i = 0; i < widthOfImage * heightOfImage; ++ i) {
		origin[i] = origin[i] > 0 ? 0 : 1;
	}
	return classifyImage(origin, 4);
}

int find(unsigned char *origin, unsigned char *res, int index, int color, int liantong)
{
	char x[] = {0,0,1,-1,1,1,-1,-1};
	char y[] = {1,-1,0,0,1,-1,1,-1};
	origin[index] = color;
	res[index] = color;
		for (int i = 0; i < liantong; ++ i) {
			int xx = index / widthOfImage + x[i];
			int yy = index % widthOfImage + y[i];
			if (xx >= 0 && xx < heightOfImage && yy >= 0 && yy < widthOfImage && res[xx * widthOfImage + yy] == 0) {
				if (origin[xx * widthOfImage + yy]) {
					res[xx * widthOfImage + yy] = color;
					origin[xx * widthOfImage + yy] = color;
					find(origin, res, xx * widthOfImage + yy, color, liantong);
				}
			}
		}
		return 0;

}

unsigned char * fullHole(unsigned char *res) 
{
	
	return res;
}

int finid(unsigned char *origin, unsigned char *res, int index, int color, int liantong)
{
	unsigned char queue_x[widthOfImage * heightOfImage];
	unsigned char queue_y[widthOfImage * heightOfImage];

	memset(queue_x, 0, sizeof(unsigned char) * widthOfImage * heightOfImage);
	memset(queue_y, 0, sizeof(unsigned char) * widthOfImage * heightOfImage);

	int head = 0;
	int tail = 1;
	char x[] = {0,0,1,-1,1,1,-1,-1};
	char y[] = {1,-1,0,0,1,-1,1,-1};
	queue_x[head] = index / widthOfImage;
	queue_y[head] = index % widthOfImage;
	
	int cnt = 0;
	while (head < tail) {
		res[queue_x[head] * widthOfImage + queue_y[head]] = color;
		origin[queue_x[head] * widthOfImage + queue_y[head]] = color;
		for (int i = 0; i < liantong; ++ i) {
			int xx = queue_x[head] + x[i];
			int yy = queue_y[head] + y[i];
			if (xx >= 0 && xx < heightOfImage && yy >= 0 && yy < widthOfImage && res[xx * widthOfImage + yy] == 0) {
				if (origin[xx * widthOfImage + yy]) {
					queue_x[tail] = xx;
					queue_y[tail] = yy;
					res[xx * widthOfImage + yy] = color;
					origin[xx * widthOfImage + yy] = color;
					++ cnt;

					++ tail;
				}
			}
		}
		
		++ head;
		
	}

	if (cnt < 7) {
		for (int i = 0; i < widthOfImage * heightOfImage; ++ i) {
			origin[i] = origin[i] == color ? 0 : origin[i];
		}
		-- color;
	}

	

	return 0;
}

int getN(unsigned char *res, int x, int y)
{
	int cnt = 0;
	int xx[] = {-1, -1, 0,1,1,1, 0, -1};
	int yy[] = {0,-1,-1,-1, 0,1,1,1};
	for (int i = 0; i < 8; ++ i) {
          if ((xx[i] + x) * widthOfImage + y + yy[i] >=0 && res[(xx[i] + x) * widthOfImage + y + yy[i]] > 0) {
            ++ cnt;
          }
	}

	return cnt;
}


int classifyImage(unsigned char *origin, int liantong)
{
	unsigned char *res;
	res = (unsigned char*) malloc (sizeof(unsigned char) * widthOfImage * heightOfImage);
	memset(res, 0, sizeof(unsigned char) * widthOfImage * heightOfImage);
	int color = 0;
	for (int i = 0; i < widthOfImage * heightOfImage; ++ i) {
		if (i / widthOfImage == 0 || i / widthOfImage == heightOfImage - 1 || i % widthOfImage == 0 || i / widthOfImage == widthOfImage - 1) {
			continue;
		}
		if (origin[i] && res[i] == 0 && getN(origin, i / widthOfImage, i % widthOfImage) >= 0) {
			find(origin, res, i, ++ color, liantong);
		}
	}

	printf("\nthe sum of color is %d\n", color);
	return color - 1;
}

int* getCicleArea(unsigned char *origin, int *res)
{
	memset(res, 0 , sizeof(int) * 13);

	for (int i = 0; i < widthOfImage * heightOfImage; ++ i) {
		++ res[origin[i]];
	}

	return res;
}
