#include "game_data.h"
#include "menu.h"
#include "options.h"

#include "scores.h"
#include <SDL/SDL_mixer.h>
void init_data(game_data* data)
{
  build_string(&(data->name));
  data->option=create_options();
  data->score=create_scores();
  data->musiques[0]=Mix_LoadMUS("./data/sound/exorciste.mp3");
}

void destroy_data(game_data* data)
{
  destruct_string(&(data->name));
  destroy_options(data->option);
  destruct_scores(data->score);
  Mix_FreeMusic(data->musiques[0]);
}
