#ifndef JEU_H 
#define JEU_H 

#include "game_state.h"
#include "list_ball.h"
#include "level.h"

#include "data_jeu.h"

void event_jeu(game_state* state);
void display_jeu(game_state* state,displayer* d);
void init_jeu(game_state* state,displayer* d);
void pause(game_state*  g);
#endif
