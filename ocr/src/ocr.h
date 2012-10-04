unsigned char* readImageFromFile(unsigned char *res, char *filePath);

unsigned char* readImageFromDataBase(unsigned char *res, char *filePath, int index);

//将图片二值化，res保存二值化后的图片，origin为原来的灰度阶图片
unsigned char* binaryImage(unsigned char *res);

//二值化图片除噪，基于连通性
unsigned char* remoteNoise(unsigned char *res);

//平滑处理
unsigned char* smoothImage(unsigned char *res);

//图片细化
unsigned char* thinImage(unsigned char *res);

//10个数字的识别，返回识别的数字。返回-1表示未识别。
float least_squares_method(unsigned char *res);

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

int Num_Cir(unsigned char *bg); //数圈圈^_^
float Length(unsigned char *res);//算总线条长度
//输出图片
int outImage(unsigned char *res);

//输出像素
int outPixel(unsigned char *res);

//用opencv输出图像
int outVisual(unsigned char *res);

extern int widthOfImage;
extern int heightOfImage;        
