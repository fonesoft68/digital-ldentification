#include "ocr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isNun_8(unsigned char *res)
{
	int judge = 0;
	
	

	return judge;
}

int isNun_8_1(unsigned char *res) 
{
	int judge = 0;
	float L_thr=0.5,B_thr=0.6;//两个判断8的特征值（从0那直接拿过来的，也许需要做些调整）

	//实现部分，返回1表示识别出，0表示识别不出
	unsigned char *bg;
	bg=(unsigned char*)malloc(sizeof(unsigned char)*widthOfImage*heightOfImage);
	memcpy(bg,res,sizeof(unsigned char)*widthOfImage*heightOfImage);
	int numc=findCircle(bg);
	int i=0,j=0;
	if(numc==2)
	{
	judge ==1;
	}
	else if(numc==1)
	{
	int boardpoint=0;
		float w=0,h=0,h_2;
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
				h_2=i;
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
                        for(j=1;j<=widthOfImage;j++)
				{
					 if(bg[i*widthOfImage+j]==2)
					 {
					 if(h_2<i) return judge=0;
					 continue;
					 }
				}
                        }
			for(i=0;i<heightOfImage;i++)
			{   
				int temp=0;
				for(j=1;j<=widthOfImage;j++)
				{
					 if(res[i*widthOfImage+j]) temp++;
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
