#include "ocr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG
unsigned char* thinImage_1(unsigned char*);
unsigned char* thinImage_2(unsigned char*);
unsigned char* thinImage_3(unsigned char*);

unsigned char* thinImage(unsigned char *origin)
{
	thinImage_1(origin);
	thinImage_2(origin);
	thinImage_3(origin);
	return origin;
}

//并行细化算法
unsigned char* thinImage_1(unsigned char *origin)
{
	unsigned char *res;
	res = (unsigned char*) malloc (sizeof(unsigned char) * widthOfImage * heightOfImage);
	memset(res, 0, sizeof(unsigned char) * widthOfImage * heightOfImage);
	int flag = 1;
	int i;
	int j;
	while(flag==1) //flag=0时迭代结束
    {

        flag=0;
        for( i=2;i<heightOfImage-2;i++)
        {
                for(j=2;j<widthOfImage-2;j++)
                {
                        //模板a
                        if(origin[(i-1)*widthOfImage+j-1]==0
                        && origin[(i-1)*widthOfImage+j+1]>0
                        && origin[(i)*widthOfImage+j-1]==0
                        && origin[(i)*widthOfImage+j-0]>0
                        && origin[(i)*widthOfImage+j+1]>0
                        && origin[(i)*widthOfImage+j+2]>0
                        && origin[(i+1)*widthOfImage+j-1]==0
                        && origin[(i+1)*widthOfImage+j+1]>0)
                        {
                                res[(i)*widthOfImage+j]=1;
                                flag=1;
                                continue;
                        }

                        //模板b
                        if(origin[(i-1)*widthOfImage+j-0]>0
                        && origin[(i-1)*widthOfImage+j+1]>0
                        && origin[(i)*widthOfImage+j-1]==0
                        && origin[(i)*widthOfImage+j-0]>0
                        && origin[(i)*widthOfImage+j+1]>0
                        && origin[(i)*widthOfImage+j+2]>0
                        && origin[(i+1)*widthOfImage+j-1]==0
                        && origin[(i+1)*widthOfImage+j-0]==0)
                        {
                                res[(i)*widthOfImage+j]=1;
                                flag=1;
                                continue;
                        }
                        //模板c
                        if(origin[(i-1)*widthOfImage+j-1]==0
                        && origin[(i-1)*widthOfImage+j-0]==0
                        && origin[(i)*widthOfImage+j-1]==0
                        && origin[(i)*widthOfImage+j-0]>0
                        && origin[(i)*widthOfImage+j+1]>0
                        && origin[(i)*widthOfImage+j+2]>0
                        && origin[(i+1)*widthOfImage+j-0]>0
                        && origin[(i+1)*widthOfImage+j+1]>0)
                        {
                                res[(i)*widthOfImage+j]=1;
                                flag=1;
                                continue;
                        }

                        //模板d
                        if(origin[(i-1)*widthOfImage+j-1]==0
                        && origin[(i-1)*widthOfImage+j-0]==0
                        && origin[(i-1)*widthOfImage+j+1]==0
                        && origin[(i)*widthOfImage+j-0]>0
                        && origin[(i+1)*widthOfImage+j-1]>0
                        && origin[(i+1)*widthOfImage+j-0]>0
                        && origin[(i+1)*widthOfImage+j+1]>0)
                        {
                                res[(i)*widthOfImage+j]=1;
                                flag=1;
                                continue;
                        }

                        //模板e
                        if(origin[(i-1)*widthOfImage+j-1]>0
                        && origin[(i-1)*widthOfImage+j+1]==0
                        && origin[(i)*widthOfImage+j-1]>0
                        && origin[(i)*widthOfImage+j-0]>0
                        && origin[(i)*widthOfImage+j+1]==0
                        && origin[(i+1)*widthOfImage+j-1]>0
                        && origin[(i+1)*widthOfImage+j+1]==0)
                        {
                                res[(i)*widthOfImage+j]=1;
                                flag=1;
                                continue;
                        }

                        //模板f
                        if(origin[(i-1)*widthOfImage+j-0]>0
                        && origin[(i)*widthOfImage+j-1]>0
                        && origin[(i)*widthOfImage+j-0]>0
                        && origin[(i)*widthOfImage+j+1]==0
                        && origin[(i+1)*widthOfImage+j-0]==0
                        && origin[(i+1)*widthOfImage+j+1]==0)
                        {
                                res[(i)*widthOfImage+j]=1;
                                flag=1;
                                continue;
                        }

                        //模板g
                        if(origin[(i-1)*widthOfImage+j-0]==0
                        && origin[(i-1)*widthOfImage+j+1]==0
                        && origin[(i)*widthOfImage+j-1]>0
                        && origin[(i)*widthOfImage+j-0]>0
                        && origin[(i)*widthOfImage+j+1]==0
                        && origin[(i+1)*widthOfImage+j-0]>0)
                        {
                                res[(i)*widthOfImage+j]=1;
                                flag=1;
                                continue;
                        }

                        //模板h
                        if(origin[(i-2)*widthOfImage+j-0]>0
                        && origin[(i-1)*widthOfImage+j-1]>0
                        && origin[(i-1)*widthOfImage+j-0]>0
                        && origin[(i-1)*widthOfImage+j+1]>0
                        && origin[(i)*widthOfImage+j-0]>0
                        && origin[(i+1)*widthOfImage+j-1]==0
                        && origin[(i+1)*widthOfImage+j-0]==0
                        && origin[(i+1)*widthOfImage+j+1]==0)
                        {
                                res[(i)*widthOfImage+j]=1;
                                flag=1;
                                continue;
                        }
                }
        }
        for(i=0;i<widthOfImage * heightOfImage;i++)
        {
                if(res[i]==1)
                {
                        origin[i]=0;
                }
        }

    }

 //-------------第二次串行细化
        for( i=2;i<heightOfImage-2;i++)
        {
                for(j=2;j<widthOfImage-2;j++)
                {
                        //缩小后的模板a
                        if(origin[(i-1)*widthOfImage+j-1]==0
                        && origin[(i-1)*widthOfImage+j+1]>0
                        && origin[(i)*widthOfImage+j-1]==0
                        && origin[(i)*widthOfImage+j-0]>0
                        && origin[(i)*widthOfImage+j+1]>0
                        && origin[(i+1)*widthOfImage+j-1]==0
                        && origin[(i+1)*widthOfImage+j+1]>0)
                        {
                                origin[(i)*widthOfImage+j]=0;
                                flag=1;
                                continue;
                        }
                        //缩小后的模板h
                        if(origin[(i-1)*widthOfImage+j-1]>0
                        && origin[(i-1)*widthOfImage+j-0]>0
                        && origin[(i-1)*widthOfImage+j+1]>0
                        && origin[(i)*widthOfImage+j-0]>0
                        && origin[(i+1)*widthOfImage+j-1]==0
                        && origin[(i+1)*widthOfImage+j-0]==0
                        && origin[(i+1)*widthOfImage+j+1]==0)
                        {
                                origin[(i)*widthOfImage+j]=0;
                                flag=1;
                                continue;
                        }
                }
        }
	
	//memcpy(origin, res, sizeof(unsigned char) * widthOfImage * heightOfImage);
	return origin;
}
//基于有效行的细化算法

unsigned char * thinImage_2(unsigned char *origin)
{
	unsigned char *res;
	res = (unsigned char*) malloc (sizeof(unsigned char) * widthOfImage * heightOfImage);
	memset(res, 0, sizeof(unsigned char) * widthOfImage * heightOfImage);
	int flag = 0;
	int check = 0;
	for (int i = 0; i < heightOfImage; ++ i) {
		int left = 0;
		int right = 0;
		flag = 0;
		while (left < widthOfImage && right < widthOfImage) {
			int repair = 0;

			while (left < widthOfImage && !origin[i * widthOfImage + left]) {
				++ left;
			}
			right = left;
			while (right < widthOfImage && origin[i * widthOfImage + right]) {
				++ right;
			}

			if (left <= right && right < widthOfImage) {
				++ res[i * widthOfImage + ((left + right) >> 1)];
				flag = 1;
			}

			if(check) {
				int l = (left + right) >> 1;
				-- l;
				int r = l + 2;
				while (origin[(i - 1) * widthOfImage + l] || origin[i * widthOfImage + l]) {
					if (res[(i - 1) * widthOfImage + l]) {
						res[(i - 1) * widthOfImage + ((left + right) >> 1) - 1] = 1;
						for (int x = l; x < ((left + right) >> 1) - 1; ++ x) {
							if (i >= 2 && res[(i - 2) * widthOfImage + x] == 0) {
								res[(i - 1) * widthOfImage + x] = 1;
							}
						}
					}
					
					-- l;
				}

				while (origin[(i - 1) * widthOfImage + r] || origin[i * widthOfImage + r]) {
					if (res[(i - 1) * widthOfImage + r]) {
						res[(i - 1) * widthOfImage + ((left + right) >> 1) + 1] = 1;
						for (int x = ((left + right) >> 1) + 2; x <= r; ++ x) {
							if (i >= 2 && res[(i - 2) * widthOfImage + x] == 0) {
								res[(i - 1) * widthOfImage + x] = 1;
							}
						}
					}
					++ r;
				}
			}

			left = right;
		}
		
		if (flag) {
			check = 1;
		}
		else {
			check = 0;
		}

	}
	memcpy(origin, res, sizeof(unsigned char) * widthOfImage * heightOfImage);
	return origin;
}

//zhang并行细化算法
unsigned char* thinImage_3(unsigned char *origin)
{
	unsigned char * res;

	int (*getA)(int *x) = [&](int *x) {
		int re = 0;
		for (int i = 2; i <= 8; ++ i) {
			if (x[i] == 0 && x[i + 1] == 1) {
				++ re;
			}
		}
		return re;
	};

	int (*getN)(int *x) = [&](int *x) {
		int re = 0;
		for (int i = 2; i <= 8; ++ i) {
			if (x[i] > 0) {
				++ re;
			}
		}
		return re;
	};

	res = (unsigned char *) malloc (sizeof(unsigned char) * widthOfImage * heightOfImage);
	memset(res, 0, sizeof(unsigned char) * widthOfImage * heightOfImage);

	for (int i = widthOfImage; i < widthOfImage * heightOfImage - widthOfImage; ++ i) {
		int *x = (int *) malloc (sizeof(int) * 10);
		x[1] = origin[i];
		x[2] = origin[i - widthOfImage];
		x[3] = origin[i - widthOfImage + 1];
		x[4] = origin[i + 1];
		x[5] = origin[i + widthOfImage + 1];
		x[6] = origin[i + widthOfImage];
		x[7] = origin[i + widthOfImage - 1];
		x[8] = origin[i - 1];
		x[9] = origin[i - widthOfImage - 1];
		int N = getN(x);
		int A = getA(x);
		if (N <= 6 && N >= 2 
			&& A == 1 
			&& ((x[2] * x[4] * x[6] == 0 && x[4] * x[6] * x[8] == 0) || (x[2] * x[4] * x[8] == 0 && x[2] * x[6] * x[8] == 0))) {
			res[i] = 1;
		}
	}
	
	for(int i = 0; i < widthOfImage * heightOfImage; ++ i) {
		if (res[i]) {
			origin[i] = 0;
		}
	}

	return origin;
}

