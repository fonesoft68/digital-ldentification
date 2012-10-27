#define ERROR "error\n"

typedef enum {
	Int = 1,
	Float = 2,
	Text = 3,
	None = 4
}TYPE;

typedef struct item{
	char *res;
	item *next;
	TYPE type;
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
extern int databaseCnt;

//创建数据库
database * createDatabase(char *);

//创建表
table * createTable(char *);

//改变表的属性，删除，添加，修改
int deleteCol(const char *);
int addCol(const char *);
int updataCol(const char *);

//清空表
int clearTable(const char *);

//指定现在使用的DB
int useDatabase(char *);

//删除表
int deleteTable(const char *);

//删除数据库
int deleteDatabase(const char *);

//重命名表
int renameTable(char *, char *);

//重命名数据库
int renameDatabase(char *, char *);

//从表中选数据
table * select(const char *);

//LIKE匹配
bool like(char *,char *);
//BETWEEN
bool between(char *,char *);
//Judge判断某行是否合要求
int Judge(table *,int,char *);

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
int showDatabase();

int altertable(const char *);





int showTestDatabase();
int showTableContext(table *);
int showCol(char *tableName);
int nameCheck(char *name);
int freeItem(item *i);
int freeCol(col *c);
int freeTable(table *t);
int freeDatabase(database *d);
int alter_parse(char *);
int showTableName(char *);
int showItem(item *);
int showColName(col *);
char **showDatabase(int *cnt);
char **showTable(database *, int *);
char **showTableCol(char *, int *);
char **showDatabaseTable(char *, int *);
int strCmp(char *, char *);
int outputForOrder(char **, int *, int);
int show_parse(char *);
col *find(table * tb, char *);
int resCmp(TYPE type, char *, char *);
void swap(table *, int i, int j);
table *sort(table *, char *, int );
