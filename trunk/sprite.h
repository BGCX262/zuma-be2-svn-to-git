#ifndef SPRITE_H 
#define SPRITE_H 

#include <SDL/SDL.h>
#include "level.h"

typedef struct sprite sprite;


typedef void(*position_updater)(sprite*);
enum {forward,backward,stay_still, NB_TYPE_MVT};
struct sprite
{
    /*Pointeur vers l'image*/
    SDL_Surface *img; 
    
    /*le point courant dans le niveau*/
    point* point_courant;

    /*Tableau de pointeur de fonction pour les différents mouvements*/
    position_updater available_movement[NB_TYPE_MVT];
    
    /*le mouvement actuel*/
    int current_movement;

    /*La position dans le cortege*/
    int nb;
};

typedef struct projectile projectile;
struct projectile
{
    SDL_Surface *img; 
    SDL_Rect pos;
    double u,v;
};

sprite create_sprite(SDL_Surface* ball,point* point_initial);

void go_forward(sprite* s);
void go_backward(sprite* s);
void go_stay_still(sprite* s);
void update_position(sprite* s);

void update_projectile(projectile* p);
projectile create_projectile(SDL_Surface* ball,int x0,int y0);

#endif
