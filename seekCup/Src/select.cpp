#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"sql.h"

table *Search(char *,char *,char *,int ,char *);
bool Judge(table *,int ,char *);
char *value(char *);
table *select(const char* Select)
  {
    char *col_name=NULL;
	char *table_name=NULL;
	char *row_limit;
	int order=1;
	char *temp;

	char *selectn=(char *)malloc(sizeof(Select));
    memcpy(selectn,Select,sizeof(Select));

	char SELECT[7]="select";
	char FROM[5]="from";
	char WHERE[6]="where";
    char DESC[5]="desc";
	char INCR[5]="incr";

	temp=strtok (selectn, " ");
    if(strcmp(temp,SELECT)!=0){
		return NULL;
		printf("error");
	}
	temp=strtok (NULL," ");
	col_name=(char *)malloc(sizeof(char)*strlen(temp));
	strcpy(col_name,temp);


	temp=strtok (NULL," ");
	if(strcmp(temp,FROM)!=0){
	    return NULL;
		printf("error");
	}
	temp=strtok (NULL," ");
    table_name=(char *)malloc(sizeof(char)*strlen(temp));
	strcpy(table_name,temp);


    temp=strtok (NULL," ");
	//判断是否有WHERE参数
	if(strcmp(temp,WHERE)==0){
		char *where=strstr(selectn,WHERE);
		//判断是否有参数ORDER BY
		char Iforder[5];
		memcpy(Iforder,selectn+strlen(selectn)-5,4);
		Iforder[5]='\0';
		if(strcmp(Iforder,DESC)==0){
			row_limit=(char *)malloc(sizeof(char)*(strlen(where)-12));
			memcpy(row_limit,where+6,strlen(where)-12);
			order=2;
		}

		else if(strcmp(Iforder,INCR)==0){
			row_limit=(char *)malloc(sizeof(char)*(strlen(where)-12));
			memcpy(row_limit,where+6,strlen(where)-12);
		}
		else{
			row_limit=(char *)malloc(sizeof(char)*(strlen(where)-7));
			memcpy(row_limit,where+6,strlen(where)-6);
		}
	}
    else if(strcmp(temp,DESC)==0){
		order=2;
	}
	return Search(col_name,table_name,row_limit,order,temp);
  }

//根据select函数的解释查找数据库
table *Search(char *col_name,char *table_name,char *row_limit,int order,char *temp)
{
	table *result = NULL;
	col *temp_col_1 = NULL;
	col *temp_col_2 = NULL;
	col *temp_col_3 = NULL;
	item *temp_item_1 = NULL;
	item *temp_item_2 = NULL;
	item *temp_item_3 = NULL;
	table *now_tab=nowUsedDatabase->rootTable;
	int i,j,k;
	for(i = 0 ; i < nowUsedDatabase->tableCnt ; i++){
		if(strcmp(now_tab->name,table_name)==0){
			result=(table *)malloc(sizeof(table));
			strcpy(result->name,now_tab->name);
			result->next = NULL;
			result->rootCol = NULL;
			result->colCnt=now_tab->colCnt;
			break;
		}
		now_tab=now_tab->next;
	}
	if(result==NULL||now_tab->rootCol==NULL||now_tab->rootCol->rootItem==NULL){
		printf("$");
		return NULL;
	}
//复制所有列名到result
	temp_col_1=now_tab->rootCol;
	result->rootCol=temp_col_2;
	temp_col_2=(col *)malloc(sizeof(col));
    strcpy(temp_col_2->name,temp_col_1->name);
	temp_col_2->next=NULL;
	temp_col_2->type=temp_col_1->type;
	temp_col_2->rootItem=NULL;
	temp_col_2->itemCnt=0;
	temp_col_1=temp_col_1->next;
	for(i = 1;i<now_tab->colCnt;i++){
	    temp_col_3 = (col *)malloc(sizeof(col));
		temp_col_3->name = (char *)malloc(sizeof(temp_col_1->name));
		strcpy(temp_col_3->name,temp_col_1->name);
	    temp_col_3->next = NULL;
	    temp_col_3->type = temp_col_1->type;
	    temp_col_3->rootItem = NULL;
	    temp_col_3->itemCnt = 0;
		temp_col_2->next = temp_col_3;
		temp_col_1 = temp_col_1->next;
	}
//找出符合条件的行，存入result

	for(i = 0;i<now_tab->rootCol->itemCnt;i++){
	   if(Judge(now_tab,i,row_limit)){
		   temp_col_1 = result->rootCol;
		   temp_col_2 = now_tab->rootCol;
	   	   for(j = 0;j<now_tab->colCnt;j++){
			   temp_item_2 = temp_col_2->rootItem;
		      for(k = 1;k<i;k++){
				  temp_item_2 = temp_item_2->next;
			  }  
			  temp_item_1 = (item *)malloc(sizeof(item));
			  temp_item_1->res = (char *)malloc(sizeof(temp_item_2->res));
			  memcpy(temp_item_1->res,temp_item_2->res,sizeof(temp_item_2->res));
			  temp_item_3 = temp_col_1->rootItem;
			  temp_col_1->rootItem = temp_item_2;
			  temp_item_2->next = temp_item_2;
			  temp_col_1->itemCnt++;
			  temp_col_1 = temp_col_1->next;
			  temp_col_2 = temp_col_2->next;
		   }
	   }
	}

	if(result->rootCol->itemCnt==0){
		printf("$");
		return NULL;
	}


//将result以orderby的要求排列
//将result中的所选列输出

}

//根据Serech的要求解释row_limit并判断
bool Judge(table * table_judge,int row,char* row_limit)
{
//    char AND[4]="and";
	char BETWEEN[8]="between";
	char LIKE[5]="like";
//	char OR[3]="or";


	if(row_limit==NULL){
		return true;
	}else{
		char *or_div;
		char *and_div;
		or_div=strtok(row_limit," or ");
		and_div=strtok(or_div," and ");


	}
}

//判断between[,],a为需判断的item，b为【，】中内容
bool between(char *a,char *b)
{
	char *min;
	char *max;
	float x,y,z;
	min = strtok(b,",");
	max = strtok(NULL,",");
	if(max==NULL||strtok(NULL,",")!=NULL){
		printf("error");
		return NULL;
	}
	min=value(min);
	max=value(max);
	sscanf(min,"%f",z);
	sscanf(max,"%f",y);
	sscanf(a,"%f",z);
	if(x<=z&&z<=y){
		return true;
	}
	else return false;
}

//判断like[]  str_1为需判别的item str_2为【】中内容
bool like(char *str_1,char *str_2)
{
	int a,b;
	int i,j,k;
	a=strlen(str_1);
	b=strlen(str_2);
	char *Match_map;
	Match_map=(char *)malloc(sizeof(char)*(a+1)*(b+1));
	memset(Match_map,0,(a+1)*(b+1));
	Match_map[0]=1;
	for(i=1;i<=a;i++){   //对目标item进行遍历
		for(j=1;j<=b;j++){//对匹配内容进行遍历
			if(Match_map[(i-1)*(b+1)+j-1]==1){
				if(str_1[i-1]==str_2[j-1]||str_2[j-1]=='?'){
					Match_map[i*(b+1)+j]=1;
					if(i==a&&j<b){
						for(k=j+1;k<=b;k++){
							if(str_2[k]=='*'||str_2[k]=='?'){
								Match_map[i*(b+1)+k]=1;
							}
							else break;
						}
					}
				}
				else if(str_2[j-1]=='*'){   //*可以和一切字符匹配
					for(k=i-1;k<a;k++){
						Match_map[k*(b+1)+j]==1;
					}
				}
			}
		}
		for(k =1;k<=b;k++){
			if(Match_map[i*(b+1)+k]){
				break;
			}
			if(k>b){
				return false;
			}
		}
	}
	if(Match_map[(a+1)*(b+1)-1]==1) return true;
	else return false;
}

//解决select嵌套，复杂数学运算等问题
char *value(char *VALUE)
{

}
