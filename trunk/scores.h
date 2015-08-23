#ifndef SCORES_H
#define SCORES_H 

#include "displayer.h"
#include "options.h"
#include <stdio.h>
#include "displayer.h"
#include "mystring.h"

#define MAX_SIZE 10 
#define MAX_SCORES 100	

struct game_state ; 
/*structure score contenant les informations et expliquee dans le rapport*/
typedef struct scores scores;
struct scores
{
	string name;
	int value;
	int difficulty; 
	int page;
	bouton* button[5];
	SDL_Surface* fleche[4];
};

void print_scores(struct game_state* state, FILE* fsco);
void save_scores(struct game_state* state);
void destruct_scores(scores* sc);
scores* create_scores();
void event_scores(struct game_state* state);
void display_scores(struct game_state* state,displayer* d);
void init_scores(struct game_state* state,displayer* d);
int indice_max(int* tab,int inf,int sup);
void permuter(int *a,int *b);
void tri(int tab[MAX_SCORES],int n,char** str_tab);
void permuter_str(char *a,char *b);
void on_click_gauche(struct game_state* state);
void on_click_droit(struct game_state* state);
void on_click_haut(struct game_state* state);
void on_click_bas(struct game_state* state);
#endif
