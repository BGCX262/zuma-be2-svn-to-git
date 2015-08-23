#include "discontinuity.h"
#include <stdlib.h>
#include <stdio.h>

void construct_list_discontinuity(list_discontinuity* l)
{
  node_discontinuity* n=malloc(sizeof(*n));
  n->next=NULL;
  n->previous=NULL;
  l->head=n;
  l->tail=n;

  l->size=0;
}

void clear_list_discontinuity(list_discontinuity* l)
{
    node_discontinuity* i=begin_list_discontinuity(*l);
    node_discontinuity* next=NULL;

    while(i!=NULL)
    {
	next=i->next;
	free(i);
	i=next;
    }
    l->size=0;
    l->head->next=0;
    l->tail=l->head;
}

void append_list_discontinuity(list_discontinuity* l,type_element value)
{
    node_discontinuity* n=malloc(sizeof(*n));
    n->val=value;
    n->next=NULL;
    n->previous=l->tail;

    l->tail->next=n;
    l->tail=n;
  l->size++;
}

type_element head_list_discontinuity(list_discontinuity l)
{
  if(l.size>0)
    return l.head->next->val;
  else
    printf("list_discontinuitye vide \n");
}
type_element tail_list_discontinuity(list_discontinuity l)
{
  if(l.size>0)
    {return l.tail->val;}
  else
    {  
      printf("list_discontinuitye vide \n");
    }
}

node_discontinuity* find_list_discontinuity(list_discontinuity l,type_element value)
{
  node_discontinuity* r=NULL;
  node_discontinuity *i=l.head->next;

  while(i!=NULL)
    {
	if(i->val==value)
	{
	  r=i;
	  break;
	}      
      i=i->next;
    }
  
  return r;
}

int size_list_discontinuity(list_discontinuity l)
{
  return l.size;
}

int empty_list_discontinuity(list_discontinuity l)
{
  return (l.size==0);
}

void print_list_discontinuity(list_discontinuity l)
{
  node_discontinuity *i=l.head->next;

  while(i!=NULL)
    {
	/*on force le cast en void car
	  %p demande un void* 
	  gcc emet un warning comme quoi type_element n'est pas un un pointeur*/
	printf("adresse=%p ",(void*)(i->val));
      i=i->next;
    }
  printf("|\n");
}

void destruct_list_discontinuity(list_discontinuity* l)
{
  clear_list_discontinuity(l);
  free(l->head);
}

node_discontinuity* begin_list_discontinuity(list_discontinuity l)
{
    return l.head->next;
}
node_discontinuity* end_list_discontinuity(list_discontinuity l)
{
    return l.tail;
}

void remove_node_list_discontinuity(list_discontinuity* l,node_discontinuity* n)
{
    if(size_list_discontinuity(*l)>1)
    {
	if(n==end_list_discontinuity(*l))
	{
	    l->tail=n->previous;
	    l->tail->next=0;
	    free(n);
	}
	else if(n==begin_list_discontinuity(*l))
	{
	    l->head->next=n->next;
	    l->head->next->previous=l->head;
	    free(n);
	}
	else
	{
	    n->previous->next=n->next;
	    n->next->previous=n->previous;
	    free(n);
	}
	l->size--;
    }
    else
    {
	clear_list_discontinuity(l);
    }
}

void remove_range_list_discontinuity(list_discontinuity* l, node_discontinuity* it1,node_discontinuity* it2)
{
    node_discontinuity* next=0;
    node_discontinuity* copy=it2->next;
    if(it1==begin_list_discontinuity(*l) && it2==end_list_discontinuity(*l))
    {
	clear_list_discontinuity(l);
    }
    else
    {
	while(it1!=copy)
	{
	    next=it1->next;
	    remove_node_list_discontinuity(l,it1);
	    it1=next;
	}    
    }
}

void print2_list_discontinuity(list_discontinuity* l)
{
    node_discontinuity* it=begin_list_discontinuity(*l);
    printf("discontinuity : ");
    while(it)
    {
	printf("%d | ",it->val->val.nb);
	it=it->next;
    }
    printf("\n");
}

int index_list_discontinuity(list_discontinuity l,node_discontinuity* n)
{
    int i=0;
    node_discontinuity* it=begin_list_discontinuity(l);

    while(it && it!=n)
    {
	it=it->next;
	++i;
    }
    return i;
}
