#include "constante.h"
#include "game_state.h"
#include "game.h"

game_state* create_game_state(display_fct d,event_fct e,initializer_fct i,game* game)
{
  game_state* g=malloc(sizeof(*g));
  /*
    Affectation des fonctions de gestions et des donnees partagees.
  */
  g->background=0;
  g->event_handler=e;
  g->display_handler=d;
  g->initializer=i;

  g->initialized=0;
  g->common_data=&(game->common_data);
  g->specific_data=0;

  g->continuer=1;
  g->specific_data=0;

  return g;
}

void run_state(game_state* s,displayer* d)
{
    SDL_Event event;    

    SDL_WaitEvent(&event);
    switch(event.type){
    case SDL_USEREVENT:
        if(event.user.code==EVENT_AFFICHAGE)
        {
	        s->display_handler(s,d);         
	        s->event_handler(s);
        }
        break;

    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
    case SDL_KEYDOWN:
    case SDL_QUIT:
	SDL_PushEvent(&event);
	break;

    default:
	break;
	}
}

void destruct_state(game_state* s)
{
    if(s->background)
    {
	SDL_FreeSurface(s->background);
    }
  free(s);
}

