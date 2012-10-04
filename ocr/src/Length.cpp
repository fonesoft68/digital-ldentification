#include"ocr.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

float Length(char *res)
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
