#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"sql.h"

database *nowUsedDatabase = (database *)calloc(1, sizeof(database));
database *allDatabaseRoot = (database *)calloc(1, sizeof(database));
int databaseCnt = 0;

int main()
{
  createDatabase("dan");
  nowUsedDatabase = allDatabaseRoot;
  char a[11]="aksopdlkjl";
  char b[8]="ak?o*l*";
  char c[5]="1234";
  char d[10]="1000,1893";
  const char Select[]="select col_1,col_2,col_3 from table where col_3>5 desc";
  if(like(a,b)){
    printf("a like b \n");
  }else printf("a dislike b  \n");
  if(between(c,d)){
    printf("c is between d  \n");
  }else printf("c is not between d  \n");
  select(Select);
  
  //if(Judge(now_tab,row,row_limit)){
    // printf("true");  
    // }else printf("false");

  return 0;
}

