#include "data_jeu.h"
#include "mystring.h"
#include "constante.h"
#include "discontinuity.h"
#include "game_state.h"
#include "update_world.h"
#include "jeu.h"

#include <SDL/SDL_image.h>
#include "options.h"

#define NB_BALL_DEBUT_NIVEAU 30
#define COEFF_DIFF_NIVEAU 20

data_jeu* create_data_jeu()
{
    data_jeu* tmp_data=malloc(sizeof(*tmp_data));
    
    int i=0;

    options opt;
    load_options(&opt);
    tmp_data->mutex=SDL_CreateMutex();
    tmp_data->level_number=1;
    tmp_data->current_level=load_level("1");

    /*Pour les parametres, cf rapport*/
    tmp_data->current_level->nb_ball_restante=NB_BALL_DEBUT_NIVEAU+(opt.diff+1)*COEFF_DIFF_NIVEAU;
    tmp_data->current_level->nb_ball_originale=tmp_data->current_level->nb_ball_restante;
    tmp_data->current_level->nb_color=2+(opt.diff+1)*2;
    
    memset(tmp_data->nb_type_playing,0,NB_TYPE_BALL*sizeof(int));
    
    tmp_data->adding_ball=1;
    tmp_data->pause=0;
    tmp_data->throw_projectile=1;
    tmp_data->score=0;
    tmp_data->new_level=1;

    construct_list_ball(&(tmp_data->file_balls));
    construct_list_discontinuity(&(tmp_data->discontinuity));

    /*On charge les images  des balles*/
    {
	int j=0;
	string str;
	char* tmp_str=0;

	char* str_graphic_set=stringify_int(opt.graphic_chosen);

	build_string(&str);
	append_string(&str,"./data/images/");
	append_string(&str,str_graphic_set);
	append_string(&str,"/");
	free(str_graphic_set);

	for(;i<NB_TYPE_BALL;++i)
	{
	    tmp_str=stringify_int(i);
	    append_string(&str,tmp_str);
	    append_string(&str,".png");

	    tmp_data->img_ball[i]=IMG_Load(get_str(str));

	    for(j=0;j<5;++j)
	    {pop_string(&str);}

	    free(tmp_str);  
	}

    }
    /*place le projectile*/
    tmp_data->cannonball=create_projectile(tmp_data->img_ball[1],largeur/2,hauteur/2);
    return tmp_data;
}

/*La meme chose qu'au dessus sauf que c'est pas la meme chose 
On update au lieu de tout mettre à O
*/
void update_data_jeu(game_state* s)
{
    /*Le coup de sauvegarde de data et background est pour eviter les probleme de synchro et de threading lie au timer
    Ne semble pas marcher super bien
    */
    data_jeu* tmp_data=s->specific_data;
    char* str=0;

    SDL_Surface* back_background=s->background;
    level* back_level=tmp_data->current_level;
    tmp_data->level_number++;


    s->background=IMG_Load("./data/images/background.jpg");    
    SDL_FreeSurface(back_background);

    /*
    On suppose qu'on a assez de fichier pour eviter que le chargement echoue
    Pour bien il faudrait lister les niveaux mais ca impose soit une methode crade 
    (tester tous les i jusqu'a ce que l'ouverture plante OU utiliser opendir
    */
    str=stringify_int(tmp_data->level_number);
    tmp_data->current_level=load_level(str);
    destroy_level(back_level);
    free(str);

    tmp_data->current_level->nb_ball_restante=tmp_data->current_level->nb_ball_originale;
    memset(tmp_data->nb_type_playing,0,NB_TYPE_BALL*sizeof(int));

    tmp_data->adding_ball=1;
    tmp_data->pause=0;
    tmp_data->throw_projectile=1;
    tmp_data->new_level=1;

    tmp_data->current_level->nb_color=2+(s->common_data->option->diff+1)*2;

    clear_list_ball(&(tmp_data->file_balls));
    clear_list_discontinuity(&(tmp_data->discontinuity));

    reset_projectile(tmp_data);
}

void destruct_data_jeu(data_jeu* d)
{
  int i=0;
  for(;i<NB_TYPE_BALL;++i)
    {
      SDL_FreeSurface(d->img_ball[i]);
    }
  destruct_list_ball(&(d->file_balls));
  destruct_list_discontinuity(&(d->discontinuity));
  free(d);
}

void reset_data_jeu(data_jeu* d)
{
  int i=0;
  options opt;
  for(;i<NB_TYPE_BALL;++i)
    {
      SDL_FreeSurface(d->img_ball[i]);
    }
    
     
    load_options(&opt);
    destroy_level(d->current_level);
    d->level_number=1;
    d->current_level=load_level("1");

    /*Pour les parametres, cf rapport*/
    d->current_level->nb_ball_restante=NB_BALL_DEBUT_NIVEAU+(opt.diff+1)*COEFF_DIFF_NIVEAU;
    d->current_level->nb_ball_originale=d->current_level->nb_ball_restante;
    d->current_level->nb_color=2+(opt.diff+1)*2;
    
    memset(d->nb_type_playing,0,NB_TYPE_BALL*sizeof(int));
    
    d->adding_ball=1;
    d->pause=1;
    d->throw_projectile=1;
    d->score=0;
    d->new_level=1;

    /*On charge les images  des balles*/
    {
	int j=0;
	string str;
	char* tmp_str=0;

	char* str_graphic_set=stringify_int(opt.graphic_chosen);

	build_string(&str);
	append_string(&str,"./data/images/");
	append_string(&str,str_graphic_set);
	append_string(&str,"/");
	free(str_graphic_set);

	for(i=0;i<NB_TYPE_BALL;++i)
	{
	    tmp_str=stringify_int(i);
	    append_string(&str,tmp_str);
	    append_string(&str,".png");

	   d->img_ball[i]=IMG_Load(get_str(str));

	    for(j=0;j<5;++j)
	    {pop_string(&str);}

	    free(tmp_str);  
	}

    }
  /*place le projectile*/
  d->cannonball=create_projectile(d->img_ball[1],largeur/2,hauteur/2);
    
  clear_list_ball(&(d->file_balls));
  clear_list_discontinuity(&(d->discontinuity));
}
