#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"sql.h"

database *nowUsedDatabase = (database *)calloc(1, sizeof(database));
database *allDatabaseRoot = (database *)calloc(1, sizeof(database));
int databaseCnt = 0;

int main()
{
  allDatabaseRoot=createDatabase("dan");
  nowUsedDatabase = allDatabaseRoot;
  char a[11]="aksopdlkjl";
  char b[8]="ak?o*l*";
  char c[5]="1234";
  char d[10]="1000,1893";
   const char Select[]="select * from a where col_4>2+3/2";
  // const char Select[]="select col_2,col_3 from a order by col_3 incr";

//  if(like(a,b)){
//    printf("a like b \n");
//  }else printf("a dislike b  \n");
//  if(between(c,d)){
//    printf("c is between d  \n");
// }else printf("c is not between d  \n");
//
    allDatabaseRoot->rootTable->next = createTable(" col_1 text , col_2 text , col_3,col_4 float,col_5 int ");
	allDatabaseRoot->rootTable->next->name = "a"; 
	insert("insert into a values ('A', 'abcde', ,1.5,1)"); 
	insert("insert into a values ('B', 'bcdef', ,2.5,2)"); 
	insert("insert into a values ('C', 'cdefg', ,3.5,3)"); 
	insert("insert into a values ('D', 'defgh', ,4.5,4)");
	insert("insert into a values ('E', 'efghi', ,5.5,5)");
	insert("insert into a values ('F', 'fghij', ,5.5,6)");
	showTableContext(allDatabaseRoot->rootTable->next);
	nowUsedDatabase=allDatabaseRoot;
        nowUsedDatabase->tableCnt=1;
	//	nowUsedDatabase->rootTable->next->rootCol->next->itemCnt=6;

	showTableContext( select(Select));
  //if(Judge(now_tab,row,row_limit)){
    // printf("true");  
    // }else printf("false");

  return 0;
}

