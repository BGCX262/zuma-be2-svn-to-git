#ifndef BUTTON_H 
#define BUTTON_H 


/*#include "game_state.h"*/
#include "mystring.h"
#include <SDL/SDL.h>

struct game_state;
/*type de pointeur vers des fonctions prenant game_state en entree*/
typedef void (*click_handler)(struct game_state* );

/*Type Strucure permettant de gerer les boutons et leurs caractéristiques*/
typedef struct bouton bouton;
struct bouton
{
/*fonction associee au bouton*/
click_handler on_click;
/*nom du joueur*/
string text;
/*couleur à l'affichage*/
SDL_Color color;
/*etat du bouton*/
int actif;
/*position et epaisseur*/
int x,dx,y,dy;
/*style : normal ou souligne*/
int style; 
};

#endif
