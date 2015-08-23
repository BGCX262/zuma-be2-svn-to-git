#ifndef DATA_JEU_H 
#define DATA_JEU_H 

#include <SDL/SDL.h>
#include "list_ball.h"
#include "level.h"
#include "discontinuity.h"
struct game_state;

enum type_ball
{
    ball0,ball1,ball2,ball3,ball4,ball5,ball6,ball7,ball8,NB_TYPE_BALL
};

typedef struct data_jeu data_jeu;
struct data_jeu
{
    /**
       Represente les images des differentes balles
     */
    SDL_Surface* img_ball[NB_TYPE_BALL];

    int nb_type_playing[NB_TYPE_BALL];
    /**
       Le niveau en train d'etre jouee
     */
    level* current_level;

    /**Le cortege de boule*/
    list_ball file_balls;

    /**Le numero du niveau*/
    int level_number;

    /**Le projectile*/
    projectile  cannonball;
    
    /**L'ID du timer pour les pauses*/
    SDL_TimerID id_timer_update_world;
    
    list_discontinuity discontinuity;

    /**Est-on en pause */
    int pause;

    /**Doit t'on ajouter une balle ou non (sert quand l'arriere du cortege bloque le debut du chemin)*/
    int adding_ball;

    /**Doit t'on ajouter une balle ou non (sert quand l'arriere du cortege bloque le debut du chemin)*/
    int throw_projectile;

   /*score cumule*/
    int score;

   /*permet de savoir si c'est un nouveau niveau et donc si on besoin de tracer le chemin des boules*/
    int new_level;

    SDL_mutex* mutex;
};

data_jeu* create_data_jeu();
void destruct_data_jeu(data_jeu* data);
void update_data_jeu(struct game_state* s);
void destruct_data_jeu(data_jeu* tmp_data);
void reset_data_jeu(data_jeu* d);
#endif



