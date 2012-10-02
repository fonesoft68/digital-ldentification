#include <cv.h>
#include <highgui.h>
#pragma comment( lib, "cv.lib" )
#pragma comment( lib, "cxcore.lib" )
#pragma comment( lib, "highgui.lib" )
int main()
{
	IplImage* src=cvLoadImage("/home/huzihao/digital-ldentification/ocr/res/hub_image/hub_image_1.jpeg",0);
	int size=256;
	float range[]={0,255};
	float* ranges[]={range};
	CvHistogram* hist=cvCreateHist(1,&size,CV_HIST_ARRAY,ranges,1);
	cvCalcHist(&src,hist,0,NULL);
	float max=0;
	cvGetMinMaxHistValue(hist,NULL,&max,NULL,NULL);
	IplImage* dst=cvCreateImage(cvSize(400,300),8,3);
	cvSet(dst,cvScalarAll(255),0);
	double bin_width=(double)dst->width/size;
	double bin_unith=(double)dst->height/max;
	for(int i=0;i<size;i++)
	{
		CvPoint p0=cvPoint(i*bin_width,dst->height);
		CvPoint p1=cvPoint((i+1)*bin_width,dst->height-cvGetReal1D(hist->bins,i)*bin_unith);
		cvRectangle(dst,p0,p1,cvScalar(0,255),-1,8,0);
	}
	cvNamedWindow("src",1);
	cvShowImage("src",src);
	cvNamedWindow("dst",1);
	cvShowImage("dst",dst);
	cvWaitKey(0); 
	cvDestroyAllWindows();
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	return 0;
}
