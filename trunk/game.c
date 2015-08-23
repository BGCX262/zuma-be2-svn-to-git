#include "constante.h"
#include "game.h"
#include "options.h"
#include "acceuil.h"
#include "menu.h"
#include "jeu.h"
#include "game_over.h"
#include "editor.h"
#include "update_world.h"
#include <SDL/SDL.h>
#include "scores.h"

/*Timer d'affichage*/
Uint32 timer_affichage_event(Uint32 interval, void *param)
{
    static SDL_Event event;
    event.user.type=SDL_USEREVENT;
    event.user.code=EVENT_AFFICHAGE;
    event.user.data1=0;
    
    SDL_PushEvent(&event);
    return interval;
}


game* create_game(displayer* d)
{
  game* g=malloc(sizeof(*g));	

  init_data(&(g->common_data));

  /*
  Construction en memoire des differents etats de jeu. ces derniers ne sont pas encore valide
  */
  g->states[accueil]=create_game_state(&display_acceuil,&event_acceuil,&init_acceuil,g);
  init_acceuil(g->states[accueil],d);
  
  g->states[menu]=create_game_state(&display_menu,&event_menu,&init_menu,g);
  g->states[jeu]=create_game_state(&display_jeu,&event_jeu,&init_jeu,g);
  g->states[option]=create_game_state(&display_option,&event_option,&init_option,g);
  g->states[score]=create_game_state(&display_scores,&event_scores,&init_scores,g);
  g->states[game_over]=create_game_state(&display_game_over,&event_game_over,&init_game_over,g);
  g->states[editor]=create_game_state(&display_editor,&event_editor,&init_editor,g);

  /*On demarre par l'etat d'accueil*/
  g->current_state=g->states[accueil];
  SDL_AddTimer(period,&timer_affichage_event,NULL);
  
  return g;
}

/*Boucle principale du jeu*/
void run_game(game* g,displayer* d)
{
    int next=0;
    int actual=0;

  while(g->current_state->continuer)
  {
      actual=g->current_state->next;
      
      /*Traite les evenements et l'affichage*/
      run_state(g->current_state,d);
	    
      
    
      /*Permet de reboucler si on revient sur l'etat depuis un menu*/
      next=g->current_state->next;
      g->states[actual]->next=actual;
	
    /*permet de passer a l'etat suivant quand next 
    est modifie dans la fonction de traitement de evenements*/
      g->current_state=g->states[next];
      if(!(g->current_state->initialized))
      {
	  g->current_state->initializer(g->current_state,d);
      }
    }
}

void  destruct_game(game* g)
{
  destruct_state(g->states[accueil]);
  destruct_state(g->states[option]);

  if(g->states[menu]->specific_data)
  {
      destruct_data_menu(g->states[menu]->specific_data);
  }

  if(g->states[jeu]->specific_data)
  {
      destruct_data_jeu(g->states[jeu]->specific_data);
  }

  destruct_state(g->states[menu]);
  destruct_state(g->states[score]);
  destruct_state(g->states[game_over]);

  free(g);
}
