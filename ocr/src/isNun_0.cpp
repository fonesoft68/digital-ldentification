#include "ocr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isNun_0(unsigned char *res) {
	int judge = 0;

	//实现部分，返回1表示识别出，0表示识别不出
	unsigned char *bg;
	bg=(unsigned char*)malloc(sizeof(unsigned char)*widthOfImage*heightOfImage);
	memcpy(bg,res,sizeof(unsigned char)*widthOfImage*heightOfImage);
	
	float A_thr=0.95,B_thr=0.6,L_thr=0.5;//判断0的三个特征值
	int numc=findCircle(bg);
	int i,j;
	if(numc==1)
	{
		float l=0;
		float L=0;
        unsigned char*back= (unsigned char*)malloc(sizeof(unsigned char)*widthOfImage*heightOfImage);
		 memset(back,0,widthOfImage*heightOfImage);
		 FindBorder(bg,res,back,2);
		 for(i=1;i<heightOfImage-1;i++)
		 {
			 for(j=2;j<widthOfImage;j++)
			 {
				 l=l+back[i*widthOfImage+j];
				 L=L+res[i*widthOfImage+j];
			 }
		 }
		 
		l/L>A_thr?judge =1:judge=0;
	}
	else if(numc==0)
	{
		int boardpoint=0;
		float w=0,h=0;
		for(i=1;i<heightOfImage-1;i++)
		{
			for(j=2;j<widthOfImage;j++)
			{
				if((res[(i-1)*widthOfImage+j-1]
				+res[(i-1)*widthOfImage+j]
				+res[(i-1)*widthOfImage+j+1]
				+res[(i)*widthOfImage+j-1]
				+res[(i)*widthOfImage+j+1]
				+res[(i+1)*widthOfImage+j-1]
				+res[(i+1)*widthOfImage+j]
				+res[(i+1)*widthOfImage+j+1])==1)
				{
				boardpoint++;
                                w=j-w;
				h=i-h;
				}
			}
		}
		if(boardpoint=2)
		{
			if((w*w+h*h)/Length(res)<=L_thr) return judge=0;
            float n,N;
			for(i=0;i<heightOfImage;i++)
			{
				int temp=0;
				for(j=1;j<=widthOfImage;j++)
				{
					 if(res[i*widthOfImage+j]==1&&res[i*widthOfImage+j-1]==0) temp++;
				}
				if(temp==2)
				{
					n++;N++;
				}
				else if(temp!=0)
				{
					N++;
				}
			}
			if(n/N>B_thr) judge=1;
		}
	}
	return judge;
}




void FindBorder(unsigned char *bg,unsigned char*res,unsigned char*back,int num)
{
   for(int i=1;i<heightOfImage-1;i++)
   {
     for(int j=2;j<widthOfImage;j++)
      {
         if(JudgePoint(bg,i*widthOfImage+j,num)&&res[i*widthOfImage+j])
         {
            back[i*widthOfImage+j]=1;
         }
      }
   }
}   



int JudgePoint(unsigned char*bg,int position,int num)
{
   int i=position;
   if(bg[i]!=num
   &&(bg[i-widthOfImage-1]==num
   ||bg[i-widthOfImage]==num
   ||bg[i-widthOfImage+1]==num
   ||bg[i-1]==num
   ||bg[i+1]==num
   ||bg[i+widthOfImage-1]==num
   ||bg[i+widthOfImage]==num
   ||bg[i+widthOfImage+1]==num))
   {
   return 1;
   }
   return 0;
}


float Length(unsigned char *res)
{
	float len=0;
	for(int i=1;i<heightOfImage-1;i++)
	{
		for(int j=2;j<widthOfImage;j++)
		{
			len+=(res[(i-1)*widthOfImage+j]
					+res[(i)*widthOfImage+j-1]
					+res[(i)*widthOfImage+j+1]
					+res[(i+1)*widthOfImage+j])
				+(res[(i-1)*widthOfImage+j-1]
					+res[(i-1)*widthOfImage+j-1]
					+res[(i+1)*widthOfImage+j-1]
					+res[(i+1)*widthOfImage+j+1])*1.4;
		}
	}
	len=len/2;
	return len;
}
