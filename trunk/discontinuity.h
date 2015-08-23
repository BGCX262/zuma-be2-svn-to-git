#ifndef DISCONTINUITY_H 
#define DISCONTINUITY_H 

/*
  Structure similaire a celle de liste_ball. Cf list_ball.h
*/
#include "node_ball.h"
typedef node_ball* type_element;

typedef struct node_discontinuity node_discontinuity;
struct node_discontinuity
{
    type_element val;
    node_discontinuity* next;
    node_discontinuity* previous;
};


typedef struct list_discontinuity list_discontinuity;
struct list_discontinuity
{
    node_discontinuity* head;
    node_discontinuity* tail;
    int size;
};

/*done*/
void construct_list_discontinuity(list_discontinuity* l);

/*done*/
void clear_list_discontinuity(list_discontinuity* l);

/*done*/
void append_list_discontinuity(list_discontinuity* l,type_element value);

/*done*/
void destruct_list_discontinuity(list_discontinuity* l);

/*done*/
type_element head_list_discontinuity(list_discontinuity l);
type_element tail_list_discontinuity(list_discontinuity l);

/*done*/
node_discontinuity* find_list_discontinuity(list_discontinuity l,type_element val);

/*donex3 */
int size_list_discontinuity(list_discontinuity l);
int empty_list_discontinuity(list_discontinuity l);
void print_list_discontinuity(list_discontinuity l);

node_discontinuity* begin_list_discontinuity(list_discontinuity l);
node_discontinuity* end_list_discontinuity(list_discontinuity l);

/*
Supprime tout les elements entre it1 et it2 (tout deux inclus)
On supose que it1 est plus proche de head que ne l'est it2 
de sorte qu'on parcourt la liste dans le sens direct (via ->next)
*/
void remove_range_list_discontinuity(list_discontinuity* list, node_discontinuity* it1,node_discontinuity* it2);
void remove_node_list_discontinuity(list_discontinuity* l,node_discontinuity* n);


int index_list_discontinuity(list_discontinuity l,node_discontinuity* n);
#endif
