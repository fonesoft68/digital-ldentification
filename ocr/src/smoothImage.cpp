#include "ocr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char * smoothImage(unsigned char *origin)
{
	unsigned char *res;
	res = (unsigned char *) malloc (sizeof(unsigned char) * widthOfImage * heightOfImage);

	//实现部分，origin是原来的图片，res是处理过后的
	
	memcpy(origin, res, sizeof(unsigned char) * widthOfImage * heightOfImage);                                                                         
	return origin;
}

