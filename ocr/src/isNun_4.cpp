#include "ocr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isNun_4(unsigned char *res) {                 
	int judge = 0;
	//实现部分，返回1表示识别出，0表示识别不出
<<<<<<< HEAD
	float B_thr=0.6; //用于识别4的特征值直接来自9
   int t=NULL,b=0,l=NULL,r=0;
   int i=0,j=0;
   int N_1=0;int N_2=0;
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
	for(i=(b+t)/2;i<=b;i++)
	{
		for(j=l;j<=r;j++)
		{
			if(res[i*widthOfImage+j]==1
				&&(res[(i-1)*widthOfImage+j-1]
				+res[(i-1)*widthOfImage+j]
				+res[(i-1)*widthOfImage+j+1]
				+res[(i)*widthOfImage+j-1]
				+res[(i)*widthOfImage+j+1]
				+res[(i+1)*widthOfImage+j-1]
				+res[(i+1)*widthOfImage+j]
				+res[(i+1)*widthOfImage+j+1])==1)
			{
			       
				if((float)((b-i)/(j-l))<=((float)(b-(b+t)/2)/(r-l)))
				{
				N_1++;
				}
				N_2++;
			}
		}
	}
	if(N_1!=1)  judge=0;
	else
	{
		unsigned char *bg=(unsigned char *)malloc(sizeof(unsigned char)*widthOfImage*heightOfImage);
		int numc=findCircle(res);
		if(numc==0)
		{
			float n,N;
			for(i=t;i<=(t+b)/2;i++)
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
			if(n/N>B_thr&&N_2>=3) judge=1;
			
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
		         crpoint==1&&N_2>=3? judge=1:judge=0;
		}
	}
=======
	int i;
	int j;
	unsigned char *cpy = (unsigned char *) malloc (sizeof(unsigned char) * widthOfImage * heightOfImage);
	memcpy(cpy, res, sizeof(unsigned) * widthOfImage * heightOfImage);
	
	//从右下角开始找第一个端点
	for (i = heightOfImage - 4; i > 0; -- i) {
		for (j = 4; j < widthOfImage - 2; ++ j) {
			if (res[i * widthOfImage + j]) {
				goto tag_1;
			}
		}
	}

tag_1:
	int x = i;
	int y = j;
	cpy[x * widthOfImage + y] = 0;

	//从下往上消除直线上的点
	while (1) {
		if (get_8_around(res, x, y) > 2) {
			break;
		}
		else if (res[(x - 1) * widthOfImage + y]) {
			-- x;
		}
		else if (res[(x - 1) * widthOfImage + y - 1]) {
			-- x;
			-- y;
		}
		else if (res[(x - 1) * widthOfImage + y + 1]) {
			-- x;
			++ y;
		}
		else {
			break;
		}
		cpy[x * widthOfImage + y] = 0;
	}

	//从右上角开始找第一个断点
	for (i = 1; i < heightOfImage - 1; ++ i) {
		for (j = widthOfImage - 1; j > 0; -- j) {
			if (res[i * widthOfImage + j]) {
				goto tag_2;
			}
		}
	}

tag_2:
	x = i;
	y = j;
	cpy[x * widthOfImage + y] = 0;


	//从上往下消除直线上的点
	while (1) {
		if (get_8_around(res, x, y) > 2) {
			break;
		}
		else if (res[(x + 1) * widthOfImage + y]) {
			++ x;
		}
		else if (res[(x + 1) * widthOfImage + y + 1]) {
			++ x;
			++ y;
		}
		else if (res[(x + 1) * widthOfImage + y - 1]) {
			++ x;
			-- y;
		}
		else {
			break;
		}
		cpy[x * widthOfImage + y] = 0;
	}

	outImage(cpy);

	//找消除直线以后左边的断点
	for (i = 1; i < heightOfImage - 1; ++ i) {
		for (j = 1; j < widthOfImage - 1; ++ j) {
			if (get_8_around(cpy, i, j) == 1 && cpy[i * widthOfImage + j]) {
				goto tag_3;
			}
		}
	}

tag_3:

	x = i;
	y = j;
	printf("(%d %d)\n", x, y);
	cpy[x * widthOfImage + y] = 0;

	//找消除直线以后右边的断点
	for (i = heightOfImage - 1; i > 0; -- i) {
		for (j = widthOfImage - 1; j > 0; -- j) {
			if (get_8_around(cpy, i, j) == 1 && cpy[i * widthOfImage + j]) {
				goto tag_4;
			}
		}
	}

tag_4:

	//消除这条弧
	i = x;
	j = y;
	printf("(%d %d)\n", i, j);
	int cnt = 0;

	while (1) {
		if (cpy[(x + 1) * widthOfImage + y]) {
			++ x;
		}
		else if (cpy[(x + 1) * widthOfImage + y + 1]) {
			++ x;
			++ y;
		}
		else if (cpy[(x + 1) * widthOfImage + y - 1]) {
			++ x;
			-- y;
		}
		else {
			break;
		}
		-- cnt;
	}
	printf("(%d %d)\n", x, y);
	j = y;

	while (1) {
		if (cpy[x * widthOfImage + y + 1]) {
			++ y;
		}
		else if (cpy[(x + 1) * widthOfImage + y + 1]) {
			++ x;
			++ y;
		}
		else if (cpy[(x - 1) * widthOfImage + y + 1]) {
			-- x;
			++ y;
		}
		else {
			break;
		}
		-- cnt;
	}

	for (int i = 0; i < widthOfImage * heightOfImage; ++ i) {
		if (cpy[i]) {
			++ cnt;
		}
	}

	if (cnt < 8 && abs(i - x) > 4 && abs(j - y) > 4) {
		return 1;
	}

>>>>>>> 0fdcd1466eda38c93d14dfdf5c996d6edd207138
	return judge;
}
