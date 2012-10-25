#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "sql.h"

// int drop(const char * str)
// {
//   char drop[5];
//   sscanf(str, "%s", drop);
//   assert(strcmp(drop, "drop") == 0);
//   char s1[256], s2[256];
//   char str2[strlen(str) + 1];
//   strcpy(str2, str);
//   const char * pch = strtok(str2, " ");
//   int cnt = 0;
  
//   while (pch != NULL){
//     ++ cnt;
//     pch = strtok(NULL, " ");
//   }
//   if(cnt == 2){
//     sscanf(str, "%s %s", drop, s1);
//     while(allDatabaseRoot->next){
//       if(strcmp(s1, allDatabaseRoot->next->name) == 0){
// 	allDatabaseRoot->next = allDatabaseRoot->next->next;
// 	return 0;
//       }
//       allDatabaseRoot = allDatabaseRoot->next;
//     }
//   }
//   if(cnt == 3){
//     sscanf(str, "%s %s %s", drop, s1, s2);
//     while(allDatabaseRoot->next){
//       if(strcmp(s1, allDatabaseRoot->next->name) == 0){
// 	table * tb = allDatabaseRoot->next->rootTable;
// 	while(tb->next){
// 	  if(strcmp(s2, tb->next->name) == 0){
// 	    tb->next = tb->next->next;
// 	    return 0;
// 	  }
// 	  tb = tb->next;
// 	}
//       }
//       allDatabaseRoot = allDatabaseRoot->next;
//     }
//   }
//   return -1;
// }
int drop(const char * str)
{
  int * p = (int *)malloc(sizeof(int));
  char * s = (char *)malloc(sizeof(char) * (strlen(str) + 1));
  strcat(s, str);
  char ** ch = split(s, " ", p);
  if (strcmp(ch[0], "drop") == 0) {
    database * db = allDatabaseRoot;
    if (*p == 2) {
      if (strcmp(ch[1], allDatabaseRoot->name) == 0) {
	allDatabaseRoot = allDatabaseRoot->next;
	
	return 0;
      }
      while (db->next) {
	if (strcmp(ch[1], db->next->name) == 0) {
	  db->next = db->next->next;

	  return 0;
	}
	db = db->next;
      }
    }
    if (*p == 3) {
      if (strcmp(ch[1], allDatabaseRoot->name) == 0) {
	allDatabaseRoot = allDatabaseRoot->next;

	  return 0;
	}
      while (db->next) {
	if (strcmp(ch[1], db->next->name) == 0) {
	  table * tb = db->next->rootTable;
	  if (strcmp(ch[2], db->next->rootTable->name) == 0) {
	    db->next->rootTable = db->next->rootTable->next;

	    return 0;
	  }
	  while (tb->next) {
	    if(strcmp(ch[2], tb->next->name) == 0) {
	      tb->next = tb->next->next;
	      return 0;
	    }
	    tb = tb->next;
	  }
	}
	db = db->next;
      }
    }
  }
  return -1;
}
