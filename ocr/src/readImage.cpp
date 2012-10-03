#include "ocr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cv.h>
#include <highgui.h>
#include <math.h>
#define MAXLEN 4
#define DEBUG

int widthOfImage;
int heightOfImage;

int ByteToInt(unsigned char *buf)
{
	int re = 0;
	for (int i = 0; i < 4; ++ i) {
		re += ((int)buf[i]) << (8 * (3 - i));
	}
	return re;
}

int outImage(unsigned char *res)
{
	printf("\n");
	for (int i = 0; i < widthOfImage * heightOfImage; ) {
		printf("%c", res[i] > 0 ? '.' : '0');
		printf("%s", (++ i) % widthOfImage ? "" : "\n");
	}

	return 0;
}

int outPixel(unsigned char *res)
{
	for (int i = 0; i < heightOfImage; ++ i) {
		for (int j = 0; j < widthOfImage; ++ j) {
			printf("%u ", res[i * widthOfImage + j]);
		}
		printf("\n");
	}

	return 0;
}

unsigned char *readImageFromDataBase(unsigned char *res, char *fileName, int index)
{
	FILE *fileIn = fopen(fileName, "rb");
	int magicNumber;
	int numberOfImages;
	int numberOfRows;
	int numberOfColunms;
	unsigned char buf[MAXLEN];
	fread(buf, sizeof(unsigned char), MAXLEN, fileIn);
	magicNumber = ByteToInt(buf);
	fread(buf, sizeof(unsigned char), MAXLEN, fileIn);
	numberOfImages = ByteToInt(buf);
	fread(buf, sizeof(unsigned char), MAXLEN, fileIn);
	numberOfRows = ByteToInt(buf);
	fread(buf, sizeof(unsigned char), MAXLEN, fileIn);
	numberOfColunms = ByteToInt(buf);
	fseek(fileIn, numberOfRows * numberOfColunms * index, SEEK_CUR);
	fread(res, sizeof(unsigned char), numberOfRows * numberOfColunms, fileIn);
	widthOfImage = numberOfColunms;
	heightOfImage = numberOfRows;
#ifdef DEBUG
	printf("\n%d %d %d %d\n", magicNumber, numberOfImages, numberOfRows, numberOfColunms);
	outImage(res);
	fclose(fileIn);
#endif
	return res;
}

unsigned char* readImageFromFile(unsigned char *res, char *fileName)
{
	IplImage *img;
	img = cvLoadImage(fileName);
	if (!img) {
		printf("Can not read the Image !\n");
		exit(1);
	}

	widthOfImage = img->width;
	heightOfImage  = img->height;
	int step = img->widthStep;
	int channels = img->nChannels;
	unsigned char *data = (unsigned char *)img->imageData;

	
	cvNamedWindow("mainWin", CV_WINDOW_AUTOSIZE);
	cvMoveWindow("mainWin", 100, 100);
	cvShowImage("mainWin", img);
	cvWaitKey(0);
	cvReleaseImage(&img);

	for (int i = 0; i < heightOfImage; ++ i) {
		for (int j = 0; j < widthOfImage; ++ j) {
			int tmp = 0;
			for (int k = 0; k < channels; ++ k) {
				tmp += data[i * step + j * channels + k];
			}
			res[i * widthOfImage + j] = tmp / 3;
                        //                        int min=binaryImage(res);
                        //                        printf("%d",min);
		}
	}
        res=binaryImage(res);
	


	return res;
}

