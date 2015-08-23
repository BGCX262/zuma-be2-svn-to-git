#include "constante.h"
#include "states.h"
#include "jeu.h"
#include "mystring.h"
#include "update_world.h"
#include <SDL/SDL_image.h>
#include <math.h>

Uint32 mytimer(Uint32 interval,void* param)
{
  update_world(param);

  return interval;
}
/*==========================*/
/*Mettre en pause le jeu*/
void pause(game_state*  g){
    data_jeu* data=g->specific_data;
    data->pause=1-data->pause;

    if(data->pause==1)
	SDL_RemoveTimer(data->id_timer_update_world);
    else
	data->id_timer_update_world=SDL_AddTimer(period_update_world,&mytimer,g);
}
void event_jeu(game_state* state)
{  
    int x,y;double t=0;
    data_jeu* data =state->specific_data;
    SDL_Event event;

    SDL_LockMutex(data->mutex);

    SDL_PollEvent(&event);
    switch(event.type)
    {

    case SDL_QUIT:
      state->continuer = 0;
      break;

    case SDL_KEYDOWN:
      switch (event.key.keysym.sym)
	{
	case SDLK_ESCAPE: 
	  if(!(data->pause))
	    {  pause(state);}
	  reset_data_jeu(data);
	  data->pause=1;
	  state->next=menu;
	  break;
	case SDLK_SPACE:
	    pause(state);
	    break;
	default:
	  break;
	}
      break;

    case SDL_MOUSEBUTTONDOWN:
	if(data->throw_projectile)
	{
	    /*des maths*/
	    data->throw_projectile=0;
	    x=(event.button.x-data->cannonball.pos.x);
	    y=(event.button.y-data->cannonball.pos.y);
	
	    t=(x==0) ? (3.14/2) : atan((double)y/x);
	    if(x<0) {t+=3.14;}
            if(x==0 && y>0) {t=-3.14/2;}

	    data->cannonball.u=8*cos(t);
	    data->cannonball.v=8*sin(t);
	}
	break;

    default:
      break;

    }
    SDL_UnlockMutex(((data_jeu*)(state->specific_data))->mutex);
}

void display_jeu(game_state* state,displayer* d)
{   
    data_jeu* data=state->specific_data;
    node_ball* it=0;
    node_ball* end=0;
    int i=0;
    char* s=0;

    SDL_mutex* mutex = data->mutex;
    SDL_LockMutex(mutex);

    data=state->specific_data;
    it=begin_list_ball(data->file_balls);
    end=end_list_ball(data->file_balls);

    if(data->new_level)
    {
	draw_path(d,state->background,data->current_level);
	data->new_level=0;
    }

    blit_background(d,state->background);

    s =stringify_int(SDL_GetTicks()/1000);
    blit_text(d,s,700,10);
    free(s);

    s =stringify_int(size_list_ball(data->file_balls));
    blit_text(d,s,700,60);
    free(s);

    s =stringify_int(data->score);
    blit_text(d,s,700,120);
    free(s);
    
    blit_text(d,"score",500,120);

    if(data->pause)
    {
	blit_text(d,"PAUSE (espace pour jouer)",largeur/2-300,hauteur-100);
    }
    blit_sprite(d,data->cannonball.img,data->cannonball.pos.x,data->cannonball.pos.y);

    while(it!=NULL)
    {

	if(it->val.img==0)
	{
	  printf("size list ball %d",size_list_ball(data->file_balls));
	  printf("%d-eme boule a une image nulle \n",i);
	}
	else
	{
	    blit_sprite(d,it->val.img,it->val.point_courant->x,it->val.point_courant->y);
	}

	it=it->next;
	i++;
    }

    flip_screen(d);

    SDL_UnlockMutex(data->mutex);
}

/*verifie que le projectile est dans le fenetre de jeu sinon le remet a niveau*/
void check_projectile(data_jeu* data)
{
    projectile* p=&(data->cannonball);
    if(p->pos.x>largeur || p->pos.x<0 || p->pos.y<0 || p->pos.y>hauteur)
    {
	reset_projectile(data);
    }
}

/*algo cf rapport*/
void update_world(game_state* g)
{
    data_jeu* data=g->specific_data;
    point lanceur;
    point* point_last_ball=0;
    point* point_first_ball=0;
    point* fin_niveau=0;
    SDL_mutex* mutex = data->mutex;
    SDL_LockMutex(mutex);
    

    lanceur=data->current_level->points[0];
    fin_niveau=data->current_level->points+data->current_level->size-1;

    if(size_list_ball(data->file_balls)>0)
    {
	point_last_ball=end_list_ball(data->file_balls)->val.point_courant;
	point_first_ball=begin_list_ball(data->file_balls)->val.point_courant;
    }

    if( ( data->adding_ball &&data->current_level->nb_ball_restante>0 &&(size_list_ball(data->file_balls) ==0 || (distance_point(&lanceur,point_last_ball)>32*32*COEFF_MAGIQUE)) ) 
	)
    {
	add_ball(data);
	data->current_level->nb_ball_restante--;
    }

    if(size_list_ball(data->file_balls)==0){printf("my truc CC\n");}
    if(data->current_level->nb_ball_restante == 0 && size_list_ball(data->file_balls)==0)
    {
	printf("going update data \n");
	update_data_jeu(g);
    }

    update_list_ball(&(data->file_balls));
    update_projectile(&(data->cannonball));
    
    merge_discontinuity(data);
    check_colision(data);   

    check_projectile(data);

    if(point_first_ball>=fin_niveau)
    {
        SDL_Surface* back_background=g->background;
        data_jeu* data2=g->specific_data;
	data_jeu* data1=create_data_jeu();
	data1->pause=1;
	
	g->common_data->score->value=data->score;
	append_string(&(g->common_data->score->name),get_str(g->common_data->name));
	pause(g);
	
    if(data->level_number>1)
	{save_scores(g);}
	
       g->specific_data=data1;

        g->background=IMG_Load("./data/images/background.jpg");    
        SDL_FreeSurface(back_background);
        destruct_data_jeu(data2); /*Peut causer des bug (vive le threading !)*/
	g->next = game_over;
    }
    SDL_UnlockMutex(mutex);
}

void init_jeu(game_state* state,displayer* d)
{
    data_jeu* tmp_data=create_data_jeu();

    state->background=IMG_Load("./data/images/background.jpg");    
    state->specific_data=tmp_data;

    state->initialized=1;
    tmp_data->id_timer_update_world=SDL_AddTimer(period_update_world,&mytimer,state);

    state->next=jeu;
}

/*ajoute une balle au cortege*/
void add_ball(data_jeu* tmp_data)
{

   int image_sprite=rand()%(tmp_data->current_level->nb_color);    
       tmp_data->nb_type_playing[image_sprite]++;
  
	append_list_ball(&(tmp_data->file_balls),
		     create_sprite(tmp_data->img_ball[image_sprite],tmp_data->current_level->points));

}

/*met a jour la position du cortege*/
void update_list_ball(list_ball* l)
{
    node_ball* head=begin_list_ball(*l);
    while(head)
    {
	update_position(&(head->val));
	head=head->next;
    }
}
