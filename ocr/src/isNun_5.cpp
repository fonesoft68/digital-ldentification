#include "ocr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isNun_5(unsigned char *res) {
	int judge = 0;
        unsigned char *src = (unsigned char *)malloc(sizeof(unsigned char) * widthOfImage * heightOfImage);
        for(int i = 0;i < widthOfImage * heightOfImage;++ i)
          *(src + i) = *(res + (heightOfImage - i / widthOfImage - 1) * widthOfImage + i % widthOfImage);
        outImage(res);
        outImage(src);
        if(isNun_2(src))
          judge = 1;
	//实现部分，返回1表示识别出，0表示识别不出
        //把res上下颠倒，运行isNun_2判断
        free(src);
	return judge;
}
