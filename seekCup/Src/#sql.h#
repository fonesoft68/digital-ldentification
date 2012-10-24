typedef enum {
	Int = 1,
	Float = 2,
	Text = 3,
	None = 4
}TYPE;

typedef struct item{
	char *res;
	item *next;
}item;

typedef struct col{
	char *name; 
	TYPE type;
	item *rootItem;
	col *next;
	int itemCnt;
}col;

typedef struct table{
	char *name;
	col *rootCol;
	int colCnt;
	table *next;
}table;

typedef struct database{
	char *name;
	table *rootTable;
	int tableCnt;
}database;

database *nowUsedDatabase;

//创建数据库
database * creatDatabase(char *);

//创建表
table * creatTable(char *);

//改变表的属性，删除，添加，修改
int deleteCol(char *);
int addCol(char *);
int updataCol(char *);

//清空表
int clearTable(char *);

//指定现在使用的DB
int useDatabase(char *);

//删除表
int deleteTable(char *);

//删除数据库
int deleteDatabase(char *);

//重命名表
int renameTable(char *);

//重命名数据库
int renameDatabase(char *);

//从表中选数据
col * select(char *);

//修改表中的数据
int updata(char *);

//删除表中的部分数据
int deleteData(char *);

//向表中插入新的行
int insert(char *);

//显示数据库中的数据
int show(char *);
