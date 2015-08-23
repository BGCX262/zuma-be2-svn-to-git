#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <SDL/SDL.h>
#include "game_data.h"
#include "displayer.h"
/*Cf rapport*/
typedef struct game_state game_state;

typedef void (*display_fct)(game_state*,displayer*);
typedef void (*event_fct)(game_state*);
typedef void (*initializer_fct)(game_state*,displayer*);

struct game;
struct game_state
{

    game_data* common_data;
    void* specific_data;

    event_fct event_handler;
    display_fct display_handler;
    initializer_fct initializer;

    SDL_Surface* background;

    int next;

    int continuer;
    
    int initialized;
};

game_state* create_game_state(display_fct d,event_fct e,initializer_fct i,struct game* g);
void destruct_state(game_state* s);
void run_state(game_state* s,displayer* d);
#endif
