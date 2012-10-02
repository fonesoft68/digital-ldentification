# $@  表示目标文件
# $^  表示所有的依赖文件
# $<  表示第一个依赖文件
# $?  表示比目标还要新的依赖文件列表

testOpencv:ts.o
	g++ -o main ts.o -I /usr/include/opencv -L /usr/lib -lm -lopencv_core -lopencv_highgui

ts.o:ts.cpp
	g++ ts.cpp -c -I /usr/include/opencv

opencv=-I /usr/include/opencv -L /usr/lib -lm -lopencv_core -lopencv_highgui
OBJ=object/readImage.o object/thinImage.o object/binaryImage.o object/smoothImage.o \
	object/remoteNoise.o object/inNun_0.o object/inNun_1.o object/inNun_2.o object/inNun_3.o object/inNun_4.o object/inNun_5.o object/inNun_6.o object/inNun_7.o object/inNun_8.o object/inNun_9.o

#################################### for c unit test
ts:$(OBJ) src/test.cpp src/ocr.h
	g++ -o $@ $^ $(opencv)
####################################

object/readImage.o:src/readImage.cpp src/ocr.h
	g++ -c $< -o object/readImage.o $(opencv)

object/thinImage.o:src/thinImage.cpp src/ocr.h
	g++ -c $< -o object/thinImage.o

object/binaryImage.o:src/binaryImage.cpp src/ocr.h
	g++ -c $< -o $@

object/smoothImage.o:src/smoothImage.cpp src/ocr.h
	g++ -c $< -o $@

object/remoteNoise.o:src/remoteNoise.cpp src/ocr.h
	g++ -c $< -o $@

object/inNun_0.o:src/isNun_0.cpp src/ocr.h
	g++ -c $< -o $@
object/inNun_1.o:src/isNun_1.cpp src/ocr.h
	g++ -c $< -o $@
object/inNun_2.o:src/isNun_2.cpp src/ocr.h
	g++ -c $< -o $@
object/inNun_3.o:src/isNun_3.cpp src/ocr.h
	g++ -c $< -o $@
object/inNun_4.o:src/isNun_4.cpp src/ocr.h
	g++ -c $< -o $@
object/inNun_5.o:src/isNun_5.cpp src/ocr.h
	g++ -c $< -o $@
object/inNun_6.o:src/isNun_6.cpp src/ocr.h
	g++ -c $< -o $@
object/inNun_7.o:src/isNun_7.cpp src/ocr.h
	g++ -c $< -o $@
object/inNun_8.o:src/isNun_8.cpp src/ocr.h
	g++ -c $< -o $@
object/inNun_9.o:src/isNun_9.cpp src/ocr.h
	g++ -c $< -o $@

ocr:$(OBJ) src/ocr.cpp src/ocr.h
	g++ -o $@ $^ $(opencv)

clean:
	rm *.o
