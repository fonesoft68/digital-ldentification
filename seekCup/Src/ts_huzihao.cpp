#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "sql.h"

database* allDatabaseRoot = (database *) calloc (1, sizeof(table));
database * nowUsedDatabase = (database *) calloc (1, sizeof(table));
int databaseCnt;
int main(int argc, char *argv[])
{
  //allDatabaseRoot = createDatabase("seedcup");
  createDatabase("seedcup");
  nowUsedDatabase = allDatabaseRoot;
  allDatabaseRoot->rootTable->next = createTable("name text , age int age1");
  // allDatabaseRoot->rootTable->next = createTable(" id int , name text , grade int");
  // allDatabaseRoot->rootTable->next->name = "person";
  // insert("insert into person values (1, 'yaoq' , 90)");
  // insert("insert into person values (2, 'huzi' , 80)");
  // insert("insert into person values (3, 'nimei', 456)");
  // showTableContext(allDatabaseRoot->rootTable->next);
  // //  initDatabaseCnt();
  // table *tmp_table = select("select name from person where id==1");
  // showTableContext(tmp_table);
  // tmp_table = select("select * from person");
  // showTableContext(tmp_table);
  
}
  // //    allDatabaseRoot->next = NULL;
  // allDatabaseRoot =  createDatabase("huzi");

  // allDatabaseRoot->rootTable->next = createTable("  a int  , b float , noe, c text   ");
  // allDatabaseRoot->rootTable->next->name = "a";
  // //allDatabaseRoot->rootTable->next = createTable("id int , name text , grade int , address text");
  //   // allDatabaseRoot->rootTable->next->name = "person";
  //   nowUsedDatabase = allDatabaseRoot;
  //   //    insert("insert into person (id , name , address) values (1 , 'yaoq' , 'qiming702')");
  //   //insert("insert into person (id, name, address) values ('yaoq', 1, 'qiming702')");
  //   // nowUsedDatabase = allDatabaseRoot;
  //       insert("insert into a values (2 , 3.5 ,'how')");
  //     insert("insert into a values ( 1 , 4.7,, 'foo')");
  //     insert("insert into a values (3, 2.4,, 'bar')");
  //   showTableContext(allDatabaseRoot->rootTable->next);
  //   //swap(allDatabaseRoot->rootTable->next, 0, 1);
  //   sort(allDatabaseRoot->rootTable->next, "b", 1);
  //   showTableContext(allDatabaseRoot->rootTable->next);
  //}
