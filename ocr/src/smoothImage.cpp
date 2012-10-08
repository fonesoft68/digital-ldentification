#include "ocr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define abs(x) (x) > 0 ? (x) : (-(x))

unsigned char* smoothImage_1(unsigned char*);
unsigned char* smoothImage_2(unsigned char*);
unsigned char* getSharp(unsigned char*);

unsigned char* smoothImage(unsigned char *origin)
{
	getSharp(origin);


	return origin;
}

extern unsigned char *getSharp(unsigned char *origin)
{
	unsigned char *res = (unsigned char*) malloc (sizeof(unsigned char) * widthOfImage * heightOfImage);
	memset(res, 0, sizeof(unsigned char) * widthOfImage * heightOfImage);

	for (int i = 0; i < widthOfImage * heightOfImage; ++ i) {
		res[i] = origin[i] > 0 ? 255 : 0;
	}

	int xx[] = {0,0,1,1,1,-1,-1,-1};
	int yy[] = {1,-1,1,-1,0,1,-1,0};
	for (int i = 1; i < widthOfImage - 1; ++ i) {
		for (int j = 1; j < heightOfImage - 1; ++ j) {
			int averg = 0;
			for (int x = 0; x < 8; ++ x) {
				averg += res[(xx[x] + i) * widthOfImage + yy[x] + j];
			}
			if (abs(averg - res[i * widthOfImage + j])) {
				origin[i * widthOfImage + j] = !origin[i * widthOfImage + j];
			}
		}
	}

	free(res);

	return origin;
}


extern unsigned char * smoothImage_2(unsigned char *origin)
{
	unsigned char *res;
	int i;
	int j;
	res = (unsigned char *) malloc (sizeof(unsigned char) * widthOfImage * heightOfImage);
	memset(res, 0, widthOfImage * heightOfImage);

	//实现部分，origin是原来的图片，res是处理过后的
	 for( i=2;i<heightOfImage-2;i++)
        {
                for(j=2;j<widthOfImage-2;j++)
                {
                        //模板1
                        if(origin[(i-1)*widthOfImage+j-1]>=0
                        && origin[(i-1)*widthOfImage+j]>0
                        && origin[(i-1)*widthOfImage+j+1]>=0
                        && origin[(i)*widthOfImage+j-1]>0
                        && origin[(i)*widthOfImage+j+1]>0
                        && origin[(i+1)*widthOfImage+j-1]>=0
                        && origin[(i+1)*widthOfImage+j]>0
                        && origin[(i+1)*widthOfImage+j+1]>=0)
                        {
                                res[(i)*widthOfImage+j]=1;
                                continue;
                        }
                        
                        //模板2
                        if(origin[(i-1)*widthOfImage+j-1]>=0
                        && origin[(i-1)*widthOfImage+j]>0
                        && origin[(i-1)*widthOfImage+j+1]>=0
                        && origin[(i)*widthOfImage+j-1]>0
                        && origin[(i)*widthOfImage+j+1]>0
                        && origin[(i+1)*widthOfImage+j-1]==0
                        && origin[(i+1)*widthOfImage+j]==0
                        && origin[(i+1)*widthOfImage+j+1]>0)
                       {
                                res[(i)*widthOfImage+j]=1;
                                continue;
                       }
                       else if(origin[(i-1)*widthOfImage+j-1]>=0
                        && origin[(i-1)*widthOfImage+j]>0
                        && origin[(i-1)*widthOfImage+j+1]>0
                        && origin[(i)*widthOfImage+j-1]>0
                        && origin[(i)*widthOfImage+j+1]==0
                        && origin[(i+1)*widthOfImage+j-1]>=0
                        && origin[(i+1)*widthOfImage+j]>0
                        && origin[(i+1)*widthOfImage+j+1]==0)
                       {
                                res[(i)*widthOfImage+j]=1;
                                continue;
                       }
                        else if(origin[(i-1)*widthOfImage+j-1]>0
                        && origin[(i-1)*widthOfImage+j]==0
                        && origin[(i-1)*widthOfImage+j+1]==0
                        && origin[(i)*widthOfImage+j-1]>0
                        && origin[(i)*widthOfImage+j+1]>0
                        && origin[(i+1)*widthOfImage+j-1]>=0
                        && origin[(i+1)*widthOfImage+j]>0
                        && origin[(i+1)*widthOfImage+j+1]>=0)
                       {
                                res[(i)*widthOfImage+j]=1;
                                continue;
                       }
                       else if(origin[(i-1)*widthOfImage+j-1]==0
                        && origin[(i-1)*widthOfImage+j]>0
                        && origin[(i-1)*widthOfImage+j+1]>=0
                        && origin[(i)*widthOfImage+j-1]==0
                        && origin[(i)*widthOfImage+j+1]>0
                        && origin[(i+1)*widthOfImage+j-1]>0
                        && origin[(i+1)*widthOfImage+j]>0
                        && origin[(i+1)*widthOfImage+j+1]>=0)
                       {
                                res[(i)*widthOfImage+j]=1;
                                continue;
                       }
                       
                       //模板3
                       if(origin[(i-1)*widthOfImage+j-1]==0
                        && origin[(i-1)*widthOfImage+j]==0
                        && origin[(i-1)*widthOfImage+j+1]>=0
                        && origin[(i)*widthOfImage+j-1]==0
                        && origin[(i)*widthOfImage+j+1]>0
                        && origin[(i+1)*widthOfImage+j-1]==0
                        && origin[(i+1)*widthOfImage+j]==0
                        && origin[(i+1)*widthOfImage+j+1]>0)
                        {
                                res[(i)*widthOfImage+j]=0;
                                continue;
                        }
                         else if(origin[(i-1)*widthOfImage+j-1]>=0
                        && origin[(i-1)*widthOfImage+j]>0
                        && origin[(i-1)*widthOfImage+j+1]>0
                        && origin[(i)*widthOfImage+j-1]==0
                        && origin[(i)*widthOfImage+j+1]==0
                        && origin[(i+1)*widthOfImage+j-1]==0
                        && origin[(i+1)*widthOfImage+j]==0
                        && origin[(i+1)*widthOfImage+j+1]==0)
                       {
                                res[(i)*widthOfImage+j]=0;
                                continue;
                       }
                       else if(origin[(i-1)*widthOfImage+j-1]>0
                        && origin[(i-1)*widthOfImage+j]==0
                        && origin[(i-1)*widthOfImage+j+1]==0
                        && origin[(i)*widthOfImage+j-1]>0
                        && origin[(i)*widthOfImage+j+1]==0
                        && origin[(i+1)*widthOfImage+j-1]>=0
                        && origin[(i+1)*widthOfImage+j]==0
                        && origin[(i+1)*widthOfImage+j+1]==0)
                       {
                                res[(i)*widthOfImage+j]=0;
                                continue;
                       }
                       else if(origin[(i-1)*widthOfImage+j-1]==0
                        && origin[(i-1)*widthOfImage+j]==0
                        && origin[(i-1)*widthOfImage+j+1]==0
                        && origin[(i)*widthOfImage+j-1]==0
                        && origin[(i)*widthOfImage+j+1]==0
                        && origin[(i+1)*widthOfImage+j-1]>0
                        && origin[(i+1)*widthOfImage+j]>0
                        && origin[(i+1)*widthOfImage+j+1]>=0)
                       {
                                res[(i)*widthOfImage+j]=0;
                                continue;
                       }
                       
                       //模板4
                        if(origin[(i-1)*widthOfImage+j-1]==0
                        && origin[(i-1)*widthOfImage+j]==0
                        && origin[(i-1)*widthOfImage+j+1]==0
                        && origin[(i)*widthOfImage+j-1]==0
                        && origin[(i)*widthOfImage+j+1]>0
                        && origin[(i+1)*widthOfImage+j-1]==0
                        && origin[(i+1)*widthOfImage+j]==0
                        && origin[(i+1)*widthOfImage+j+1]>=0)
                        {
                                res[(i)*widthOfImage+j]=0;
                                continue;
                        }
                        else if(origin[(i-1)*widthOfImage+j-1]==0
                        && origin[(i-1)*widthOfImage+j]>0
                        && origin[(i-1)*widthOfImage+j+1]>=0
                        && origin[(i)*widthOfImage+j-1]==0
                        && origin[(i)*widthOfImage+j+1]==0
                        && origin[(i+1)*widthOfImage+j-1]==0
                        && origin[(i+1)*widthOfImage+j]==0
                        && origin[(i+1)*widthOfImage+j+1]==0)
                       {
                                res[(i)*widthOfImage+j]=0;
                                continue;
                       }
                        else if(origin[(i-1)*widthOfImage+j-1]>=0
                        && origin[(i-1)*widthOfImage+j]==0
                        && origin[(i-1)*widthOfImage+j+1]==0
                        && origin[(i)*widthOfImage+j-1]>0
                        && origin[(i)*widthOfImage+j+1]==0
                        && origin[(i+1)*widthOfImage+j-1]==0
                        && origin[(i+1)*widthOfImage+j]==0
                        && origin[(i+1)*widthOfImage+j+1]==0)
                       {
                                res[(i)*widthOfImage+j]=0;
                                continue;
                       }
                        else if(origin[(i-1)*widthOfImage+j-1]==0
                        && origin[(i-1)*widthOfImage+j]==0
                        && origin[(i-1)*widthOfImage+j+1]==0
                        && origin[(i)*widthOfImage+j-1]==0
                        && origin[(i)*widthOfImage+j+1]==0
                        && origin[(i+1)*widthOfImage+j-1]>=0
                        && origin[(i+1)*widthOfImage+j]>0
                        && origin[(i+1)*widthOfImage+j+1]==0)
                       {
                                res[(i)*widthOfImage+j]=0;
                                continue;
                       }
                       
                       res[(i)*widthOfImage+j]=origin[(i)*widthOfImage+j];
                }
         }       
	memcpy(origin, res, sizeof(unsigned char) * widthOfImage * heightOfImage);                                                                         
	return origin;
}

