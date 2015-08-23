#ifndef OPTIONS_H
#define OPTIONS_H 

/*#include "game_state.h"*/

#include <stdio.h>
#include "displayer.h"
#include "mystring.h"
#include "button.h"

/*struct game_state ; */

/*structure contenant les boutons et les options activees*/
typedef struct options options;
struct options
{
    bouton* buttons[9];
    int sound;
    int activ_sound;
    int graphic_chosen;
    enum difficulty{easy,medium,hard} diff;

};
void on_click_sound_on(struct game_state* state);
void on_click_sound_off(struct game_state* state);
void on_click_theme_one(struct game_state* state);
void on_click_theme_two(struct game_state* state);
void on_click_theme_three(struct game_state* state);
void on_click_diff_easy(struct game_state* state);
void on_click_diff_medium(struct game_state* state);
void on_click_diff_hard(struct game_state* state);
void destruct_button(bouton* button);
bouton* create_button(click_handler on_click,char* str,int r,int g,int b, int actif, int x, int dx, int y, int dy, int style);
int has_in(bouton* button,int x,int y);
void on_click_menu(struct game_state* state);
void destroy_options(options* op);
options* create_options();
void save_options(options op);
void print_opt(int opt_pr, FILE* fopt,int* currentchar);
void load_options(options* opt);
void get_opt(int* opt_get, FILE* fopt,int* currentchar);
void event_option(struct game_state* state);
void display_option(struct game_state* state,displayer* d);
void init_option(struct game_state* state,displayer* d);

#endif

