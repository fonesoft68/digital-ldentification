#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"sql.h"

database *nowUsedDatabase = (database *)calloc(1, sizeof(database));
database *allDatabaseRoot = (database *)calloc(1, sizeof(database));
int databaseCnt = 0;
bool Judge(table*,int,char*);
int main()
{
  createDatabase("dan");
  nowUsedDatabase = allDatabaseRoot;
  char a[11]="aksopdlkjl";
  char b[8]="ak?o*l*";
  char c[5]="1234";
  char d[10]="1000,1893";
  if(like(a,b)){
    printf("a like b \n");
  }else printf("a dislike b  \n");
  if(between(c,d)){
    printf("c is between d  \n");
  }else printf("c is not between d  \n");

  
  //if(Judge(now_tab,row,row_limit)){
    // printf("true");  
    // }else printf("false");
        bool e=false;
	int i,j,k,l,m;
	int *p = (int *)malloc(sizeof(int));
	int *q = (int *)malloc(sizeof(int));
    char row_limit[51] = "457 between[122,522.83] and 7<=8 or ioop like[io*]";
	char **or_div=split(row_limit," or ",p);
	for(i=0;i<*p;i++){
	    char **and_div=split(or_div[i]," and ",q);
	    for(j=0;j<*q;j++){
		if(strstr(and_div[j],BETWEEN)!=NULL){//判断是否是between语句
		  char *where_col;
		    for(k=1;k<=strlen(and_div[j]);k++){if(and_div[j][k-1]==' ')break;}//找出第一次出现空格的位子存入k
		    where_col=(char *)malloc(sizeof(char)*i);
		    memcpy(where_col,and_div[j],i-1);
		    memcpy[i-1]='\0';
		    area=(char *)malloc(sizeof(char)*(strlen(and_div[j])-i-8));
		    memcpy(area,and_div[j]+i+8,sizeof(char)*(strlen(and_div[j]-i-9)]
			   area[strlen(and_div[j])-i-9]='\0';    
		    e=between(where_col,area);

		}else if(strstr(and_div[j],LIKE)!=NULL){//判断是否为like语句
		    char *where_col;//like选定的行
		    char *area;     //【】内的内容
		    for(k=1;k<=strlen(and_div[j]);k++){if(and_div[j][k-1]==' ')break;}//找出第一次出现空格的位子存入k
		    where_col=(char *)malloc(sizeof(char)*i);
		    memcpy(where_col,and_div[j],i-1);
                    where_col[i]='\0';
		    area=(char *)malloc(sizeof(char)*(strlen(and_div[j])-i-5));
		    memcpy(area,and_div[j]+i+5,sizeof(char)*(strlen(and_div[j])-i-6));
		    area[strlen(and_div[j])-i-6]='\0';
		    e=like(where_item,area);
		    //实现==/~=/>=/<=/>/<
		}else if(strstr(and_div[j],"==")!=NULL){
		    char **compare;
		    float *right=NULL,*left=NULL;
		    int *r=(int *)malloc(sizeof(int));
		    compare=split(and_div[j],"==",r); //将比较操作符两边分开，暂没考虑比较符两侧可能的空格

		    compare[1]=value(compare[1]);
		    sscanf(compare[0],"%f",left);
		    sscanf(compare[1],"%f",right);
		    if(*left==*right){e=true;}
		}else if(strstr(and_div[j],"~=")!=NULL){
		    char **compare;
		    float *right=NULL,*left=NULL;
		    int *r=(int *)malloc(sizeof(int));
		    compare=split(and_div[j],"~=",r);


		    compare[1]=value(compare[1]);
		    sscanf(compare[0],"%f",left);
		    sscanf(compare[1],"%f",right);
		    if(*left!=*right){e=true;}
		}else if(strstr(and_div[j],">=")!=NULL){
		    char **compare;
		    float *right=NULL,*left=NULL;
		    int *r=(int *)malloc(sizeof(int));
		    compare=split(and_div[j],">=",r);


		    compare[1]=value(compare[1]);
		    sscanf(compare[0],"%f",left);
		    sscanf(compare[1],"%f",right);
		    if(*left>=*right){e=true;}
		}else if(strstr(and_div[j],"<=")!=NULL){
		    char **compare;
		    float *right=NULL,*left=NULL;
		    int *r=(int *)malloc(sizeof(int));
		    compare=split(and_div[j],"<=",r);

		    compare[1]=value(compare[1]);
		    sscanf(compare[0],"%f",left);
		    sscanf(compare[1],"%f",right);
		    if(*left<=*right){e=true;}
		}else if(strstr(and_div[j],">")!=NULL){
		    char **compare;
		    float *right=NULL,*left=NULL;
		    int *r=(int *)malloc(sizeof(int));
		    compare=split(and_div[j],">",r);}

		    compare[1]=value(compare[1]);
		    sscanf(compare[0],"%f",left);
		    sscanf(compare[1],"%f",right);
		    if(*left>*right){a=true;}
		}else if(strstr(and_div[j],"<")!=NULL){
		    char **compare;
		    float *right=NULL,*left=NULL;
		    int *r=(int *)malloc(sizeof(int));
		    compare=split(and_div[j],"<",r);
		    compare[1]=value(compare[1]);
		    sscanf(compare[0],"%f",left);
		    sscanf(compare[1],"%f",right);
		    if(*left<*right){e=true;}
		}
		if(e=false){break;}
	    }
	    if(e=true){break;}
	}
        if(e) printf("e=true");
	else printf("e=false");

  return 0;
}

