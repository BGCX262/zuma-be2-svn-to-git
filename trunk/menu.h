#ifndef MENU_H 
#define MENU_H 

#include "game_state.h"

/*structure contenat d'eventuelles images pour le menu*/
typedef struct data_menu data_menu;
struct data_menu
{
    SDL_Surface* img_menu[4];
};

void event_menu(game_state* state);
void display_menu(game_state* state,displayer* d);
void init_menu(game_state* state,displayer* d);
void destruct_data_menu(data_menu* tmp_data);

#endif
