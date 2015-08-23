#ifndef EDITOR_H
#define EDITOR_H 
#include "game_state.h"
#include "displayer.h"
#include "level.h"

/*structure noeud contenant des pointeurs vers les noeuds suivants et precedents ainsi que le point*/
typedef struct node_point node_point;
struct node_point
{
    node_point* next;
    node_point* previous;
    point val;
};

/*structure liste contenant les pointeurs vers la tete et la queue*/
typedef struct list_points list_points;
struct list_points
{
    node_point* head;
    node_point* tail;
		int made;
		/*taille de la liste*/
    int size;
		/*un carre et une boule seront chargés*/
    SDL_Surface *carre;
		SDL_Surface *ball;
};

void event_editor(game_state* state);
void display_editor(game_state* state,displayer* d);
void init_editor(game_state* state,displayer* d);

void construct_list_points(list_points* l);
void clear_list_points(list_points* l);
void append_list_points(list_points* l,int x, int y);
void save_list_points(list_points* l);
void destruct_list_points(list_points* l);
int size_list_points(list_points l);
int empty_list_points(list_points l);
void print_list_points(list_points* l);
node_point* begin_list_points(list_points l);
void trace(list_points* l,point val1,point val2,int* current_pos);
void interpol(list_points* l);
node_point* find_list_points(list_points l,point value);
void insert2_list_points(list_points* l,node_point* n,point value);
void append2_list_points(list_points* l,point value);
#endif
