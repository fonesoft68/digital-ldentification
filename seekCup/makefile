# $@  表示目标文件
# $^  表示所有的依赖文件
# $<  表示第一个依赖文件
# $?  表示比目标还要新的依赖文件列表
#
#
obj=tmp/alterTable.o tmp/createDatabase.o tmp/createTable.o tmp/delete.o tmp/drop.o tmp/insert.o tmp/renameDatabase.o tmp/renameTable.o tmp/select.o tmp/showCol.o \
	tmp/showDatabase.o tmp/truncateTable.o tmp/updata.o tmp/useDatabase.o tmp/foo.o tmp/parse.o tmp/show.o

srcfile=Src/sql.h

Bin/ts:$(srcfile) Src/ts.cpp $(obj)
	g++ -o $@ $^ -g -Wwrite-strings

Bin/ts_huzihao:$(srcfile) Src/ts_huzihao.cpp $(obj)
	g++ -o $@ $^ -g -Wwrite-strings

Bin/ts_dengzhe:$(srcfile) Src/ts_dengzhe.cpp $(obj)
	g++ -o $@ $^ -g -Wwrite-strings

Bin/SeedCup:$(srcfile) Src/SeedCup.cpp $(obj)
	g++ -o $@ $^ -g -Wwrite-strings

tmp/alterTable.o:Src/alterTable.cpp  $(srcfile)
	g++ -c -o $@ $< -g -Wwrite-strings

tmp/createDatabase.o:Src/createDatabase.cpp $(srcfile)
	g++ -c -o $@ $< -g -Wwrite-strings

tmp/createTable.o:Src/createTable.cpp $(srcfile)
	g++ -c -o $@ $< -g -Wwrite-strings

tmp/delete.o:Src/delete.cpp $(srcfile)
	g++ -c -o $@ $< -g -Wwrite-strings

tmp/drop.o :Src/drop.cpp $(srcfile)
	g++ -c -o $@ $< -g -Wwrite-strings

tmp/insert.o:Src/insert.cpp $(srcfile)
	g++ -c -o $@ $< -g -Wwrite-strings

tmp/renameDatabase.o:Src/renameDatabase.cpp $(srcfile)
	g++ -c -o $@ $< -g -Wwrite-strings

tmp/renameTable.o:Src/renameTable.cpp $(srcfile)
	g++ -c -o $@ $< -g -Wwrite-strings

tmp/select.o:Src/select.cpp $(srcfile)
	g++ -c -o $@ $< -g -Wwrite-strings

tmp/showCol.o:Src/showCol.cpp $(srcfile)
	g++ -c -o $@ $< -g -Wwrite-strings

tmp/showDatabase.o:Src/showDatabase.cpp $(srcfile)
	g++ -c -o $@ $< -g -Wwrite-strings

tmp/truncateTable.o:Src/truncateTable.cpp $(srcfile)
	g++ -c -o $@ $< -g -Wwrite-strings

tmp/updata.o:Src/updata.cpp $(srcfile)
	g++ -c -o $@ $< -g -Wwrite-strings

tmp/useDatabase.o:Src/useDatabase.cpp $(srcfile)
	g++ -c -o $@ $< -g -Wwrite-strings

tmp/foo.o:Src/foo.cpp $(srcfile)
	g++ -c -o $@ $< -g -Wwrite-strings

tmp/parse.o:Src/parse.cpp $(srcfile)
	g++ -c -o $@ $< -g -Wwrite-strings

tmp/show.o:Src/show.cpp $(srcfile)
	g++ -c -o $@ $< -g -Wwrite-strings

clean:
	rm /tmp/*
