#include "ocr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isNun_7(unsigned char *res) {
	int judge = 0;
        int i = 0;
        int *p = (int *)malloc(sizeof(int) * 8);
        int top = 0;
        for(i = 0;i < widthOfImage * heightOfImage;++ i){
          if(*(res + i) && getN(res, i / widthOfImage, i % widthOfImage) == 1){
            *(p + top) = i;
            ++ top;
          }
        }
        if(top == 2){
          int cnt = countPoint(res) >> 1;
          for(i = 0;i < widthOfImage * heightOfImage;++ i){
            if(*(res + i))
              -- cnt;
            if(cnt < 0)
              break;
          }
          if(least_squares_method(res, 0, widthOfImage * heightOfImage) > 10 && is_C(res, p[0], i, countPoint(res), 1) && least_squares_method(res, i, widthOfImage * heightOfImage) <= 10)
            judge = 1;
        }

	//实现部分，返回1表示识别出，0表示识别不出
	
	return judge;
}
