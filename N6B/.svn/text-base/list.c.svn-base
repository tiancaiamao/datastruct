#include "list.h"
int createlist(list* head)
{
    (*head)=makenode(0,0);
    return (*head)?0:1;
}
void destroylist(list* head)
{
	list p=(*head)->next;
	while(p)
	{
		free(*head);
		(*head)=p;
		p=p->next;
	}
	free(*head);
}
pnode find(pnode p,Elemtype data)
{
    while(p&&p->data!=data)
        p=p->next;
    return p;
}
