#include "ocr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isNun_0(unsigned char *res) {
	int judge = 0;

	//实现部分，返回1表示识别出，0表示识别不出
	unsigned char *bg;
	bg=(unsigned char*)malloc(sizeof(unsigned char)*widthOfImage*heightOfImage);
	memcpy(*bg,*res,sizeof(unsigned char)*widthOfImage*heightOfImage);
	
	float A_thr=0.95,B_thr=0.6,L_thr=0.5;//判断0的三个特征值
	int num=Num_Cir(*res);
	int i,j;
	if(num==1)
	{
		int A=0; 
	    int B=0;
		for(i=0;i<heightOfImage;i++)
		{
			int temp=0;
			for(j=1;j<=widthOfImage;j++)
			{
              res[i*widthOfImage+j]==1 ? temp++:temp=temp;
			}
			if(temp==2)
			{
				A++;B++;
			}
			else if(temp !=0)
			{
				B++;
			}
		}
		for(i=1;i<heightOfImage-1;i++)
		{
			for(j=2;j<heightOfImage;j++)
			{
				if(res[i*widthOfImage+j]==1)
				{
				if(bg[(i-1)*widthOfImage+j-1]==2
				   ||(bg[(i-1)*widthOfImage+j]==2
				   ||(bg[(i-1)*widthOfImage+j+1]==2
				   ||(bg[(i)*widthOfImage+j-1]==2
				   ||(bg[(i)*widthOfImage+j+1]==2
				   ||(bg[(i+1)*widthOfImage+j-1]==2
				   ||(bg[(i+1)*widthOfImage+j]==2
				   ||(bg[(i+1)*widthOfImage+j+1]==2)
				   {
				    
				   }
				 }
			}
		}
		A/B>=A_thr?judue =1:judue=0;
	}
	else if(num==0)
	{

	}
	return judge;
}
