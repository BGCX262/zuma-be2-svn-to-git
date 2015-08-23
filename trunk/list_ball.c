#include "list_ball.h"
#include <stdlib.h>
#include <stdio.h>

void construct_list_ball(list_ball* l)
{
  node_ball* n=malloc(sizeof(*n));
  n->next=NULL;
  n->previous=NULL;
  l->head=n;
  l->tail=n;
  n->val.nb=0;
  l->size=0;
}

void clear_list_ball(list_ball* l)
{
    node_ball* i=begin_list_ball(*l);
    node_ball* next=NULL;

    while(i!=NULL)
    {
	next=i->next;
	free(i);
	i=next;
    }
    
    l->head->next=0;
    l->tail=l->head;
    l->size=0;
}

void append_list_ball(list_ball* l,sprite value)
{
  node_ball* n=malloc(sizeof(*n));

  n->val=value;
  n->next=NULL;
  n->previous=l->tail;
  n->val.nb=l->tail->val.nb+1;

  l->tail->next=n;
  l->tail=n;
  l->size++;
}

sprite head_list_ball(list_ball l)
{
  if(l.size>0)
    return l.head->next->val;
  else
    printf("list_balle vide \n");
}

sprite tail_list_ball(list_ball l)
{
  if(l.size>0)
    {return l.tail->val;}
  else
    {  
      printf("list_balle vide \n");
    }
}

node_ball* find_list_ball(list_ball l,sprite value)
{
  node_ball* r=NULL;
  node_ball *i=l.head->next;

  while(i!=NULL)
    {
	if(i->val.point_courant==value.point_courant)
	{
	  r=i;
	}      
      i=i->next;
    }
  
  return r;
}

int size_list_ball(list_ball l)
{
  return l.size;
}

int empty_list_ball(list_ball l)
{
  return (l.size==0);
}

void print_list_ball(list_ball l)
{
  node_ball *i=l.head->next;

  while(i!=NULL)
    {
	printf("x=%d, y=%d ",i->val.point_courant->x,i->val.point_courant->y);
      i=i->next;
    }
  printf("|\n");
}

void insert_list_ball(list_ball* l,int pos,sprite value)
{
    if(pos<size_list_ball(*l))
    {
      int i=0;
      node_ball* current=l->head->next;
      node_ball* n=malloc(sizeof(*n));
      n->val=value;

      while(i<pos)
	{
	  current=current->next;
	  ++i;
	}

      n->next=current->next;
      current->next=n;

      l->size++;
    }
  else
    {
      printf("insertion dans une position depassant la taille de la list_balle");
    }
}

void insert2_list_ball(list_ball* l,node_ball* n,sprite value)
{
  node_ball *i=l->head->next;
  node_ball* it=i;
  int j=1;
  while(i!=NULL)
    {
      if(i==n && i!=l->tail)
	{
	      node_ball* new_node_ball=malloc(sizeof(*n));
	      new_node_ball->val=value;

	      n->val.nb=i->val.nb+1;

	      new_node_ball->next=i->next;
	      new_node_ball->next->previous=new_node_ball;
	      new_node_ball->previous=i;
	      i->next=new_node_ball;

	      /*DEBUG*/
	      while(it)
	      {
		  it->val.nb=j++;
		  it=it->next;
	      }
	      l->size++;
	      break;
	}
      else if(i==l->tail)
      {
	  append_list_ball(l,value);
	  break;
      }
      i=i->next;
    }

}

void print2_list_ball(list_ball* l)
{
    node_ball* it=begin_list_ball(*l);
    while(it)
    {
	printf("%d | ",it->val.nb);
	it=it->next;
    }
    printf("\n");
}

void print3_list_ball(list_ball* l)
{
    node_ball* it=end_list_ball(*l);
    while(it!=l->head)
    {
	printf("%d | ",it->val.nb);
	it=it->previous;
    }
    printf("\n");
}

void destruct_list_ball(list_ball* l)
{
  clear_list_ball(l);
  free(l->head);
}

node_ball* begin_list_ball(list_ball l)
{
    return l.head->next;
}

node_ball* end_list_ball(list_ball l)
{
    return l.tail;
}

void remove_node_list_ball(list_ball* l,node_ball* n)
{
    if(size_list_ball(*l)>1)
    {
	if(n==end_list_ball(*l))
	{
	    l->tail=n->previous;
	    l->tail->next=0;
	}
	else if(n==begin_list_ball(*l))
	{
	    l->head->next=n->next;
	    l->head->next->previous=l->head;
	}
	else
	{
	    n->previous->next=n->next;
	    n->next->previous=n->previous;
	}
	free(n);	
	l->size--;
    }
    else
    {
	clear_list_ball(l);
    }
}

void remove_range_list_ball(list_ball* l, node_ball* it1,node_ball* it2)
{
    node_ball* next=0;
    node_ball* it=0;
    node_ball* copy=it2->next;
    int j=1;

    if(it1==begin_list_ball(*l) && it2==end_list_ball(*l))
    {
	clear_list_ball(l);
    }
    else
    {
	while(it1!=copy)
	{
	    next=it1->next;
	    remove_node_list_ball(l,it1);
            it1=NULL;	 
	    it1=next;
	}
	it=begin_list_ball(*l);
	while(it)
	{
	    it->val.nb=j;
	    it=it->next;
	    j++;
	}
    }
}
