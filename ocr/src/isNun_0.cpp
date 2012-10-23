#include "ocr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int end_x;
int end_y;
int start_x;
int start_y;

int isNun_0(unsigned char *res) 
{
	unsigned char *cpy = (unsigned char *) malloc (sizeof(unsigned char) * widthOfImage * heightOfImage);
	memset(cpy, 0, sizeof(unsigned char) * widthOfImage * heightOfImage);


	int judge = 0;
	int i;
	int j;
	for (i = 1; i < heightOfImage - 1; ++ i) {
		for (j = 1; j < widthOfImage - 1; ++ j) {
			if (res[i * widthOfImage + j]) {
				goto tag_1;
			}
		}
	}


tag_1:

	start_x = i;
	start_y = j;
	int flag = 1;
	int x = start_x;
	int y = start_y;

	printf("(%d %d)\n", x, y);

	for (j = y + 1; j < heightOfImage - 1 && res[x * widthOfImage + j]; ++ j) {
		cpy[i * widthOfImage + j] = 1;
	}
	start_y = -- j;
	cpy[i * widthOfImage + j] = 0;
	printf("(%d %d)\n", x, y);

	while (1) {
		if (res[(i + 1) * widthOfImage + j]) {
			++ i;
		}
		else if (res[i * widthOfImage + j + 1]) {
			++ j;
		}
		else if (res[(i + 1) * widthOfImage + j + 1]) {
			++ i;
			++ j;
		}
		else {
			if (!res[(i + 1) * widthOfImage + j - 1] && !res[(i + 1) * widthOfImage + j] && !res[(i + 1) * widthOfImage + j + 1] && !res[i * widthOfImage + j + 1]) {
				start_x = i;
				start_y = j;
			}
			break;
		}
	}

	printf("(%d %d)\n", x, y);


	int xx[] = {1, 1, -1, -1};
	int yy[] = {-1, 1, 1, -1};
	int sum = 0;

	for (i = 0; i < 4; ++ i) {
		int left_right = 0;
		int top_bottom = 0;
	
		while (1) {
			if (res[x * widthOfImage + y + yy[i]] && !cpy[x * widthOfImage + y + yy[i]]) {
				y += yy[i];
				++ left_right;
				cpy[x * widthOfImage + y] = 1;
			}
			else if (res[(x + xx[i]) * widthOfImage + y + yy[i]] && !cpy[(x + xx[i]) * widthOfImage + y + yy[i]]) {
				x += xx[i];
				y += yy[i];
				++ left_right;
				++ top_bottom;
				cpy[x * widthOfImage + y] = 1;
				
			}
			else if (res[(x + xx[i]) * widthOfImage + y] && !cpy[(x + xx[i]) * widthOfImage + y]) {
				x += xx[i];
				++ top_bottom;
				cpy[x * widthOfImage + y] = 1;
			}
			else {
				printf("%d\n", left_right + top_bottom);
				++ flag;
				break;
			}
		}
		if (left_right < 1 || top_bottom < 1 || left_right + top_bottom + sum < 5) {
			if (i < 3)
				return 0;
		}

		sum = left_right + top_bottom;
	}

	int cnt_of_nosearch = 0;
	int remote = abs(x - start_x) + abs(y - start_y);

	printf("(%d %d)\n", x, y);

	for (i = 1; i < heightOfImage - 1; ++ i) {
		for (j = 1; j < widthOfImage - 1; ++ j) {
			if (res[i * widthOfImage + j] && !cpy[i * widthOfImage + j]) {
				++ cnt_of_nosearch;
				//remote = remote < abs(i - x) + abs(j - y) ? remote : abs(i - x) + abs(j - y);
			}
		}
	}

	if (remote < 8 && flag >= 3 && cnt_of_nosearch < 8) {
		judge = 1;
		printf("the remote is %d, the remain is %d\n", remote, cnt_of_nosearch);
	}

	return judge;
}


int isNun_0_2(unsigned char *res) {
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
