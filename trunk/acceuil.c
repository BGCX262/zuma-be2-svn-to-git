#include "acceuil.h"
#include "mystring.h"
#include <SDL/SDL_mixer.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "constante.h"
#include "states.h"
#include "game_data.h"

#define APPENDER(c) case SDLK_##c: \
  append_string(&(state->common_data->name),#c);		\
break
void event_acceuil(game_state* state)
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
	  
	  APPENDER(a);
	  APPENDER(b);
	  APPENDER(c);
	  APPENDER(d);
	  APPENDER(e);
	  APPENDER(f);
	  APPENDER(g);
	  APPENDER(h);
	  APPENDER(i);
	  APPENDER(j);
	  APPENDER(k);
	  APPENDER(l);
	  APPENDER(m);
	  APPENDER(n);
	  APPENDER(o);
	  APPENDER(p);
	  APPENDER(q);
	  APPENDER(r);
	  APPENDER(s);
	  APPENDER(t);
	  APPENDER(u);
	  APPENDER(v);
	  APPENDER(w);
	  APPENDER(x);
	  APPENDER(y);
	  APPENDER(z);
	  
	case SDLK_BACKSPACE: 
	  pop_string(&(state->common_data->name)); 
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
#undef APPENDER

void display_acceuil(game_state* s,displayer* d)
{
    blit_background(d,s->background);
    blit_text(d,"Quel est ton nom ? ",370,300);
    blit_text(d,get_str(s->common_data->name),500,400);
    flip_screen(d);
}

void init_acceuil(game_state* state,displayer* d)
{		
    state->background=IMG_Load("./data/images/background_accueil.jpg");
		
    if(state->common_data->option->sound==1){
	Mix_PlayMusic(state->common_data->musiques[0], -1);
    }

    state->initialized=1;
    state->next=accueil;
}
