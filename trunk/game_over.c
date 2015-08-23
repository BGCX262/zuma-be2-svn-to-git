#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "constante.h"
#include "states.h"
#include "game_state.h"
#include "displayer.h"

void event_game_over(game_state* state)
{
    SDL_Event event;

    SDL_WaitEvent(&event);
    switch(event.type)
    {
    case SDL_QUIT:
      state->continuer = 0;
      break;
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym)
	{
	case SDLK_ESCAPE: 
	  state->continuer = 0;
	  break;	  
		  
	case SDLK_RETURN:
	    state->next=menu;
	    break;

	default:
	  break;
	}
      break;
    default:
      break;

    }
}
void display_game_over(game_state* s,displayer* d)
{
    blit_background(d,s->background);
    blit_text(d,"Tu as perdu !!!!!!!",largeur/2-100,hauteur/2-50);
    blit_text(d,"Escape pour quitter",largeur/2-200,hauteur/2);
    blit_text(d,"Entree pour revenir au menu ",largeur/2-300,hauteur/2+50);
    flip_screen(d);
}

void init_game_over(game_state* state,displayer* d)
{
    state->background=IMG_Load("./data/images/background_over.jpg");

    state->initialized=1;
    state->next=game_over;
}
