
#include "ocr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxImage 1000 * 1000

int main(int args, char *argv[])
{
  printf("test for c unit\n");
  unsigned char *res;
  res = (unsigned char *) malloc (sizeof(unsigned char) * maxImage);
  memset(res, 0, sizeof(unsigned char) * maxImage);
  if (args > 1) {
	  
    int index = 0;
    if (args > 2) {
      for (int i = 0; argv[2][i]; ++ i) {
        index = index * 10 + (int) (argv[2][i] - '0');
 
      }
    }

    if (memcmp(argv[1], "readImage", strlen(argv[1])) == 0) {
      printf("test for readImage from file\n");
      char name[50] = "res/hub_image/hub_image_1.jpeg";
 
      if (args > 2) {
        memcpy(name, argv[2], sizeof(argv[2]));
      }

      res = (unsigned char*) malloc (sizeof(unsigned char) * maxImage);
      memset(res, 0, sizeof(unsigned char) * maxImage);
      readImageFromFile(res, name);
      binaryImage(res);
	  outPixel(res);
      return 0;
    }

    readImageFromDataBase(res, "res/database", index);
    if (memcmp(argv[1], "is_Num7", strlen(argv[1]) * sizeof(char)) == 0) {
      printf("test for isNum7\n");
      thinImage(res);
      outImage(res);
      printf("%d\n",isNun_7(res));
    }
	if (memcmp(argv[1], "isNun_9", strlen(argv[1])) == 0) {
		printf("test for isNun_9\n");
		thinImage(res);
		outImage(res);
		printf("\n**********%d***********\n", isNun_9(res));
	}
    if (memcmp(argv[1], "isNum5", strlen(argv[1]) * sizeof(char)) == 0) {
      printf("test for isNum5\n");
      thinImage(res);
      printf("%d\n",isNun_5(res));
    }
    if (memcmp(argv[1], "is_Num3", strlen(argv[1]) * sizeof(char)) == 0) {
      printf("test for is_Num3\n");
      thinImage(res);
      outImage(res);
      printf("%d\n",isNun_3(res));
    }
    if (memcmp(argv[1], "isNum2", strlen(argv[1]) *sizeof(char))==0) {
      printf("test for is_Num2\n");
      thinImage(res);
      outImage(res);
      printf("%d\n",isNun_2(res));
    }
    if (memcmp(argv[1], "isNum1", strlen(argv[1]) *sizeof(char))==0) {
      printf("test for least_square\n");
      thinImage(res);
      outImage(res);
      printf("%d\n",isNun_1(res));
    }
	if (memcmp(argv[1], "isNun_6", strlen(argv[1])) == 0) {
		printf("test for 6\n");
		thinImage(res);
		outImage(res);
		printf("***********%d************\n", isNun_6(res));
	}
	if (memcmp(argv[1], "isNun_4", strlen(argv[1])) == 0) {
		printf("test for 4\n");
		thinImage(res);
		outImage(res);
		printf("***********%d************\n", isNun_4(res));
	}
    if (memcmp(argv[1], "thinImage", strlen(argv[1]) * sizeof(char)) == 0) {
      printf("test for thinImage\n");
      thinImage(res);
      outImage(res);
    }
    if (memcmp(argv[1], "remoteNoise", strlen(argv[1]) * sizeof(char)) == 0) {
      printf("test for remoteNoise\n");
      char name[50] = "res/hub_image/hub_image_1.jpeg";
      if (args > 2) {
        strcpy(name, argv[2]);
      }
      printf("%s", name);

      readImageFromFile(res, name);
      binaryImage(res);
      thinImage(res);
      //findCircle(res);
      //smoothImage(res);
      remoteNoise(res);
      outVisual(res);
    }

    if (memcmp(argv[1], "smoothImage", strlen(argv[1])) == 0) {
      printf("test for smoothImage\n");
      smoothImage(res);
      outImage(res);
    }


    if (memcmp(argv[1], "binaryImage", strlen(argv[1])) == 0) {
      printf("test for binarImage\n");
      binaryImage(res);
      outImage(res);
    }

    if (memcmp(argv[1], "readImage", strlen(argv[1])) == 0) {
      printf("test for binaryImage\n");
    }

    if (memcmp(argv[1], "isNun_0", strlen(argv[1])) == 0) {
      printf("test for 0\n");
      thinImage(res);
      outVisual(res);
	  outImage(res);
      int tm = isNun_0(res);
      printf("**************%d*************\n", tm);
    }
<<<<<<< HEAD
   if (memcmp(argv[1], "isNun_4", strlen(argv[1])) == 0) {
      printf("test for 4\n");
      thinImage(res);
      smoothImage(res);
      outVisual(res);
      int tm = isNun_4(res);
      printf("**************%d*************\n", tm);
    }
=======
	if (memcmp(argv[1], "xiaoBoHang", strlen(argv[1])) == 0) {
		printf("test for xiaoBo\n");
		free(res);
		alg(1);
	}
	if (memcmp(argv[1], "edgeDetector", strlen(argv[1])) == 0) {
		printf("test for edgeDetector\n");
		alg(2);
	}
>>>>>>> 0fdcd1466eda38c93d14dfdf5c996d6edd207138

  }
  return 0;
}
