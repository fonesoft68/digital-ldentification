#include "ocr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countPoint(unsigned char *res){
  int cnt = 0;
  for(int i = 0;i != widthOfImage * heightOfImage;++ i){
    if(*(res + i))
      ++ cnt;
  }
  return cnt;
}
int is_C(unsigned char *res,int start,int end,int cnt,int k){
  int flag=1;
  float a,b;
  float x1=start%widthOfImage,x2=end%widthOfImage;
  float y1=start/widthOfImage,y2=end/widthOfImage;
  a=(y2-y1)/(x2-x1);
  b=y1-a*x1;
  float cnt1=0;
  for(int i=start;i!=end;++i)
    if(*(res+i)){
      if(k==1)
        if((a > 0 && i / widthOfImage - b - i % widthOfImage * a > 0) || (a < 0 && i / widthOfImage - b - i % widthOfImage * a < 0)){
          ++ cnt1;
        }
      if(k==2)
        if((a > 0 && i / widthOfImage - b - i % widthOfImage * a < 0) || (a < 0 && i / widthOfImage - b -i % widthOfImage * a > 0)){
          ++ cnt1;
        }
    }
  if(cnt1/(float)cnt>0.1)
    flag=0;
  return flag;
}
int isNun_2(unsigned char *res) {
  int judge = 0;
  int circle_count = 0;
  unsigned char *src = (unsigned char *)malloc(sizeof(unsigned char) * widthOfImage * heightOfImage);
  memcpy(src, res, widthOfImage * heightOfImage);
  circle_count = findCircle(src);
  if(circle_count){
    if(!isNun_0(res)){
    for(int i = 0;i != widthOfImage * heightOfImage;++ i)
      if(*(src + i) > 1)
        *(src + i) = 0;
    for(int i = 0;i != widthOfImage * heightOfImage;++ i){
      *(src + i) = 1 - *(src + i);
    }
    thinImage(src);
    int mid = -1;
    int cnt = countPoint(src);
    for(int i = 0;i != widthOfImage * heightOfImage;++ i){
      if(*(src + i) &&  getN(src, i / widthOfImage, i % widthOfImage) == 3){
        mid = i;
        break;
      }
    }
    int *p = (int *)malloc(sizeof(int) * 8);
    int top = 0;
    for(int i = 0;i < widthOfImage * heightOfImage;++ i){
      if(*(src + i) && getN(src, i / widthOfImage, i % widthOfImage) == 1){
        *(p + top) = i;
        ++ top;
      }
    }
    if(top == 2)
      if(is_C(src, p[0], p[1], cnt, 1))
        judge = 1;
    if(top == 3){
      if(is_C(src, p[0], mid, cnt, 1) && is_C(src, p[1], p[2], cnt, 2))
        judge = 1;
    }
    free(src);
    }
  }
  else{
    int *p = (int *)malloc(sizeof(int) * 8);
    int count = 0;
    for(int i = 0;i != widthOfImage * heightOfImage;++ i)
      if(*(res + i) && getN(res, i / widthOfImage, i % widthOfImage) == 1){
        *(p+count)=i;
        ++ count;
      }
    if(count == 2){
      int j;
      int cnt = countPoint(res);
      int mid=0,start=0,end=0;
      mid=cnt/2+1;
      j=0;
      while(mid){
        if(*(res+j))
          --mid;
        ++j;
      }
      mid=j-1;
      start = p[0];
      end = p[1];
      if(is_C(res,start,mid,cnt,1)&&is_C(res,mid,end,cnt,2) && least_squares_method(res, start, mid) >= 10 && least_squares_method(res, mid,end) >= 10)
        judge=1;
      //实现部分，返回1表示识别出，0表示识别不出
    }
    free(p);
  }
  return judge;
}
