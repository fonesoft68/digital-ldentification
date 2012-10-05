#include "ocr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

float least_squares_method(unsigned char *res, int start, int end){
  int i;
  int cnt=0;
  for(i = start;i != end;++ i)
    if(*(res+i))
      ++ cnt;
  float *p1=(float *)malloc(sizeof(float)*cnt);
  float *p2=(float *)malloc(sizeof(float)*cnt);
  cnt=0;
  for(i = start;i != end;++ i)
    if(*(res+i))
      {
        *(p1+cnt)=i/widthOfImage;
        *(p2+cnt)=i%widthOfImage;
        ++cnt;
      }
  float x_avg=0,y_avg=0;
  float a=0,b=0;
  for(i=0;i!=cnt;++i){
    x_avg+=*(p1+i);
    y_avg+=*(p2+i);
    a+=(*(p1+i))*(*(p2+i));
    b+=(*(p1+i))*(*(p1+i));
  }
  x_avg/=cnt;
  y_avg/=cnt;
  b=(a-cnt*x_avg*y_avg)/(b-cnt*x_avg*x_avg);
  a=y_avg-x_avg*b;
  float length=0;
  for(i=0;i!=cnt;++i)
    length+=(fabs(b*(*(p1+i))+a-(*(p2+i)))<=1?0:(fabs(b*(*(p1+i))+a-(*(p2+i)))));
  return length;
}
int isNun_1(unsigned char *res) {
	int judge = 0;

	//实现部分，返回1表示识别出，0表示识别不出
	if(least_squares_method(res ,0 ,widthOfImage * heightOfImage)<=5)
          judge=1;
	return judge;
}
