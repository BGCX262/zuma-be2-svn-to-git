#include "displayer.h"
#include "constante.h"
#include "button.h"
#include "level.h"

void draw_path(displayer* d,SDL_Surface* background,level *l)
{
    int i=0;
    SDL_Rect r;
    r.w=r.h=1;
    for(;i<l->size;++i)
    {
	r.x=l->points[i].x;
	r.y=l->points[i].y;
	SDL_FillRect(background,&r,SDL_MapRGB(d->screen->format,0,0,255));
    }

}

void blit_button(displayer* d, bouton* b)
{
    TTF_SetFontStyle(d->police,b->style);
    blit_text(d,get_str(b->text),b->x,b->y);
    TTF_SetFontStyle(d->police,TTF_STYLE_NORMAL);
}

void blit_text(displayer* d,const char* str,int x,int y)
{
  SDL_Rect position;

  SDL_Surface* texte=TTF_RenderText_Solid(d->police,str,d->black);
  position.x = x;
  position.y = y;
  SDL_BlitSurface(texte, NULL, d->screen, &position);  
  SDL_FreeSurface(texte);
}
void blit_background(displayer* d,SDL_Surface* background)
{
    blit_img(d,background,0,0,d->screen);
}

void blit_sprite(displayer* s,SDL_Surface* img, int x,int y)
{
    blit_img(s,img,x-img->w/2,y-img->h/2,s->screen);  
}

/*Corriger la connerie de demander screen a la fin alors qu'on a deja un displayer ....*/
void blit_img(displayer* d,SDL_Surface* img, int x,int y, SDL_Surface* screen)
{
  SDL_Rect position;
  position.x = x;
  position.y = y;
  SDL_BlitSurface(img, NULL, d->screen, &position);  
}

void flip_screen(displayer* d)
{
  SDL_Flip(d->screen);
}

displayer* create_display()
{
    displayer* d=malloc(sizeof(*d));
    d->screen= SDL_SetVideoMode(largeur, hauteur, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    d->police=TTF_OpenFont("./data/ttf/thecroach.ttf",65);
    
    d->black.r=255;
    d->black.g=0;
    d->black.b=0;

    return d;
}

void destruct_display(displayer* d)
{
    TTF_CloseFont(d->police);
    free(d);
}

