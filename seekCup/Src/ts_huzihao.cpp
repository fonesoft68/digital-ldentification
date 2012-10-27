#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "sql.h"

database *nowUsedDatabase = (database *)calloc(1, sizeof(database));
database *allDatabaseRoot = (database *)calloc(1, sizeof(database));
int databaseCnt = 0;

// void swap(table *tmp_table, int i, int j)
// {
//   col *tmp_col = tmp_table->rootCol->next;
//   while (tmp_col) {
//     int cnt = 0;
//     item *tmp_item1 = tmp_col->rootItem, *tmp_item2 = tmp_col->rootItem;
//     while (cnt <= i) {
//       tmp_item1 = tmp_item1->next;
//       ++ cnt;
//     }
//     cnt = 0;
//     while (cnt <= j) {
//       tmp_item2 = tmp_item2->next;
//       ++ cnt;
//     }
//     char *tmp = (char *) calloc (1, sizeof(char) * 256);
//     strcpy(tmp, tmp_item1->res);
//     memset(tmp_item1->res, '\0', sizeof(char) * (strlen(tmp_item1->res) + 1));
//     strcpy(tmp_item1->res, tmp_item2->res);
//     memset(tmp_item2->res, '\0', sizeof(char) * (strlen(tmp_item2->res) + 1));
//     strcpy(tmp_item2->res, tmp);
//     tmp_col = tmp_col->next;
//   }
// }

// #define ASC 1
// #define DESC 2

// table *sort(table *tmp_table, char *name, int rule)
// {
//   col *tmp_col = find(tmp_table, name);
//   if (!tmp_col) {
//     printf(ERROR);
//     return 0;
//   }
//   int j, k;
//   for (j = 0;j < tmp_col->itemCnt;++ j) {
//     for (k = tmp_col->itemCnt - 1;k > j;-- k) {
//       int cnt = 0;
//       item *tmp_item = tmp_col->rootItem;
//       while (cnt <= k - 1) {
// 	tmp_item = tmp_item->next;
// 	++ cnt;
//       }
//       if ((rule == DESC && resCmp(tmp_col->type, tmp_item->res, tmp_item->next->res) > 0) || (rule == ASC && resCmp(tmp_col->type, tmp_item->res, tmp_item->next->res) < 0)) {
// 	swap(tmp_table, k, k - 1);
//       }
//     }
//   }
// }
char Precede(char a, char b) { //判断运算符优先级

    int i, j;

    char Table[8][8] = {

        {' ','+','-','*','/','(',')','='},

        {'+','>','>','<','<','<','>','>'},

        {'-','>','>','<','<','<','>','>'},

        {'*','>','>','>','>','<','>','>'},

        {'/','>','>','>','>','<','>','>'},

        {'(','<','<','<','<','<','=',' '},

        {')','>','>','>','>',' ','>','>'},

        {'=','<','<','<','<','<',' ','='}

    };  //优先级表格

    for(i=0; i<8; i++)

        if(Table[0][i]==a)  //寻找运算符a

            break;

    for(j=0; j<8; j++) //寻找运算符b

        if(Table[j][0]==b)

            break;

    return Table[j][i];

}
bool Calcu_temp(float a, char theta, float b, float *r) { //计算二元表达式的值

    if(theta=='+')
        *r = a + b;
    else if(theta=='-')
        *r = a - b;
    else if(theta=='*')
        *r = a * b;
    else {
        if(fabs(b-0.0)<1e-8)  //如果除数为0，返回错误信息
            return false;
        else
            *r = a / b;
    }
    return true;
}

bool IsOper(char ch) { //判断字符ch是否为运算符

    char ptr[10] = {'+', '-', '*', '/', '(', ')', '='};
    int i;
    for(i=0; i<7; i++) {
        if(ch==ptr[i])
            return true;
    }
    return false;
}

float calculate(char *s)
{
  char ch;
  int i = 0, j, point = 0;
  float a, b, *r = 0, num = 0;
  float *ns = (float *) calloc (1, sizeof(float) * (strlen(s) + 1));
  char *os = (char *) calloc (1, sizeof(char) * (strlen(s) + 1));
  int beg1 = 0, beg2 = 0;
  *(os + beg2) = '=';
  ++ beg2;
  while (s[i] != '\0' || os[beg2 - 1] != '=') {
    if ((s[i] >= '0' && s[i] <= '9') || s[i] == '.') {
      num = 0;
      point = 0;
      if (s[i] == '.') {
	point = 10;
      }
      else {
	num = s[i] - 48;
      }
      j = i + 1;
      while (!IsOper(s[j])) {
	if (s[j] == '.') {
	  point = 10;
	  j ++;
	  continue;
	}
	if (!point) {
	  num = num * 10 + (s[j] - 48);
	}
	else {
	  num = num + 1.0 * (s[j] - 48) / point;
	  point *= 10;
	}
	j ++;
      }
      i = j;
      *(ns + beg1) = num;
      ++ beg1;
    }
    else if (IsOper(s[i])) {
      switch(Precede(s[i], os[beg2 - 1])) {
      case '<':
	*(os + beg2) = s[i ++];
	++ beg2;
	break;
      case '=':
	-- beg2;
	i ++;
	break;
      case '>':
	ch = os[beg2 - 1];
	-- beg2;
	b = ns[beg1 - 1];
	-- beg1;
	a = ns[beg1 - 1];
	-- beg1;
	if (Calcu_temp(a, ch, b, r)) {
	  ns[beg1] = *r;
	  ++ beg1;
	}
	else {
	  printf(ERROR);
	  return 0;
	}
	break;
      }
    }
  }
  return ns[beg1 - 1];
} 
// int main(int argc, char **argv)
// {
//   printf("%f\n", calculate("2.4 * 1.3 + 4.7 / ( 1 + 2.3)"));
//   return 0;
// }

int main(int argc, char *argv[])
{

  //    allDatabaseRoot->next = NULL;
  allDatabaseRoot =  createDatabase("huzi");

  //    allDatabaseRoot->rootTable->next = createTable("  a int  , b float , noe, c text   ");
    //    allDatabaseRoot->rootTable->next->name = "a";
  allDatabaseRoot->rootTable->next = createTable("id int , name text , grade int , address text");
  allDatabaseRoot->rootTable->next->name = "person";
  nowUsedDatabase = allDatabaseRoot;
  insert("insert into person (id , name , address) values (1 , 'yaoq' , 'qiming702')");
    nowUsedDatabase = allDatabaseRoot;
    //    insert("insert into a values (2 , 3.5 , , 'how')");
    //    insert("insert into a values ( 1 , 4.7, , 'foo')");
    //    insert("insert into a values (3, 2.4, , 'bar')");
    showTableContext(allDatabaseRoot->rootTable->next);
    //swap(allDatabaseRoot->rootTable->next, 0, 1);
    sort(allDatabaseRoot->rootTable->next, "name", 1);
    showTableContext(allDatabaseRoot->rootTable->next);
    //    insert("insert into a (b , c ) values (2.3, 'wuhan' )");
    //    alter_parse("alter table b drop column c ");
    if (argc > 1) {
	if (memcpy(argv[1], "drop", strlen(argv[1])) == 0) {
	    //    drop("huzi");
	    printf("%p ***\n", allDatabaseRoot);
	}
	if (memcmp(argv[1], "createTable", strlen(argv[1])) == 0) {
	    //allDatabaseRoot->rootTable = createTable(" int a , float b , noe  ");
	}
    }
}
