#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"sql.h"
#define ERROR "fuckdian\n"
table *Search(char *,char *,char *,char *,int);
int between(char *,char *);
int like(char *,char *);
int Judge(table *,int ,char *);

int andoror(char *);
int Complex_Judge(table *,int,char *);


table *select(const char* Select)
{
  char *col_name=NULL;
  char *table_name=NULL;
  char *row_limit=NULL;
  int order=1;
  char *odby=NULL;
  char **temp;
  int *p=(int *)calloc(1,sizeof(int));


  char SELECT[7]="select";
  char FROM[5]="from";
  char WHERE[6]="where";
  char DESC[5]="desc";
  char INCR[5]="incr";

  char *selectn=(char *)calloc(1,strlen(Select)+1);
  strcpy(selectn,Select);
  temp=split(selectn," ",p);

  if(strcmp(temp[0],SELECT)!=0){
    printf(ERROR);
    return NULL;
  }


  col_name=(char *)calloc(1,strlen(temp[1])+1);
  strcpy(col_name,temp[1]);


  if(strcmp(temp[2],FROM)!=0){
    printf(ERROR);
    return NULL;
  }
    
  table_name=(char *)calloc(1,strlen(temp[3])+1);
  strcpy(table_name,temp[3]);


  //判断是否有WHERE参数
  if(temp[4]!=NULL&&strcmp(temp[4],WHERE)==0){
    char *where=strstr(selectn,WHERE);
    //判断是否有参数ORDER BY
    if(strstr(selectn,"order by")!=0){
      if(strcmp(temp[*p-1],DESC)==0){
	row_limit=(char *)calloc(1,strlen(where)-strlen(temp[*p-2])-14);
	memcpy(row_limit,where+6,strlen(where)-strlen(temp[*p-2])-21);
	order=2;
	odby=(char *)calloc(1,strlen(temp[*p-2])+1);
	strcpy(odby,temp[*p-2]);	
      }
      else if(strcmp(temp[*p-1],INCR)==0){
	row_limit=(char *)calloc(1,strlen(where)-strlen(temp[*p-2])-14);
	memcpy(row_limit,where+6,strlen(where)-strlen(temp[*p-2])-21);
	order=1;
	odby=(char *)calloc(1,strlen(temp[*p-2])+1);
	strcpy(odby,temp[*p-2]);
      }
      else
	{
	  row_limit=(char *)calloc(1,strlen(where)-strlen(temp[*p-1])-9);
	  memcpy(row_limit,where+6,strlen(where)-strlen(temp[*p-1])-16);
	  order=1;
	  odby=(char *)calloc(1,strlen(temp[*p-1])+1);
	  strcpy(odby,temp[*p-1]);
	}
    }
    else{
      row_limit=(char *)calloc(1,strlen(where)+1);
      memcpy(row_limit,where+6,strlen(where)-6);
    }
  }
  else if(strstr(selectn,"order by")!=0){
    if(strcmp(temp[*p-1],DESC)==0){
      order=2;
      odby=(char *)calloc(1,strlen(temp[*p-2])+1);
      strcpy(odby,temp[*p-2]);
    }
    else if(strcmp(temp[*p-1],INCR)==0){
      order=1;
      odby=(char *)calloc(1,strlen(temp[*p-2])+1);
      strcpy(odby,temp[*p-2]);
    }
    else{
      order=1;
      odby=(char *)calloc(1,strlen(temp[*p-1])+1);
      strcpy(odby,temp[*p-1]);
    }
  }
  return Search(col_name,table_name,row_limit,odby,order);
}

//根据select函数的解释查找数据库
table *Search(char *col_name,char *table_name,char *row_limit,char *odby,int order)
{
  table *result = NULL;
  table *fn_result=NULL;  //最终输出的结果
  col *temp_col_1 = NULL;
  col *temp_col_2 = NULL;
  col *temp_col_3 = NULL;
  char **result_col;
  int *p=(int *)calloc(1,sizeof(int));
  item *temp_item_1 = NULL;
  item *temp_item_2 = NULL;
  item *temp_item_3 = NULL;
  table *now_tab=nowUsedDatabase->rootTable->next;     //
  int i,j,k;
  for(i = 0 ; i < nowUsedDatabase->tableCnt ; i++){
    if(strcmp(now_tab->name,table_name)==0){
      result =(table *)calloc(1,sizeof(table));
      result->name = (char *)calloc(1,strlen(now_tab->name)+1);
      strcpy(result->name,now_tab->name);
      result->next = NULL;
      result->rootCol =(col *)calloc(1,sizeof(col));
      result->colCnt=now_tab->colCnt;
      break;
    }
    now_tab=now_tab->next;
  }
  if(result==NULL){
    printf("error/n");
    return NULL;
  }

  //复制所有列名到result
  temp_col_1=now_tab->rootCol->next;                      //
  temp_col_2=(col *)calloc(1,sizeof(col));
  result->rootCol->next=temp_col_2;                       //
  temp_col_2->name=(char *)calloc(1,strlen(temp_col_1->name)+1); 
  strcpy(temp_col_2->name,temp_col_1->name);
  temp_col_2->next=NULL;
  temp_col_2->type=temp_col_1->type;
  temp_col_2->rootItem=(item *)calloc(1,sizeof(item));
  temp_col_2->itemCnt=0;
  temp_col_1=temp_col_1->next;
  for(i = 1;i<now_tab->colCnt;i++){
    temp_col_3 = (col *)calloc(1,sizeof(col));
    temp_col_3->name = (char *)calloc(1,strlen(temp_col_1->name)+1);
    strcpy(temp_col_3->name,temp_col_1->name);
    temp_col_3->next = NULL;
    temp_col_3->type = temp_col_1->type;
    temp_col_3->rootItem =(item *)calloc(1,sizeof(item));
    temp_col_3->itemCnt = 0;
    temp_col_2->next = temp_col_3;
    temp_col_2=temp_col_3;
    temp_col_1 = temp_col_1->next;
  }
  //找出符合条件的行，存入result
  bool temp_bool=false;
  for(i = 0;i<now_tab->rootCol->next->itemCnt;i++){
    int rt=Complex_Judge(now_tab,i+1,row_limit);
    if(rt==2) return NULL;
    if(rt==1){    //如果符合条件
      bool  temp_bool=true;
      temp_col_1 = result->rootCol->next;               //
      temp_col_2 = now_tab->rootCol->next;              //
      if(temp_col_2->type==None) continue;
      for(j = 0;j<now_tab->colCnt;j++){
	temp_item_2 = temp_col_2->rootItem->next;         //
	for(k = 1;k<i+1;k++){
	  temp_item_2 = temp_item_2->next;
	}  
	temp_item_1 = (item *)calloc(1,sizeof(item));
	temp_item_1->res = (char *)calloc(1,strlen(temp_item_2->res)+1);
	strcpy(temp_item_1->res,temp_item_2->res);
	temp_item_3 = temp_col_1->rootItem->next;         //
	temp_col_1->rootItem->next = temp_item_1;        //
	temp_item_1->next = temp_item_3;
	temp_col_1->itemCnt++;
	temp_col_1 = temp_col_1->next;
	temp_col_2 = temp_col_2->next;
      }
    }
  }

  if(temp_bool){
    printf("$");
    return NULL;
  }


  //将result以orderby的要求排列
  if(odby!=NULL) sort(result,odby,order);
	
  //将result中的所选列输出，若所选列不存在则输出error
  if(strcmp(col_name,"*")==0) return result;              //如果所选列为*号
  bool a;//若存在，则a为true
  result_col=split(col_name,",",p);
  fn_result=(table *)calloc(1,sizeof(table));
  fn_result->name=(char *)calloc(1,sizeof(char)*strlen(result->name)+1);
  strcpy(fn_result->name,result->name);
  fn_result->rootCol=(col *)calloc(1,sizeof(col));
  fn_result->rootCol->next=NULL;
  fn_result->colCnt=*p;
  temp_col_1=(col *)calloc(1,sizeof(col));
  temp_col_2=(col *)calloc(1,sizeof(col));
  temp_col_3=(col *)calloc(1,sizeof(col));
  for(i=*p;i>0;i--)
    {
      temp_col_1=result->rootCol->next;
      a=false;
      for(j=0;j<result->colCnt;j++)
	{
	  if(strcmp(result_col[i-1],temp_col_1->name)==0)
	    {
	      temp_col_2=(col *)calloc(1,sizeof(col));
	      temp_col_2->name=(char *)calloc(1,sizeof(char)*strlen(temp_col_1->name));
	      strcpy(temp_col_2->name,temp_col_1->name);
	      temp_col_2->type=temp_col_1->type;
	      temp_col_2->rootItem=temp_col_1->rootItem;
	      temp_col_2->itemCnt=temp_col_1->itemCnt;
	      temp_col_3=fn_result->rootCol->next;                        //
	      fn_result->rootCol->next=temp_col_2;                        //
	      temp_col_2->next=temp_col_3;
	      a=true;
	    }
	  temp_col_1=temp_col_1->next;
	}
      if(!a){printf("error");return NULL;}
    }
  return fn_result;
}

//根据Serech的要求分割复杂的row_limit为简单的，传给Judge函数，以实现复杂逻辑运算
int Complex_Judge(table *now_tab,int row,char* complex_row_limit)
{
  int *left_paren=(int *)calloc(100,sizeof(int));  //当作一个栈用，压入左括号的位置
  int *orandor=(int *)calloc(100,sizeof(int));     //当作一个栈用，压入or,and，(,)其中or为1,and为2,(为3,)为4
  int p=0,q=0;                                     //用来标记栈顶
  typedef struct element{
    char *res;
    int *tof;
    element *pr;
  }element;

  element *top=(element *)calloc(1,sizeof(element));
  element *temp_ele;
  char *temp_char;
  int i;

  if(complex_row_limit==NULL) return 1;
  if(strstr(complex_row_limit,"and")==NULL&&strstr(complex_row_limit,"or")==NULL){
    	    char * fd=(char *)calloc(1,strlen(complex_row_limit));
	 if(complex_row_limit[0]=='('){

		strncpy(fd,complex_row_limit+1,strlen(complex_row_limit)-2);
	 } 
	  return Judge(now_tab,row,fd);
  }
  for(i=0;i<strlen(complex_row_limit);i++)
    {
      if(complex_row_limit[i]=='('){
	left_paren[p]=i;
	orandor[q]=3;
	if(q!=0&&(orandor[q-1]==1||orandor[q-1]==2)){
	  temp_ele=(element *)calloc(1,sizeof(element));
	  temp_ele->pr=top;
	  top=temp_ele;
	}
	p++;
	q++;
      }
      else if(complex_row_limit[i]==')'){
	if(p==0){
	  printf("error");
	  return 2;
	}
	if(orandor[q-1]==1||orandor[q-1]==2){
	  while(orandor[q-1]!=3){
	    if(orandor[q-1]==2){
	      if(top->tof==NULL){
		top->tof=(int *)calloc(1,sizeof(int));
		  *(top->tof)=Judge(now_tab,row,top->res);
		if(*(top->tof)==2)return 2;
	      }
	      if(top->pr->tof==NULL)
		{
		  top->pr->tof=(int *)calloc(1,sizeof(int));
		  *(top->pr->tof)=Judge(now_tab,row,top->pr->res);
		  if(*(top->pr->tof)==2)return 2;
		}
	      if(*(top->tof)==1&&*(top->pr->tof)==1) *(top->pr->tof)=1;
	      else *(top->pr->tof)=0;
	      top=top->pr;
	      orandor[q-1]=0;
	      q--;
	    }
	    else if(orandor[q-1]==1){
	      if(top->tof==NULL){
		top->tof=(int *)calloc(1,sizeof(int));
		*(top->tof)=Judge(now_tab,row,top->res);
		if(*(top->tof)==2)return 2;
	      }
	      if(top->pr->tof==NULL)
		{
		  top->pr->tof=(int *)calloc(1,sizeof(int));
		  *(top->pr->tof)=Judge(now_tab,row,top->pr->res);
		  if(*(top->pr->tof)==2)return 2;
		}
	      if(*(top->tof)==1||*(top->pr->tof)==1) *(top->pr->tof)=1;
	      else *(top->pr->tof)=0;
	      top=top->pr;
	      orandor[q-1]=0;
	      q--;
	    }
	  }
	  orandor[q-1]=0;
	  q--;
	}
	else{
	  top->res=(char *)calloc(i-left_paren[p-1],sizeof(char));
	  memcpy(top->res,complex_row_limit+left_paren[p-1]+1,i-left_paren[p-1]-1);
	  orandor[q-1]=0;
	  q--;
	}
	left_paren[p-1]=0;
	p--;
      }
      else if(andoror(complex_row_limit+i)==1){
	if(orandor[q-1]==1||orandor[q-1]==3){
	  orandor[q]=1;
	  q++;
	}
	else if(orandor[q-1]==2){
	  while(orandor[q-1]!=2)
	    {
	      if(top->tof==NULL)
		{
		  top->tof=(int *)calloc(1,sizeof(int));
		  *(top->tof)=Judge(now_tab,row,top->res);
		  if(*(top->tof)==2)return 2;
		}
	      if(top->pr->tof==NULL)
		{
		  top->pr->tof=(int *)calloc(1,sizeof(int));
		  *(top->pr->tof)=Judge(now_tab,row,top->pr->res);
		  if(*(top->pr->tof)==2)return 2;
		}
	      if(*(top->tof)==1&&*(top->pr->tof)==1) *(top->pr->tof)=1;
	      else *(top->pr->tof)=0;
	      top=top->pr;
	      orandor[q-1]=0;
	      q--;
	    }
	}
      }
      else if(andoror(complex_row_limit+i)==2){
	orandor[q]=2;
	q++;
      }
    }
  if(left_paren[p-1]!=0){
    printf(ERROR);
    return 2;
  }
  /*do{
    if(orandor[q-1]=2){
      if(top->tof==NULL){
	top->tof=Judge(now_tab,row,top->res);
	if(top->tof==2)return 2;
      }
      if(top->pr->tof==NULL)
	{
	  top->pr->tof=Judge(now_tab,row,top->pr->res);
	  if(top->pr->tof==2)return 2;
	}
      if(top->tof==1&&top->pr->tof==1) top->pr->tof=1;
      else top->pr->tof=2;
      top=top->pr;
      orandor[q-1]=0;
      q--;
    }
    else if(orandor[q-1]==1){
      if(top->tof==NULL){
	top->tof=Judge(now_tab,row,top->res);
	if(top->tof==2)return 2;
      }
      if(top->pr->tof==NULL)
	{
	  top->pr->tof=Judge(now_tab,row,top->pr->res);
	  if(top->pr->tof==2)return 2;
	}
      if(top->tof==1||top->pr->tof==1) top->pr->tof=1;
      else top->pr->tof=2;
      top=top->pr;
      orandor[q-1]=0;
      q--;
    }
  }
  while(q==0);*/
  
  return *(top->tof);
}

int andoror(char *a){
  if(strlen(a)>=2&&a[0]=='o'&&a[1]=='r') return 1;
  if(strlen(a)>=3&&a[0]=='a'&&a[1]=='n'&&a[2]=='d') return 2;
  return 0;
}

//根据Complex_Judge传入的简单row_limit判断某行是否满足Select where的条件
int Judge(table * now_tab,int row,char* row_limit)
{
  //    char AND[4]="and";
  char BETWEEN[8]="between";
  char LIKE[5]="like";
  //char OR[3]="or";
  col *temp_col=now_tab->rootCol->next;               //
  item *temp_item;


  if(row_limit==NULL){
    return 1;
  }else{
    int a=0;
    int k,l,m;
    if(strstr(row_limit,BETWEEN)!=NULL){//判断是否是between语句
      char *where_col;//where选定的行
      char *where_item;//被比较的item内容
      char *area;     //【】内的内容
      bool iscol=false;
      for(k=1;k<=strlen(row_limit);k++){if(row_limit[k-1]==' ')break;}//找出第一次出现空格的位子存入k
      where_col=(char *)calloc(1,sizeof(char)*k);
      memcpy(where_col,row_limit,k-1);
      for(l=0;l<now_tab->colCnt;l++){                        //找出item内容
	if(strcmp(temp_col->name,where_col)==0){
	   iscol=true;
	  if(temp_col->type==Text||temp_col->type==None){   //between的类型不对
	    printf(ERROR);      
	    return 2;
	  }
	  temp_item=temp_col->rootItem->next;                //
	  for(m=1;m<row;m++){temp_item=temp_item->next;}
	  where_item=(char *)calloc(1,strlen(temp_item->res)+1);
	  strcpy(where_item,temp_item->res);
	  break;
	}
	temp_col=temp_col->next;
      }
      if(iscol==false){printf(ERROR);return 2;}
      area=(char *)calloc(1,sizeof(char)*(strlen(row_limit)-k-8));
      memcpy(area,row_limit+k+8,sizeof(char)*(strlen(row_limit)-k-9));
      a=between(where_item,area);
    }else if(strstr(row_limit,LIKE)!=NULL){//判断是否为like语句
      char *where_col;//like选定的行
      char *where_item;//被比较的item内容
      char *area;     //【】内的内容
      bool iscol=false;
      for(k=1;k<=strlen(row_limit);k++){if(row_limit[k-1]==' ')break;}//找出第一次出现空格的位子存入k
      where_col=(char *)calloc(1,sizeof(char)*k);
      memcpy(where_col,row_limit,k-1);
      for(l=0;l<now_tab->colCnt;l++){     //从表中取出item
	if(strcmp(temp_col->name,where_col)==0){
	  iscol=true;
	  if(temp_col->type!=Text){   //like的类型不对
	    printf(ERROR);      
	    return 2;
	  }
	  temp_item=temp_col->rootItem->next;
	  for(m=1;m<row;m++){temp_item=temp_item->next;}
	  where_item=temp_item->res;
	  break;
	}
	temp_col=temp_col->next;
      }
      if(iscol==false){printf(ERROR);return 2;}
      area=(char *)calloc(1,sizeof(char)*(strlen(row_limit)-k-5));
      memcpy(area,row_limit+k+5,sizeof(char)*(strlen(row_limit)-k-6));
      a=like(where_item,area);


      //实现==/~=/>=/<=/>/<
    }else if(strstr(row_limit,"==")!=NULL){
      char **compare;
 //     float *right=(float *)calloc(1,sizeof(float));
 //   float *left =(float *)calloc(1,sizeof(float));
      float right=NULL;
      float left=NULL;
      int *r=(int *)calloc(1,sizeof(int));
      bool iscol=false;
      TYPE temp_type=None;
      compare=split(row_limit,"==",r); //将比较操作符两边分开
      if(*r!=2){printf(ERROR);return 2;}
      for(l=0;l<now_tab->colCnt;l++){     //从表中取出item
	if(strcmp(temp_col->name,compare[0])==0){
	  iscol=true;
	  temp_type = temp_col->type;
	  if(temp_col->type==None){   //类型不对
	    printf(ERROR);      
	    return 2;
	  }
	  temp_item=temp_col->rootItem->next;
	  for(m=1;m<row;m++){temp_item=temp_item->next;}
	  compare[0]=temp_item->res;
	  break;
	}
	temp_col=temp_col->next;
      }
      if(iscol==false){printf(ERROR);return 2;}
//      compare[1]=value(compare[1]);
      if(temp_type==Text){
		  compare[0]=cut(compare[0],'\'','\'');
		  if(strcmp(compare[0],compare[1])==0) a=1;
      }else{
//         sscanf(compare[0],"%f",left);
//         sscanf(compare[1],"%f",right);
         left=calculate(compare[0]);
         right=calculate(compare[1]);
         if(left==right){a=1;}
	  }
    }else if(strstr(row_limit,"~=")!=NULL){                           //~=
      char **compare;
//      float *right=(float *)calloc(1,sizeof(float));
	  float right=NULL;
	  float left=NULL;
  //    float *left =(float *)calloc(1,sizeof(float));
      int *r=(int *)calloc(1,sizeof(int));
      TYPE temp_type=None;
      bool iscol=false;
      compare=split(row_limit,"~=",r);
      if(*r!=2){printf(ERROR);return 2;}
      for(l=0;l<now_tab->colCnt;l++){     //从表中取出item
	    if(strcmp(temp_col->name,compare[0])==0){
	      iscol=true;
	      temp_type = temp_col->type;
	      if(temp_col->type==None){   //类型不对
	        printf(ERROR);      
	        return 2;
	      }
	      temp_item=temp_col->rootItem->next;
	      for(m=1;m<row;m++){temp_item=temp_item->next;}
	      compare[0]=temp_item->res;
	      break;
	    }
	    temp_col=temp_col->next;
      }
      if(iscol==false){printf(ERROR);return 2;}
//      compare[1]=value(compare[1]);
//      sscanf(compare[0],"%f",left);
//      sscanf(compare[1],"%f",right);
       if(temp_type==Text){
		  compare[0]=cut(compare[0],'\'','\'');
		  if(strcmp(compare[0],compare[1])==0) a=1;
	   }else{
       left=calculate(compare[0]);
	   right=calculate(compare[1]);
       if(left!=right){a=1;}
	   }
    }else if(strstr(row_limit,">=")!=NULL){                    //>=
      char **compare;
      //float *right=(float *)calloc(1,sizeof(float));
      //float *left =(float *)calloc(1,sizeof(float));
	  float left;
	  float right;
      int *r=(int *)calloc(1,sizeof(int));
      bool iscol=false;
      compare=split(row_limit,">=",r);
      if(*r!=2){printf(ERROR);return 2;}
      for(l=0;l<now_tab->colCnt;l++){     //从表中取出item
	if(strcmp(temp_col->name,compare[0])==0){
	  iscol=true;
	  if(temp_col->type==Text||temp_col->type==None){   //类型不对
	    printf(ERROR);      
	    return 2;
	  }
	  temp_item=temp_col->rootItem->next;
	  for(m=1;m<row;m++){temp_item=temp_item->next;}
	  compare[0]=temp_item->res;
	  break;
	}
	temp_col=temp_col->next;
      }
      if(iscol==false){printf(ERROR);return 2;}
      //compare[1]=value(compare[1]);
      //sscanf(compare[0],"%f",left);
      //sscanf(compare[1],"%f",right);
	  left=calculate(compare[0]);
	  right=calculate(compare[1]);
      if(left>=right){a=1;}
    }else if(strstr(row_limit,"<=")!=NULL){                   //<=
      char **compare;
      //float *right=(float *)calloc(1,sizeof(float));
      //float *left =(float *)calloc(1,sizeof(float));
	  float left=NULL;
	  float right=NULL;
      int *r=(int *)calloc(1,sizeof(int));
      bool iscol=false;
      compare=split(row_limit,"<=",r);
      if(*r!=2){printf("error");return 2;}
      for(l=0;l<now_tab->colCnt;l++){     //从表中取出item
	if(strcmp(temp_col->name,compare[0])==0){
	  iscol=true;
	  if(temp_col->type==Text||temp_col->type==None){   //类型不对
	    printf(ERROR);      
	    return 2;
	  }
	  temp_item=temp_col->rootItem->next;
	  for(m=1;m<row;m++){temp_item=temp_item->next;}
	  compare[0]=temp_item->res;
	  break;
	}
	temp_col=temp_col->next;
      }
      if(iscol==false){printf(ERROR);return 2;}
      //compare[1]=value(compare[1]);
      //sscanf(compare[0],"%f",left);
      //sscanf(compare[1],"%f",right);
	  left=calculate(compare[0]);
	  right=calculate(compare[1]);
      if(left<=right){a=1;}
    }else if(strstr(row_limit,">")!=NULL){                  //>
      char **compare;
      //    float *right=(float *)calloc(1,sizeof(float));
      //    float *left =(float *)calloc(1,sizeof(float));
      float left;
      float right;
      int *r=(int *)calloc(1,sizeof(int));
      bool iscol=false;
      compare=split(row_limit,">",r);
      if(*r!=2){printf(ERROR);return 2;}
      for(l=0;l<now_tab->colCnt;l++){     //从表中取出item
	if(strcmp(temp_col->name,compare[0])==0){
          iscol=true;
	  if(temp_col->type==Text||temp_col->type==None){   //类型不对
	    printf(ERROR);      
	    return 2;
	  }
	  temp_item=temp_col->rootItem->next;
	  for(m=1;m<row;m++){
	    temp_item=temp_item->next;
	  }
	  compare[0]=temp_item->res;
	  break;
	}
	temp_col=temp_col->next;
      }
      if(iscol==false){printf(ERROR); return 2;}
      //compare[1]=value(compare[1]);
      //      sscanf(compare[0],"%f",left);
      //     sscanf(compare[1],"%f",right);
      left=calculate(compare[0]);
      right=calculate(compare[1]);
      if(left>right){a=1;}
    }else if(strstr(row_limit,"<")!=NULL){                   //<
      char **compare;
      //float *right=(float *)calloc(1,sizeof(float));
      //float *left =(float *)calloc(1,sizeof(float));
	  float left;
	  float right;
      int *r=(int *)calloc(1,sizeof(int));
      bool iscol=false;
      compare=split(row_limit,"<",r);
      if(*r!=2){printf(ERROR);return 2;}
      for(l=0;l<now_tab->colCnt;l++){     //从表中取出item
	if(strcmp(temp_col->name,compare[0])==0){
	  iscol=true;
	  if(temp_col->type==Text||temp_col->type==None){   //类型不对
	    printf(ERROR);      
	    return 2;
	  }
	  temp_item=temp_col->rootItem->next;
	  for(m=1;m<row;m++){temp_item=temp_item->next;}
	  compare[0]=temp_item->res;
	  break;
	}
	temp_col=temp_col->next;
      }
      if(iscol==false){printf(ERROR);return 2;}
      //compare[1]=value(compare[1]);
      //sscanf(compare[0],"%f",left);
      //sscanf(compare[1],"%f",right);

	  left=calculate(compare[0]);
	  right=calculate(compare[1]);
      if(left<right){a=1;}
    }
    return a;
  }
}

//判断between[,],a为需判断的item，b为【，】中内容
int between(char *a,char *b)
{
  char *min;
  char *max;
  float x=NULL;
  float y=NULL;
  float z=NULL;
  min = strtok(b,",");
  max = strtok(NULL,",");
  if(max==NULL||strtok(NULL,",")!=NULL){
    printf(ERROR);
    return 2;
  }
  //min=value(min);
  //max=value(max);
  x=calculate(min);
  y=calculate(max);
  z=calculate(a);
  if(x<=z&&z<=y){
    return 1;
  }
  else return 0;
}

//判断like[]  str_1为需判别的item str_2为【】中内容
int like(char *str_1,char *str_2)
{
  int a,b;
  int i,j,k;
  a=strlen(str_1);
  b=strlen(str_2);
  int *Match_map;
  Match_map=(int *)calloc(1,sizeof(int)*(a+1)*(b+1));
  memset(Match_map,0,(a+1)*(b+1));
  Match_map[0]=1;
  for(i=1;i<=a;i++){   //对目标item进行遍历
    for(j=1;j<=b;j++){//对匹配内容进行遍历
      if(Match_map[(i-1)*(b+1)+j-1]==1){
	if(str_1[i-1]==str_2[j-1]||str_2[j-1]=='?'){
	  Match_map[i*(b+1)+j]=1;
	  if(i==a&&j<b){                           
	    for(k=j+1;k<=b;k++){
	      if(str_2[k-1]=='*'||str_2[k-1]=='?'){    //考虑*与？结尾的情况
		Match_map[i*(b+1)+k]=1;
	      }
	      else break;
	    }
	  }
	}
	else if(str_2[j-1]=='*'){   //*可以和一切字符匹配
	  for(k=i-1;k<=a;k++){
	    Match_map[k*(b+1)+j]=1;
	  }
	}
      }
    }
    for(k =1;k<=b;k++){
      if(Match_map[i*(b+1)+k]==1){
	break;
      }
    }
    if(k>b+1){
      return 0;
    }
  }
  if(Match_map[a*(b+1)+b]==1) return 1;
  else return 0;
}
