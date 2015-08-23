#include "options.h"
#include "constante.h"
#include "states.h"
#include "displayer.h"
#include "game_state.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

/*creation d'une structure option pointee*/
options* create_options(){
	options* opt=malloc(sizeof(*opt));
	load_options(opt);

	return opt;
}
/* destruction*/
void destroy_options(options* op){
	int i;
	for(i=0;i<=9;i++){
		destruct_button(op->buttons[i]);
	}
	free(op);
}
/*sauvegarde des options dans le fichier*/
void save_options(options op){

	FILE* fopt = NULL;
	int currentchar;

	fopt = fopen("./data/options/options.txt","r+");
 	currentchar=fgetc(fopt);
	print_opt(op.sound,fopt,&currentchar);
	currentchar=fgetc(fopt);
	print_opt(op.graphic_chosen,fopt,&currentchar);
	currentchar=fgetc(fopt);
	print_opt(op.diff,fopt,&currentchar);

	fclose(fopt);
}

void print_opt(int opt_pr, FILE* fopt,int* currentchar){
		
		while (*currentchar !='='){
			*currentchar=fgetc(fopt);
		}
		fprintf(fopt,"%d",opt_pr);
		fputc('\n', fopt);
}
/*chargement des options*/
void load_options(options* opt){
	FILE* fopt = NULL;
	int currentchar;
	int diff;
	fopt = fopen("./data/options/options.txt","r+");

	get_opt(&(opt->sound),fopt,&currentchar);
	currentchar=fgetc(fopt);
	get_opt(&(opt->graphic_chosen),fopt,&currentchar);
	currentchar=fgetc(fopt);
	while (currentchar !='='){
			currentchar=fgetc(fopt);
		}
	fscanf(fopt,"%d",&diff);
	opt->diff=diff;	

	fclose(fopt);
}

void get_opt(int* opt_get, FILE* fopt,int* currentchar){
		
		while (*currentchar !='='){
			*currentchar=fgetc(fopt);
		}
	fscanf(fopt,"%d",opt_get);
}
/*gestion des evenements et des boutons*/
void event_option(game_state* state)
{  
    SDL_Event event;
		int i;

    SDL_WaitEvent(&event);
  switch(event.type)
    {
    case SDL_QUIT:
      state->continuer = 0;
      break;
		case SDL_MOUSEBUTTONDOWN:
		
		for(i=0;i<=8;i++){
			if(has_in(state->common_data->option->buttons[i],event.button.x,event.button.y)){
				state->common_data->option->buttons[i]->on_click(state);
				break;
			}
		}
    break;
    default:
      break;

    }
}
/*affichage */
void display_option(game_state* state,displayer* d)
{	      
    int i=0;
    blit_background(d,state->background);
    blit_text(d,"Sound",340,50);
		blit_text(d,"Theme",340,220);
		blit_text(d,"Difficulty",320,380);

    for (; i<9; ++i)
    {
	blit_button(d,state->common_data->option->buttons[i]);
    }
    blit_text(d,"MENU",10,10);		
		
    flip_screen(d);
}
/*initialisation*/
void init_option(game_state* state,displayer* d)
{
    options* opt=0;
    load_options(state->common_data->option);
    opt=state->common_data->option;
		if(opt->sound==0) opt->activ_sound=0;
		else opt->activ_sound=1;
    state->common_data->option->buttons[0]=create_button(&on_click_menu,"MENU",255,0,0,0,10,131,10,46,TTF_STYLE_NORMAL);
    state->common_data->option->buttons[1]=create_button(&on_click_sound_on,"ON",255,0,0,0,250,62,120,42,TTF_STYLE_NORMAL);
    state->common_data->option->buttons[2]=create_button(&on_click_sound_off,"OFF",255,0,0,0,500,116,120,42,TTF_STYLE_NORMAL);
    state->common_data->option->buttons[3]=create_button(&on_click_theme_one,"1",255,0,0,0,250,25,300,55,TTF_STYLE_NORMAL);
    state->common_data->option->buttons[4]=create_button(&on_click_theme_two,"2",255,0,0,0,400,25,300,55,TTF_STYLE_NORMAL);
    state->common_data->option->buttons[5]=create_button(&on_click_theme_three,"3",255,0,0,0,550,25,300,55,TTF_STYLE_NORMAL);
    state->common_data->option->buttons[6]=create_button(&on_click_diff_easy,"EASY",255,0,0,0,150,120,470,55,TTF_STYLE_NORMAL);
    state->common_data->option->buttons[7]=create_button(&on_click_diff_medium,"MEDIUM",255,0,0,0,325,175,470,55,TTF_STYLE_NORMAL);
    state->common_data->option->buttons[8]=create_button(&on_click_diff_hard,"HARD",255,0,0,0,550,115,470,55,TTF_STYLE_NORMAL);
    if (opt->sound)
	on_click_sound_on(state);
    else
    	on_click_sound_off(state);

    if (opt->graphic_chosen==1)
	on_click_theme_one(state);
    else if(opt->graphic_chosen==2)
    	on_click_theme_two(state);
    else
	on_click_theme_three(state);


    if (opt->diff==0)
	on_click_diff_easy(state);
    else if(opt->graphic_chosen==1)
	on_click_diff_medium(state);
    else
	on_click_diff_hard(state);
	

    
    state->background=IMG_Load("./data/images/option.jpg"); 
    state->next=option;
    state->initialized=1;
}
/* Les boutons de l'ecran des scores*/
void on_click_menu(game_state* state){
	state->next=menu;
}

void set_button(bouton* b,int actif,int style)
{
    b->actif=actif;
    b->style=style;


}
void on_click_sound_on(game_state* state){
	if(!(state->common_data->option->buttons[1]->actif)){
	    set_button(state->common_data->option->buttons[1],1,TTF_STYLE_UNDERLINE);
	    set_button(state->common_data->option->buttons[2],0,TTF_STYLE_NORMAL);
			if(state->common_data->option->activ_sound==0) {
				Mix_PlayMusic(state->common_data->musiques[0], -1);
				state->common_data->option->activ_sound=1;
			}
			else Mix_ResumeMusic();
	    state->common_data->option->sound=1;
	    save_options(*(state->common_data->option));
	}
}
void on_click_sound_off(game_state* state){
	if(!(state->common_data->option->buttons[2]->actif)){

	    set_button(state->common_data->option->buttons[2],1,TTF_STYLE_UNDERLINE);
	    set_button(state->common_data->option->buttons[1],0,TTF_STYLE_NORMAL);
			Mix_PauseMusic();
	    state->common_data->option->sound=0;
	    save_options(*(state->common_data->option));
	}
}
void on_click_theme_one(game_state* state){
	if(!(state->common_data->option->buttons[3]->actif)){

	    set_button(state->common_data->option->buttons[3],1,TTF_STYLE_UNDERLINE);
	    set_button(state->common_data->option->buttons[4],0,TTF_STYLE_NORMAL);
	    set_button(state->common_data->option->buttons[5],0,TTF_STYLE_NORMAL);
	
	    state->common_data->option->graphic_chosen=1;
	    save_options(*(state->common_data->option));
	}
}
void on_click_theme_two(game_state* state){
	if(!(state->common_data->option->buttons[4]->actif)){
	
	    set_button(state->common_data->option->buttons[4],1,TTF_STYLE_UNDERLINE);
	    set_button(state->common_data->option->buttons[3],0,TTF_STYLE_NORMAL);
	    set_button(state->common_data->option->buttons[5],0,TTF_STYLE_NORMAL);
	
	    state->common_data->option->graphic_chosen=2;
	    save_options(*(state->common_data->option));
	}
}
void on_click_theme_three(game_state* state){
	if(!(state->common_data->option->buttons[5]->actif)){

	    set_button(state->common_data->option->buttons[5],1,TTF_STYLE_UNDERLINE);
	    set_button(state->common_data->option->buttons[3],0,TTF_STYLE_NORMAL);
	    set_button(state->common_data->option->buttons[4],0,TTF_STYLE_NORMAL);

	    state->common_data->option->graphic_chosen=3;
	    save_options(*(state->common_data->option));
	}
}
void on_click_diff_easy(game_state* state){
	if(!(state->common_data->option->buttons[6]->actif)){
	
	    set_button(state->common_data->option->buttons[6],1,TTF_STYLE_UNDERLINE);
	    set_button(state->common_data->option->buttons[7],0,TTF_STYLE_NORMAL);
	    set_button(state->common_data->option->buttons[8],0,TTF_STYLE_NORMAL);

		state->common_data->option->diff=0;
		save_options(*(state->common_data->option));
	}
}
void on_click_diff_medium(game_state* state){
	if(!(state->common_data->option->buttons[7]->actif)){
	    set_button(state->common_data->option->buttons[7],1,TTF_STYLE_UNDERLINE);
	    set_button(state->common_data->option->buttons[6],0,TTF_STYLE_NORMAL);
	    set_button(state->common_data->option->buttons[8],0,TTF_STYLE_NORMAL);
	    state->common_data->option->diff=1;
	    save_options(*(state->common_data->option));
	}
}
void on_click_diff_hard(game_state* state){
	if(!(state->common_data->option->buttons[8]->actif)){
	    set_button(state->common_data->option->buttons[8],1,TTF_STYLE_UNDERLINE);
	    set_button(state->common_data->option->buttons[6],0,TTF_STYLE_NORMAL);
	    set_button(state->common_data->option->buttons[7],0,TTF_STYLE_NORMAL);

	    state->common_data->option->diff=2;
	    save_options(*(state->common_data->option));
	}
}



int has_in(bouton* button,int x,int y){
	
	if((x > button->x && x < (button->x + button->dx))&&(y > button->y && y < (button->y + button->dy))){
		return 1;
	}
	else return 0;
}
/*creation d'un bouton a partir des donnees utiles*/
bouton* create_button(click_handler on_click,char* str,int r,int g,int b, int actif, int x, int dx, int y, int dy, int style){
 
    bouton* button=malloc(sizeof(*button));
    build_string(&(button->text));
    button->on_click=on_click;
    button->text.ptr=str;
    button->color.r=r;
    button->color.g=g;
    button->color.b=b;
    button->actif=actif;
    button->x=x;
    button->dx=dx;
    button->y=y;
    button->dy=dy;
    button->style=style;
	
    return button;
}

void destruct_button(bouton* button){
	destruct_string(&(button->text));
	free(button);
}



