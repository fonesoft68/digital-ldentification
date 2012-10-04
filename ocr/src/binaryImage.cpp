#include "ocr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define GrayScale 256
unsigned char * binaryImage(unsigned char *origin)
{
  int *p=(int *)malloc(sizeof(int)*256);
  for(int i=0;i!=256;++i)
    *(p+i)=0;
  for(int i=0;i!=widthOfImage * heightOfImage;++i)
    p[origin[i]]++;
  float q[256]={0,};
  for(int i=0;i!=256;++i)
    q[i]=(float)p[i]/(widthOfImage * heightOfImage);
  int threshold=0;
  float w0,w1,u0tmp,u1tmp,u0,u1,u,deltaTmp,deltaMax=0;
  for(int i=0;i!=GrayScale;++i){
    w0=w1=u0tmp=u1tmp=u0=u1=u=deltaTmp=0;
    for(int j=0;j!=GrayScale;++j)
      {
        if(j<=i)
          {
            w0+=q[j];
            u0tmp+=j*q[j];
          }
        else
          {
            w1+=q[j];
            u1tmp+=j*q[j];
          }
      }
    u0=u0tmp/w0;
    u1=u1tmp/w1;
    u=u0tmp+u1tmp;
    deltaTmp=w0*(u0-u)*(u0-u)+w1*(u1-u)*(u1-u);
    if(deltaTmp>deltaMax)
      {
        deltaMax=deltaTmp;
        threshold=i;
      }
  }
  printf("\nthe yuzhi is %d\n",threshold);
  for(int i=0;i!=widthOfImage * heightOfImage;++i)
    if(*(origin+i)<=threshold)
      *(origin+i)=1;
    else
      *(origin+i)=0;
  return origin;
}


