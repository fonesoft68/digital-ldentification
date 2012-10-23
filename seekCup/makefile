# $@  表示目标文件
# $^  表示所有的依赖文件
# $<  表示第一个依赖文件
# $?  表示比目标还要新的依赖文件列表
#
#
obj=tmp/alterTable.o tmp/createDatabase.o tmp/createTable.o tmp/delete.o tmp/dropDatabase.o tmp/dropTable.o tmp/insert.o tmp/renameDatabase.o tmp/renameTable.o tmp/select.o tmp/showCol.o \
	tmp/showDatabase.o tmp/truncateTable.o tmp/updata.o tmp/useDatabase.o tmp/foo.o tmp/parse.o

srcfile=Src/sql.h

Bin/ts:$(srcfile) Src/ts.cpp $(obj)
	g++ -o $@ $^ -g

Bin/SeedCup:$(srcfile) Src/SeedCup.cpp $(obj)

Bin/SeedCup:$(srcfile) Src/SeedCup.cpp $(obj)
	g++ -o $@ $^ -g

tmp/alterTable.o:Src/alterTable.cpp
	g++ -c -o $@ $^ -g

tmp/createDatabase.o:Src/createDatabase.cpp
	g++ -c -o $@ $^ -g

tmp/createTable.o:Src/createTable.cpp
	g++ -c -o $@ $^ -g

tmp/delete.o:Src/delete.cpp
	g++ -c -o $@ $^ -g

tmp/dropDatabase.o:Src/dropDatabase.cpp
	g++ -c -o $@ $^ -g

tmp/dropTable.o:Src/dropDatabase.cpp
	g++ -c -o $@ $^ -g

tmp/insert.o:Src/insert.cpp
	g++ -c -o $@ $^ -g

tmp/renameDatabase.o:Src/renameDatabase.cpp
	g++ -c -o $@ $^ -g

tmp/renameTable.o:Src/renameTable.cpp
	g++ -c -o $@ $^ -g

tmp/select.o:Src/select.cpp
	g++ -c -o $@ $^ -g

tmp/showCol.o:Src/showCol.cpp
	g++ -c -o $@ $^ -g

tmp/showDatabase.o:Src/showDatabase.cpp
	g++ -c -o $@ $^ -g

tmp/truncateTable.o:Src/truncateTable.cpp
	g++ -c -o $@ $^ -g

tmp/updata.o:Src/updata.cpp
	g++ -c -o $@ $^ -g

tmp/useDatabase.o:Src/useDatabase.cpp
	g++ -c -o $@ $^ -g

tmp/foo.o:Src/foo.cpp
	g++ -c -o $@ $^ -g

tmp/parse.o:Src/parse.cpp
	g++ -c -o $@ $^ -g

clean:
	rm /tmp/*
