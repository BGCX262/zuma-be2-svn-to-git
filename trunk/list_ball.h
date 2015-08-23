#ifndef LISTE_H
#define LISTE_H


#include "node_ball.h"

typedef struct list_ball list_ball;
struct list_ball
{
    node_ball* head;
    node_ball* tail;
    int size;
};

/*construit un emplacement memoire valide*/
void construct_list_ball(list_ball* l);

/*vide la liste*/
void clear_list_ball(list_ball* l);

/*ajoute a la fin*/
void append_list_ball(list_ball* l,sprite value);

/*ajoute val apres le noeud n*/
void insert2_list_ball(list_ball* l,node_ball* n,sprite value);

/*detruit entièrement la liste. la mémoire n'est plus valide apres*/
void destruct_list_ball(list_ball* l);

/*Retourne un iterateur sur le premier element de la liste qui vaut val, NULL s'il ne trouve rien*/
node_ball* find_list_ball(list_ball l,sprite val);

/*donex3 */
int size_list_ball(list_ball l);
int empty_list_ball(list_ball l);
void print_list_ball(list_ball l);

/*Retourne le début effectif de la liste : ie l.head->next*/
node_ball* begin_list_ball(list_ball l);

/*Retourne le début effectif de la liste : ie l.head->next*/
node_ball* end_list_ball(list_ball l);

/*
Supprime tout les elements entre it1 et it2 (tout deux inclus)
On supose que it1 est plus proche de head que ne l'est it2 
de sorte qu'on parcourt la liste dans le sens direct (via ->next)
*/
void remove_range_list_ball(list_ball* list, node_ball* it1,node_ball* it2);
#endif
