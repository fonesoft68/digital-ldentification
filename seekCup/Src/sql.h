#define DEBUGi

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
	database *next;
}database;

extern database *nowUsedDatabase;
extern database *allDatabaseRoot;

//创建数据库
database * createDatabase(const char *);

//创建表
table * createTable(const char *);

//改变表的属性，删除，添加，修改
int deleteCol(const char *);
int addCol(const char *);
int updataCol(const char *);

//清空表
int clearTable(const char *);

//指定现在使用的DB
int useDatabase(const char *);

//删除表
int deleteTable(const char *);

//删除数据库
int deleteDatabase(const char *);

//重命名表
int renameTable(const char *);

//重命名数据库
int renameDatabase(const char *);

//从表中选数据
table * select(const char *);

//LIKE匹配
bool Like(char *,char *);

//修改表中的数据
int updata(const char *);

//删除表中的部分数据
int deleteData(const char *);

//向表中插入新的行
int insert(const char *);

//显示数据库中的数据
int show(const char *);

int drop(const char *);

int* go(char *module);
int* findString(char *query, char *module, int *go); 
int toLowCase(char *str);
int parseCommand(char * command);
char ** split(char *str, char *split, int *cnt);
int showDatabase(char *name);

int altertable(const char *);
<<<<<<< HEAD
=======

>>>>>>> 6f0b89ceb697a7db9c939c0b20723876f0e42ed6
int showTestDatabase();
int showTable(char *databaseName);
int showCol(char *tableName);
int nameCheck(char *name);
