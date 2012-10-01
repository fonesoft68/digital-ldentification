# $@  表示目标文件
# $^  表示所有的依赖文件
# $<  表示第一个依赖文件
# $?  表示比目标还要新的依赖文件列表

testOpencv:ts.o
	g++ -o main ts.o -I /usr/include/opencv -L /usr/lib -lm -lopencv_core -lopencv_highgui

ts.o:ts.cpp
	g++ ts.cpp -c -I /usr/include/opencv

opencv=-I /usr/include/opencv -L /usr/lib -lm -lopencv_core -lopencv_highgui
OBJ=object/thinImage.o object/readImage.o
#################################### for c unit test
test:$(OBJ) src/test.cpp src/ocr.h
	g++ -o $@ $^
####################################

object/readImage.o:src/readImage.cpp src/ocr.h
	g++ -c src/readImage.cpp  -o object/readImage.o

object/thinImage.o:src/thinImage.cpp src/ocr.h
	g++ -c $< -o object/thinImage.o


ocr:$(OBJ) src/ocr.cpp src/ocr.h
	g++ -o $@ $^

clean:
	rm *.o
