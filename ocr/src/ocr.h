#include </usr/include/opencv/cv.h>
#include </usr/include/opencv/highgui.h>

//��ȡͼƬ�����浽һ��char�����У�rgb��ͼƬת��Ϊ256�׵ĻҶȼ�ͼƬ
unsigned char* readImageFromFile(unsigned char *res, char *filePath);

unsigned char* readImageFromDataBase(unsigned char *res, char *filePath, int index);

//��ͼƬ��ֵ����res�����ֵ�����ͼƬ��originΪԭ���ĻҶȽ�ͼƬ
unsigned char* binaryImage(unsigned char *res);

//��ֵ��ͼƬ���룬������ͨ��
unsigned char* remoceNoise(unsigned char *res);

//ƽ������
unsigned char* smoothImage(unsigned char *res);

//ͼƬϸ��
unsigned char* thinImage(unsigned char *res);

//10�����ֵ�ʶ�𣬷���ʶ������֡�����-1��ʾδʶ��
int isNun_0(unsigned char *pic);
int isNun_1(unsigned char *pic);
int isNun_2(unsigned char *pic);
int isNun_3(unsigned char *pic);
int isNun_4(unsigned char *pic);
int isNun_5(unsigned char *pic);
int isNun_6(unsigned char *pic);
int isNun_7(unsigned char *pic);
int isNun_8(unsigned char *pic);
int isNun_9(unsigned char *pic);

//���ͼƬ
int outImage(unsigned char *res);

extern int widthOfImage;
extern int heightOfImage;
