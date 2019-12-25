#include "mychat.h";
#include "info_list.h"
Info_Node *head;

int Init_List()
{
	 if(NULL == head)
	 {
       head = (Info_Node *)malloc(sizeof(Info_Node));
       //指针变量p为静态分配,malloc开辟的空间为动态分配  
       memset(head,0,sizeof(Info_Node));
  //  free(p); //free
      return 0;
	 }
   return -1;
}

int Deinit_List()
{
   Info_Node *cur = head;
   Info_Node *tmp = NULL;
	 while(cur != NULL)
	 {
	    tmp = cur->next;
 	    free(cur);
 	    cur = tmp;
	 }
	 
   return 0;
}

int Add_List(my_usr *info)
{  
   Info_Node *item = (Info_Node *)malloc(sizeof(Info_Node));
   if(NULL == item)
   {
   	 return -1;
   }
   memset(item,0,sizeof(Info_Node));
	  
	 item->info.num = info->num;
	 item->info.pid = info->pid;
	 strcpy(item->info.name,info->name);

   Info_Node *cur = head;
	 while(cur != NULL)
	 {
      if(cur->next == NULL)
      {
        cur->next = item;
        cur = item->next;
      }
      else
      {
        cur = cur->next;
      }
	 }
   return 0;
}
int Remove_List(my_usr *info)
{
  Info_Node *elem = head->next;//用于索引的指针  
   Info_Node *temp = NULL;//用于记录删除结点的上一个结点  
  
   if (elem->info.pid == info->pid)//删除的正好是第一个结点  
   {  
        head->next = elem->next;  
        free(elem);  
   }  
    else  
    {  
        while (elem != NULL)//没有到尽头  
        {  
            temp = elem;//记录保存好  
            elem = elem->next;//往后索引  
  
            if (elem == NULL)//遍历完也没找到  
            {  
                printf("没有找到要删除的结点\n");  
                return -1;
            }  
            else if(elem->info.pid == info->pid)//找到  
            {  
                temp->next = elem->next;
                //删除结点的前一个结点指向删除结点的后一个结点  
                free(elem);//释放删除结点的内存  
                return 0;  
            }  
            else  
            {  
            printf("没有找到要删除的结点\n");  
            return -2;
            }  
          
        }  
    }   
}

Info_Node *GetHead_List()
{
   return head;
}

Info_Node *GetNodeBy_List(int num)
{
   Info_Node *cur = head;
   Info_Node *tmp = NULL;
	 while(cur != NULL)
	 {
	    tmp = cur->next;
 	    if(cur->info.num == num)
 	    {
 	      return cur;
 	    }
 	    cur = tmp;
	 }
	 return NULL;
}


