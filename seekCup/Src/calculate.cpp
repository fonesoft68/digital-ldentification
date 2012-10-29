#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "sql.h"
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
int IsOper(char ch) { //判断字符ch是否为运算符

    char ptr[10] = {'+', '-', '*', '/', '(', ')', '='};
    int i;
    for(i=0; i<7; i++) {
        if(ch==ptr[i])
          return 1;
    }
    return 0;
}
int check(char * s) 
{
  int flag1 = 0, flag2 = 0;
  int i;
  for (i = 0;i < strlen(s);++ i){
    if (*(s + i) == '(') {
      ++ flag1;
    }
    if (*(s + i) == ')') {
      -- flag1;
    }
    if (IsOper(s[i]) && IsOper(s[i + 1])) {
      flag2 = 1;
    }
  }
  if (flag1 && flag2) {
    return 0;
  }
  return 1;
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
  char *str = (char *) calloc (1, sizeof(char) * (strlen(s) + 1));
  int k = 0;
  while (*(s + i)) {
    if (*(s + i) != ' ') {
      *(str + k) = *(s + i);
      ++ k;
    }
    ++ i;
  }
  if (!check(str)) {
    printf(ERROR);
    return 0;
  }
  *(str + k) = '=';
  i = 0;
  while (str[i] != '=' || os[beg2 - 1] != '=') {
    if ((str[i] >= '0' && str[i] <= '9') || str[i] == '.') {
      num = 0;
      point = 0;
      if (str[i] == '.') {
	point = 10;
      }
      else {
	num = str[i] - 48;
      }
      j = i + 1;
      while (!IsOper(str[j])) {
	if (str[j] == '.') {
	  point = 10;
	  j ++;
	  continue;
	}
	if (!point) {
	  num = num * 10 + (str[j] - 48);
	}
	else {
	  num = num + 1.0 * (str[j] - 48) / point;
	  point *= 10;
	}
	j ++;
      }
      i = j;
      *(ns + beg1) = num;
      ++ beg1;
    }
    else if (IsOper(str[i])) {
      switch(Precede(str[i], os[beg2 - 1])) {
      case '<':
	*(os + beg2) = str[i ++];
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
	if (ch == '+') {
	  ns[beg1] = a + b;
	}
	else if (ch == '-') {
	  ns[beg1] = a - b;
	}
	else if (ch == '*') {
	  ns[beg1] = a * b;
	}
	else if (ch == '/') {
	  if ((b - 0.0) < 1e-8) {
	    return 0;
	  }
	  else {
	    ns[beg1] = a / b;
	  }
	}
	++ beg1;
	break;
      }
    }
  }
  return ns[beg1 - 1];
} 
