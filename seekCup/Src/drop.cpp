#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "sql.h"

int drop(const char * str)
{
  int * p = (int *)calloc(1, sizeof(int));
  char * s = (char *)calloc(1, sizeof(char) * (strlen(str) + 1));
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
      while (db->next) {
	if (strcmp(ch[1], db->name) == 0) {
	  table * tb = db->rootTable;
	  if (strcmp(ch[2], db->rootTable->name) == 0) {
	    db->rootTable = db->rootTable->next;

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
