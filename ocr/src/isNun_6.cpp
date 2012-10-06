#include "ocr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isNun_6(unsigned char *res) {
	int judge = 0;

	//实现部分，返回1表示识别出，0表示识别不出
	float B_thr=0.7; //用于识别6的特征值
   int t=NULL,b=0,l=NULL,r=0;
   int i=0,j=0;
   int N_1=0;
	for(i=0;i<heightOfImage;i++)
	{
		for(j=1;j<=widthOfImage;j++)
		{
			if(res[i*widthOfImage+j]==1)
			{
			    t==NULL?t=i:t;
				l==NULL?l>j?l=j:l:l;
				b<i?b=i:b;
				r<j?r=j:r;
			}
		}
	}
	for(i=t;i<=(b+t)/2;i++)
	{
		for(j=l;j<=r;j++)
		{
			if((float)(((b+t)/2-i)/(r-l))>=((float)((b+t)/2-t)/(r-j))
				&&(res[i*widthOfImage+j]==1
				&&(res[(i-1)*widthOfImage+j-1]
				+res[(i-1)*widthOfImage+j]
				+res[(i-1)*widthOfImage+j+1]
				+res[(i)*widthOfImage+j-1]
				+res[(i)*widthOfImage+j+1]
				+res[(i+1)*widthOfImage+j-1]
				+res[(i+1)*widthOfImage+j]
				+res[(i+1)*widthOfImage+j+1])==1))
			{
				N_1++;
			}
		}
	}
	if(N_1!=1) return judge=0;
	else
	{
		unsigned char *bg=(unsigned char *)malloc(sizeof(unsigned char)*widthOfImage*heightOfImage);
		int numc=findCircle(res);
		if(numc==0)
		{
			float n,N;
			for(i=(t+b)/2;i<=b;i++)
			{
				int temp=0;
				for(j=l;j<=r;j++)
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
		else if(numc==1)
		{
		unsigned char*back= (unsigned char*)malloc(sizeof(unsigned char)*widthOfImage*heightOfImage);
		memset(back,0,sizeof(unsigned char)*widthOfImage*heightOfImage);
		int crpoint=0;                           //统计分支点
		       for(i=t;i<=b;i++)
		       {
		                for(j=l;j<=r;j++)
		                {
		                 if((res[(i-1)*widthOfImage+j-1]
				+res[(i-1)*widthOfImage+j]
				+res[(i-1)*widthOfImage+j+1]
				+res[(i)*widthOfImage+j-1]
				+res[(i)*widthOfImage+j+1]
				+res[(i+1)*widthOfImage+j-1]
				+res[(i+1)*widthOfImage+j]
				+res[(i+1)*widthOfImage+j+1])>=3)
				{
				   back[(i)*widthOfImage+j]=1;
				   if((back[(i-1)*widthOfImage+j-1]
				    +back[(i-1)*widthOfImage+j]
				    +back[(i-1)*widthOfImage+j+1]
				    +back[(i)*widthOfImage+j-1]
				    +back[(i)*widthOfImage+j+1]
				    +back[(i+1)*widthOfImage+j-1]
				    +back[(i+1)*widthOfImage+j]
				    +back[(i+1)*widthOfImage+j+1])==0)
				    {
				        crpoint++;
				    }
				  }
		                }
		         }
		         crpoint==1? judge=1:judge=0;
		}
	}
	return judge;
}
