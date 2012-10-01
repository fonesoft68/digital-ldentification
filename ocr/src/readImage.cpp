#include "ocr.h"
#include <stdio.h>
#include <stdlib.h>
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
	for (int i = 0; i < widthOfImage * heightOfImage; ) {
		printf("%c", res[i] > 0 ? '.' : '0');
		printf("%s", (++ i) % widthOfImage ? "" : "\n");
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
#endif
	return res;
}
