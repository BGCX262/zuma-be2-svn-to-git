#ifndef GAME_OVER_H
#define GAME_OVER_H

#include "game_state.h"

void event_game_over(game_state* state);
void display_game_over(game_state* state,displayer* d);
void init_game_over(game_state* state,displayer* d);

#endif
