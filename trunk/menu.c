#include "menu.h"
#include "constante.h"
#include "states.h"
#include "mystring.h"
#include <SDL/SDL_image.h>

/*gestion des evenements du menu, la direction vers les autres etats de jeu et quitter*/
void event_menu(game_state* state)
{  
    SDL_Event event;

    SDL_WaitEvent(&event);
  switch(event.type)
    {
    case SDL_QUIT:
      state->continuer = 0;
      break;
    case SDL_MOUSEBUTTONDOWN:
            if((event.button.x>338 && event.button.x<550) && (event.button.y>110 && event.button.y<160)){
             state->next=jeu;
						state->common_data->option->activ_sound=0;
						 Mix_PauseMusic(); }
	    else if((event.button.x>300 && event.button.x<510) && (event.button.y>235 && event.button.y<285))
             state->next=score;
	    else if((event.button.x>300 && event.button.x<510) && (event.button.y>360 && event.button.y<410))
             state->next=option;
	    else if((event.button.x>315 && event.button.x<530) && (event.button.y>485 && event.button.y<535))
             state->next=editor;
			else if((event.button.x>50 && event.button.x<180) && (event.button.y>500 && event.button.y<550))
             state->continuer=0;
    break;

    default:
      break;

    }
}
/*affichage du menu et des textes*/
void display_menu(game_state* state,displayer* d)
{		
    string s;
    const char* c="Bienvenue a toi ";
    const char* name=get_str(state->common_data->name);
    build_string(&s);
    append_string(&s,c);
    append_string(&s,name);
    blit_background(d,state->background);
    blit_text(d,get_str(s),150,5);
    blit_text(d,"GAME",338,110);
    blit_text(d,"SCORES",300,235);			
    blit_text(d,"OPTIONS",300,360);
    blit_text(d,"EDITOR",317,485);	
    blit_text(d,"QUIT",50,500);		
    destruct_string(&s);
    flip_screen(d);
}
/*initialisation du menu*/
void init_menu(game_state* state,displayer* d)
{
    state->background=IMG_Load("./data/images/maison.jpg"); 
	
    state->next=menu;
    state->initialized=1;
}

void destruct_data_menu(data_menu* tmp_data){
    free(tmp_data);
}

