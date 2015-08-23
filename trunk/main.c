#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "game.h"
#include "displayer.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    
  game* g=0;
  displayer* d=0;

  srand(time(NULL));
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);
  SDL_WM_SetCaption("SDL_Mixer", NULL);
  if(TTF_Init() == -1)
  {
    fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
    exit(EXIT_FAILURE);
  }
 
#if (1 <= SDL_MIXER_MAJOR_VERSION) && (2 <= SDL_MIXER_MINOR_VERSION) && (10 <= SDL_MIXER_PATCHLEVEL)
  {
      int mix_flags = MIX_INIT_OGG;
      int mix_initted = Mix_Init(mix_flags);
      if((mix_initted & mix_flags) != mix_flags) 
      {
	  fprintf(stderr, "Mix_Init failed : %s\n", Mix_GetError());
	  exit(EXIT_FAILURE);
      }

      Mix_VolumeMusic(70);
}
#endif
  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) 
   {
       printf("%s", Mix_GetError());
   }

  d=create_display();
  g=create_game(d);

  run_game(g,d);
  
  destruct_game(g);
  destruct_display(d);
  
  TTF_Quit();
  Mix_CloseAudio();
  SDL_Quit();



  return EXIT_SUCCESS;
}
