#ifndef GAME_H
#define GAME_H

#include "game_state.h"
#include "game_data.h"
#include "displayer.h"

#include "states.h"


typedef struct game game;
struct game
{
  /** Donne du jeu*/
  game_data common_data;
    
  /*Les etats de jeu et l'etat courant*/
  game_state* states[NB_ETAT];
  game_state* current_state;
};

game* create_game(displayer* d);
void run_game(game* g,displayer* d);
void  destruct_game(game* g);
#endif
