#include "scores.h"
#include "game_state.h"
#include "displayer.h"
#include "states.h"
#include "mystring.h"
#include "options.h"
#include "math.h"
#include <SDL/SDL_image.h>

/*fonction d'affichage des scores, gere l'application des boutons*/
void display_scores(game_state* state,displayer* d)
{	

  FILE* fsco = NULL;
	char currentchar;
	int nb_score;
	char** tab_str;
	int* tab_scores;
	int i;
	int j;
	int p;
	int page=state->common_data->score->page;
	blit_background(d,state->background);
	/*determination du fichier a charger*/
	if(fabs((state->common_data->score->difficulty)%3)==0){
		fsco = fopen("./data/options/scores_easy.txt","r+");
		blit_text(d,"EASY",340,50);
	}	
	else if(fabs((state->common_data->score->difficulty)%3)==1){
		fsco = fopen("./data/options/scores_medium.txt","r+");
		blit_text(d,"MEDIUM",320,50);
	}
	else{ 
		fsco = fopen("./data/options/scores_hard.txt","r+");
		blit_text(d,"HARD",340,50);
	}
	SDL_SetColorKey(state->common_data->score->fleche[0], SDL_SRCCOLORKEY, SDL_MapRGB(state->common_data->score->fleche[0]->format,255,255,255));
	SDL_SetColorKey(state->common_data->score->fleche[1], SDL_SRCCOLORKEY, SDL_MapRGB(state->common_data->score->fleche[1]->format,255,255,255));
	SDL_SetColorKey(state->common_data->score->fleche[2], SDL_SRCCOLORKEY, SDL_MapRGB(state->common_data->score->fleche[2]->format,255,255,255));
	SDL_SetColorKey(state->common_data->score->fleche[3], SDL_SRCCOLORKEY, SDL_MapRGB(state->common_data->score->fleche[3]->format,255,255,255));
	blit_img(d,state->common_data->score->fleche[0],225,50,d->screen);
	blit_img(d,state->common_data->score->fleche[1],535,50,d->screen);
	blit_img(d,state->common_data->score->fleche[2],700,200,d->screen);
	blit_img(d,state->common_data->score->fleche[3],700,450,d->screen);
	/*lecture du fichier*/
	blit_text(d,"MENU",10,10);

	fscanf(fsco,"%d",&nb_score);
	rewind(fsco);
	while(currentchar!='\n'){
		currentchar=fgetc(fsco);
	}
		tab_scores=malloc(nb_score*sizeof(int));
		tab_str = malloc(nb_score* sizeof(*tab_str)); 
		for(i=0;i<nb_score;i++){
			j=0;
			tab_str[i] = malloc(MAX_SIZE*sizeof(**tab_str)); 
			while (currentchar !=' '){
				tab_str[i][j]=currentchar;
				j++;
				tab_str[i][j]='\0';
				currentchar=fgetc(fsco);
			}
			fscanf(fsco,"%d",&tab_scores[i]);
			currentchar=fgetc(fsco);
		}	
	
	tri(tab_scores,nb_score,tab_str);
	p=0;
	for(i=5*page;i<5*page+5;i++){
		char* s;
		if(i>=nb_score){
			break;
		}
		s=stringify_int(tab_scores[i]);
		blit_text(d,tab_str[i],100,120+p*80);
		blit_text(d,s,340,120+p*80);
		/*attribution des rangs*/
		if(tab_scores[i]>5000)	blit_text(d,"Alien",480,120+p*80);	
		else if(tab_scores[i]>=3000 && tab_scores[i]<=5000)	blit_text(d,"Zombie",480,120+p*80);
		else if(tab_scores[i]>=1000 && tab_scores[i]<3000)	blit_text(d,"Mutant",480,120+p*80);
		else if(tab_scores[i]<1000)	blit_text(d,"Fantome",480,120+p*80);
		p++;
		free(s);
	}
	
	fclose(fsco);
		
  flip_screen(d);

	for(i=0;i<nb_score;i++){
		free(tab_str[i]);
	}
	free(tab_str);
	free(tab_scores);
}
/*initialisation de l'ecran et des boutons*/
void init_scores(game_state* state,displayer* d)
{ 	
    state->background=IMG_Load("./data/images/livre.jpg"); 
		state->common_data->score->fleche[0]=IMG_Load("./data/images/flechegauche.png");
		state->common_data->score->fleche[1]=IMG_Load("./data/images/flechedroite.png");
		state->common_data->score->fleche[2]=IMG_Load("./data/images/flechehaut.png");
		state->common_data->score->fleche[3]=IMG_Load("./data/images/flechebas.png");
    state->next=score;
    state->initialized=1;
		state->common_data->score->button[0]=create_button(&on_click_menu,"MENU",255,0,0,0,10,131,10,46,TTF_STYLE_NORMAL);
    state->common_data->score->button[1]=create_button(&on_click_gauche," ",255,0,0,0,225,50,50,50,TTF_STYLE_NORMAL);
    state->common_data->score->button[2]=create_button(&on_click_droit," ",255,0,0,0,535,50,50,50,TTF_STYLE_NORMAL);
    state->common_data->score->button[3]=create_button(&on_click_haut," ",255,0,0,0,700,50,200,50,TTF_STYLE_NORMAL);
    state->common_data->score->button[4]=create_button(&on_click_bas," ",255,0,0,0,700,50,450,50,TTF_STYLE_NORMAL);
}
/*gestion des evenements sur les boutons*/
void event_scores(game_state* state)
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
		
		for(i=0;i<=4;i++){
			if(has_in(state->common_data->score->button[i],event.button.x,event.button.y)){
				state->common_data->score->button[i]->on_click(state);
				break;
			}
		}
    break;
    default:
      break;
    }
}
/*ensemble de fonctions de tri de tableaux d'entiers*/
int indice_max(int tab[MAX_SCORES],int inf,int sup){	
	int j;					
	int max=tab[inf];			
	int a=inf;
	for(j=inf;j<sup;j++){
		if(tab[j]>max){
			max=tab[j];
			a=j;
		}
	}
	return a;
}

void permuter(int *a,int *b){			
	int temp;				
	temp=*a;
	*a=*b;
	*b=temp;
}

void permuter_str(char *a,char *b){			
	char *temp;
	temp=malloc(strlen(a));				
	strcpy(temp,a);
	strcpy(a,b);
	strcpy(b,temp);
}
	
void tri(int* tab,int n,char** str_tab){
	int i;
	int a;
	for(i=0;i<n;i++){
		a=indice_max(tab,i,n);
		permuter(tab+a,tab+i);
		permuter_str(str_tab[a],str_tab[i]);	
	}					
	return;
}
/*liberation de la memoire*/
void destruct_scores(scores* sc){
	int i;
	destruct_string(&(sc->name));
	for(i=0;i<=5;i++){
		destruct_button(sc->button[i]);
	}
	for(i=0;i<=4;i++){
		SDL_FreeSurface(sc->fleche[i]);
	}
	free(sc);
}

scores* create_scores(){
	scores* score=malloc(sizeof(*score));
	build_string(&(score->name));
	score->value=0;
	score->difficulty=0;
	score->page=0;
	return score;
}
void save_scores(game_state* state){
	FILE* fsco = NULL;
	if(state->common_data->score->difficulty==easy){
		fsco = fopen("./data/options/scores_easy.txt","r+");
		print_scores(state,fsco);
	}
	else if(state->common_data->score->difficulty==medium){
		fsco = fopen("./data/options/scores_medium.txt","r+");
		print_scores(state,fsco);
	}
	else{
		fsco = fopen("./data/options/scores_hard.txt","r+");
		print_scores(state,fsco);
	}
	fclose(fsco);
}
void print_scores(game_state* state, FILE* fsco){
    char currentchar;
	char* s; 
	int nb_score;
	fscanf(fsco,"%d",&nb_score);
	rewind(fsco);
	fprintf(fsco,"%d",nb_score+1);
	fputc('\n', fsco);
	currentchar=fgetc(fsco);
	while(currentchar!=EOF){
		currentchar=fgetc(fsco);
	}
/*	fputc('\n', fsco);	*/
	fputs(state->common_data->score->name.ptr, fsco);
	fputc(' ', fsco);
	s=stringify_int(state->common_data->score->value);
	fputs(s, fsco);
	free(s);
}	
void on_click_gauche(game_state* state){
	state->common_data->score->difficulty--;
	state->common_data->score->page = 0;
}
void on_click_droit(game_state* state){
	state->common_data->score->difficulty++;
	state->common_data->score->page = 0;
}
void on_click_haut(game_state* state){
	if(state->common_data->score->page != 0) state->common_data->score->page--;
}
void on_click_bas(game_state* state){
	state->common_data->score->page++;
}
