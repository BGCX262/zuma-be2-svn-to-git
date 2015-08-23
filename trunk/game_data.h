#ifndef GAME_DATA_H
#define GAME_DATA_H

#include <SDL/SDL_mixer.h>
#include "scores.h"
#include "options.h"
#include "mystring.h"
#include <SDL/SDL_ttf.h>
#include "states.h"

typedef struct game_data game_data;

/**
Contient les donnee utiles entres tous les etats de jeu.
nom du joueur, configuration, score, et les musiques
*/
struct game_data
{
    string name;
    options* option;
    scores* score;
    Mix_Music *musiques[NB_ETAT];
};

void init_data(game_data* data);
#endif
