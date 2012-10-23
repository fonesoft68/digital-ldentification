#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "sql.h"

int drop(const char * str)
{
  char drop[5] = "drop";
  sscanf(str, "%s", drop);
  assert(strcmp(drop, "drop") == 0);
  char s1[256], s2[256];
  char * pch = strtok(str, " ");
  int cnt = 0;
  
  while (pch != NULL){
    ++ cnt;
    pch = strtok(NULL, " ");
  }
  if(cnt == 2){
    sscanf(str, "%s %s", drop, s1);
    while(allDatabaseRoot->next){
      if(strcmp(s1, allDatabaseRoot->next->name) == 0){
	allDatabaseRoot->next = allDatabaseRoot->next->next;
	return 0;
      }
      allDatabaseRoot = allDatabaseRoot->next;
    }
  }
  if(cnt == 3){
    sscanf(str, "%s %s %s", drop, s1, s2);
    while(allDatabaseRoot->next){
      if(strcmp(s1, allDatabaseRoot->next->name) == 0){
	table * tb = allDatabaseRoot->next->rootTable;
	while(tb->next){
	  if(strcmp(s2, tb->next->name) == 0){
	    tb->next = tb->next->next;
	    return 0;
	  }
	  tb = tb->next;
	}
      }
      allDatabaseRoot = allDatabaseRoot->next;
    }
  }
  return -1;
}

    
