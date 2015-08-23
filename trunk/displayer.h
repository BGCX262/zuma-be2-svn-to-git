#ifndef DISPLAYER_H 
#define DISPLAYER_H 

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>


#include "button.h"
#include "level.h"


/*brief structure chargee de centraliser les variable necessaire a l'affichage
Propose aussi un certain nombre de fonction pour afficher texte, background, image
*/
typedef struct displayer displayer;
struct displayer
{
    SDL_Surface* screen;
    TTF_Font* police;
    SDL_Color black;
};

void blit_button(displayer* d,struct bouton* b);
void blit_text(displayer* s,const char* str,int x,int y);
void blit_background(displayer* s,SDL_Surface* background);

void blit_sprite(displayer* s,SDL_Surface* img, int x,int y);

void blit_img(displayer* s,SDL_Surface* img, int x,int y, SDL_Surface* screen);
void flip_screen(displayer* s);

displayer* create_display();
void destruct_display(displayer* d);
void draw_path(displayer* d,SDL_Surface* background,level *l);
#endif
