#include "ocr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isNun_3(unsigned char *res) {
	int judge = 0;
        int i;
	//实现部分，返回1表示识别出，0表示识别不出
        int *p = (int *)malloc(sizeof(int) * 8);
        int top = 0;
        for( i = 0;i != widthOfImage * heightOfImage;++ i){
          if(*(res + i) && getN(res, i / widthOfImage, i % widthOfImage) == 1){
            *(p + top) = i;
            ++ top;
          }
        }
        unsigned char *src = (unsigned char *)malloc(sizeof(unsigned char) * widthOfImage * heightOfImage);
        memcpy(src, res, widthOfImage * heightOfImage);
        int countCircle = findCircle(src);
        outPixel(src);
        for(i = 0;i < widthOfImage * heightOfImage;++ i){
          if(*(src + i) >= 2){
            -- countCircle;
          }
        }
        if(countCircle < 0) {
          free(src);
          return 0;
        }
        if(top == 2 || top == 3){
          int start, mid, end;
          int cnt = countPoint(res);
          if(top == 2){
          start = p[0];
          end = p[1];
          int cnt = countPoint(res);
          int count = 0.4375 * cnt;
          for( i = 0;i < widthOfImage * heightOfImage;++ i){
            if(*(res + i))
              --count;
            if(count < 0)
              break;
          }
          mid = i;
          }
          else{
            start = p[0];
            mid = p[1];
            end = p[2];
          }
          if(!isNun_1(res) && is_C(res, start, mid, cnt, 1) && is_C(res, mid, end, cnt, 1))
            judge = 1;
        }
        free(src);
	return judge;
}
