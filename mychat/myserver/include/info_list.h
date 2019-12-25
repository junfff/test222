#ifndef INFO_LIST_H
#define INFO_LIST_H

#include "mychat.h"

typedef struct Info_Node 
{
   my_usr info;
   struct Info_Node *next;
}Info_Node;

int Init_List();

int Add_List(my_usr * info);

int Remove_List(my_usr *info);

Info_Node *GetHead_List();

Info_Node *GetNodeBy_List(int num);
int Deinit_List();
#endif
