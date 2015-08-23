#include "sprite.h"
#include <SDL/SDL.h>
#include <stdio.h>

void go_forward(sprite* s)
{
    s->point_courant++;
}

/*On reculera de 3 points a chaque iteration*/
void go_backward(sprite* s)
{
    (s->point_courant)-=3;
}

void go_stay_still(sprite* s){}

sprite create_sprite(SDL_Surface* ball,point* point_initial)
{
    sprite s;

    s.nb=0;
    s.img=ball;
    s.point_courant=point_initial;

    s.available_movement[forward]=&go_forward;
    s.available_movement[backward]=&go_backward;
    s.available_movement[stay_still]=&go_stay_still;

    s.current_movement=forward;
    return s;
}

void update_position(sprite* s)
{
    (*s->available_movement[s->current_movement])(s);
}
/*=================================*/

void update_projectile(projectile* p)
{
    p->pos.x+=p->u;
    p->pos.y+=p->v;

}

projectile create_projectile(SDL_Surface* ball,int x0,int y0)
{
    projectile s;

    s.img=ball;

    s.u=s.v=0;

    s.pos.x=x0;
    s.pos.y=y0;

    return s;
}
