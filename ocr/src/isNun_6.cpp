#include "ocr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_8_around(unsigned char *res, int x, int y)
{
	int cnt = 0;

	int xx[] = {0,0,1,1,1,-1,-1,-1};
	int yy[] = {1,-1,0,1,-1,0,1,-1};

	for (int i = 0; i < 8; ++ i) {
		if (x + xx[i] >= 0 && x + xx[i] < heightOfImage && y + yy[i] >= 0 && y + yy[i] < widthOfImage && res[(x + xx[i]) * widthOfImage + y + yy[i]]) {
			++ cnt;
		}
	}


	return cnt;
}

int isNun_6(unsigned char *res)
{
	int judge = 0;
	unsigned char *cpy = (unsigned char *) malloc (sizeof(unsigned char) * widthOfImage * heightOfImage);
	memcpy(cpy, res, sizeof(unsigned char) * widthOfImage * heightOfImage);

	int i = 0;
	int j = 0;

	for (i = 1; i < heightOfImage - 1; ++ i) {
		for (j = widthOfImage - 1; j > 0; -- j) {
			if (res[i * widthOfImage + j]) {
				goto tag_1;
			}
		}
	}
tag_1:

	int x = i;
	int y = j;
	printf("(%d %d)\n", x, y);
	cpy[x * widthOfImage + y] = 0;

	/*
	while (1) {
		if (cpy[(i + 1) * widthOfImage + j]) {
			++ i;
		}
		else if (cpy[(i + 1) * widthOfImage + j + 1]) {
			++ i;
			++ j;
		}
		else if (cpy[i * widthOfImage + j + 1]) {
			++ j;
		}
		else {
			break;
		}
		cpy[i * widthOfImage + j] = 0;
	}
	*/
	int  cnt = 0;

	while (1) {
		if (get_8_around(res, x, y) > 2) {
			break;
		}
		if (cpy[(x + 1) * widthOfImage + y]) {
			++ x;
		}
		else if (cpy[x * widthOfImage + y - 1]) {
			-- y;
		}
		else if (cpy[(x + 1) * widthOfImage + y - 1]) {
			++ x;
			-- y;
		}
		else {
			break;
		}
		cpy[x * widthOfImage + y] = 0;
		++ cnt;
	}

	printf("(%d %d)\n", x, y);

	while (1) {
		if (get_8_around(res, x, y) > 2) {
			break;
		}
		if (cpy[(x + 1) * widthOfImage + y]) {
			++ x;
		}
		else if (cpy[x * widthOfImage + y + 1]) {
			++ y;
		}
		else if (cpy[(x + 1) * widthOfImage + y + 1]) {
			++ x;
			++ y;
		}
		else {
			break;
		}
		cpy[x * widthOfImage + y] = 0;
		++ cnt;
	}

	printf("(%d %d)\n", x, y);

	printf("\n");
	outImage(cpy);

	if (cnt < 7) {
		return 0;
	}

	if (isNun_0(cpy)) {
		return 1;
	}

	return judge;
}

int isNun_6_1(unsigned char *res) {
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
			if((float)(((b+t)/2-i)/(float)(r-j))>=((float)((b+t)/2-t)/(float)(r-l))
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
