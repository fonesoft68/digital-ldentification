#include "ocr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 int Num_Cir(char*bg)   
 {
   int temp=1; 
   for(int i=0;i<heightOfImage;i++)
   {
      for(int j=1;j<=widthOfImage;j++)
      {
		  if(bg[i*widthOfImage+j]>temp)
		  {
		  temp=bg[i*widthOfImage+j];
		  }
	  }
   }
  return temp-1; 
 }
