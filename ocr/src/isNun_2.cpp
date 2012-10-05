#include "ocr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int borderPoint(unsigned char *res,int i){
  return getN(res, i/widthOfImage, i%widthOfImage)==1;
}

int lower_left_exist(unsigned char *res,int i){
  int flag=0;
  if(*(res+i-1)||*(res+i+widthOfImage-1)||*(res+i+widthOfImage))
    flag=1;
  return flag;
}

int DFS(unsigned char *res,int i,int cnt){
  int *color=(int *)malloc(sizeof(int) * widthOfImage * heightOfImage);
  int j;
  for(j = 0;j != widthOfImage * heightOfImage;++j){
    *(color+j)=0;
  }
  *(color+i)=1;
  unsigned char * s = (unsigned char *)malloc(cnt * sizeof(unsigned char));
  int top = 0;
  *(s + top) = i;
  while(getN(res,i/widthOfImage,i%widthOfImage)&&cnt > 1){
    int p[8] = {i-widthOfImage,i-1-widthOfImage,i-1,i-1+widthOfImage,i+widthOfImage,i+1+widthOfImage,i+1,i+1-widthOfImage};
    for(j = 0;j != 8;j ++){
      if(getN(res,p[j]/widthOfImage,p[j]%widthOfImage)){
        if(*(res+p[j]) && *(color+p[j])==0){
          *(color+p[j])=1;
          ++ top;
          *(s + top) = p[j];
          -- cnt;
          i = p[j];
        }
      }
      else{
        while(!getN(res,p[j]/widthOfImage,p[j]%widthOfImage)){
          i = *(s + top -1);
          -- top;
        }
      }
    }
  }
  if(cnt-1)
    return -1;
  return i;
}

int is_C(unsigned char *res,int start,int end,int cnt,int k){
  int flag=1;
  float a,b;
  float x1=start%widthOfImage,x2=end%widthOfImage;
  float y1=start/widthOfImage,y2=end/widthOfImage;
  a=(y2-y1)/(x2-x1);
  b=y1-a*x1;
  printf("%f %f %f %f %f %f\n",x1,y1,x2,y2,a,b);
  float cnt1=0;
  for(int i=start;i!=end;++i)
    if(*(res+i)){
      printf("%f ",i/widthOfImage - b - i % widthOfImage * a);
      if(k==1)
        if((a > 0 && i/widthOfImage - b - i%widthOfImage*a > 0) || (a < 0 && i/widthOfImage - b - i%widthOfImage < 0)){
          ++ cnt1;
        }
      if(k==2)
        if((a > 0 && i/widthOfImage - b -i%widthOfImage * a < 0) || (a < 0 && i/widthOfImage - b -i%widthOfImage > 0)){
          ++ cnt1;
        }
    }
  printf("%d %f\n",cnt,cnt1);
  if(cnt1/(float)cnt>0.1)
    flag=0;
  return flag;
}
int isNun_2(unsigned char *res) {
  printf("get into isnum2\n");
  int judge = 0;
  int circle_count = 0;
  unsigned char *src = (unsigned char *)malloc(sizeof(unsigned char) * widthOfImage * heightOfImage);
  memcpy(src, res, widthOfImage * heightOfImage);
  circle_count = findCircle(src);
  printf("**********************%d**********************",circle_count);
  outImage(res);
  outImage(src);
  if(circle_count <= 1){
    if(circle_count){
      unsigned char *back = (unsigned char *)malloc(sizeof(unsigned char) * widthOfImage *heightOfImage);
      memset(back, 0, sizeof(unsigned char) * widthOfImage * heightOfImage);
      outImage(back);
      FindBorder(src, res, back, 2);
      printf("before\n");
      outImage(back);
      for(int i = 0;i != widthOfImage * heightOfImage;++ i)
        if(*(src + i) == *(back + i))
          *(back + i) = 0;
        else
          *(back + i) = 1;
      outImage(back);
      isNun_2(back);
    }
    int *p = (int *)malloc(sizeof(int) * 8);
    int count = 0;
  for(int i = 0;i != widthOfImage * heightOfImage;++ i)
    if(*(res + i) && borderPoint(res, i)){
      *(p+count)=i;
      ++ count;
    }
  if(count == 2){
    int i=0;
    int j;
    int cnt=0;
    int mid=0,start=0,end=0;
    while(*(res+i)==0)
      ++i;
    for(j=0;j!=widthOfImage * heightOfImage;++j)
      if(*(res+j))
        ++cnt;
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
    if(p[1] == DFS(res, start, cnt))
      if(is_C(res,start,mid,cnt,1)&&is_C(res,mid,end,cnt,2))
        judge=1;
    //实现部分，返回1表示识别出，0表示识别不出
  }
  }
  return judge;
}
