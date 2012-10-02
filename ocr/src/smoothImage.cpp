#include "ocr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char * smoothImage(unsigned char *origin)
{
	unsigned char *res;
	int i;
	int j;
	res = (unsigned char *) malloc (sizeof(unsigned char) * widthOfImage * heightOfImage);

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

