#include "editor.h"
#include "game_state.h"
#include "displayer.h"
#include "options.h"
#include "math.h"
#include "jeu.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

/*fonction de gestion des evenements*/
void event_editor(game_state* state)
{  /*savoir si la souris a deja été enfoncée*/
		static int press=0;
    SDL_Event event;
		/*recuperation de l'adresse de la liste*/
    list_points* l=state->specific_data;
    SDL_WaitEvent(&event);
  switch(event.type)
    {
    case SDL_QUIT:
      state->continuer = 0;
      break;
		/*test click droit enfonce*/
    case SDL_MOUSEBUTTONDOWN:
			/*retour au menu*/
      if((event.button.x> 10 && event.button.x< 140 )&&(10<event.button.y && event.button.y<56)){
			state->next=menu;}
			/*test parcours effectue*/
			else if(l->made){
					/*test choix de sauvegarde, si oui la liste est réinitialisée mais toujours disponible*/
					if((event.button.x> 300 && event.button.x< 550 )&&(175<event.button.y && event.button.y<240)){
							save_list_points(l);
							clear_list_points(l);
							l->made=0;
							state->next=menu;
							
					}
					/*test recommencer, si oui tout est reinitialise*/
					else if((event.button.x> 300 && event.button.x< 500 )&&(400<event.button.y && event.button.y<460)){
							destruct_list_points(l);
							construct_list_points(l);
					}
			}

			else{press=1;} 
			
			break;
		/*bouton releve, interpolation du trace, arcours effectue*/
		case SDL_MOUSEBUTTONUP:interpol(l);if(press){l->made=1;} press=0;break;

		/*bouton appuye, souris en mouvement, enregistrement des coordonnees*/		
		case SDL_MOUSEMOTION:
    	 if(press) append_list_points(l,event.button.x,event.button.y);
			
      break;
   
    default:
      break;

    }
}
/*fonction d'affichage de l'editeur*/
void display_editor(game_state* state,displayer* d)
{		
		/*adresse de liste envoyee a specific data*/
    list_points* l=state->specific_data;
    SDL_Surface *carre;
		/*on commence au debut de la liste*/
    node_point* it=begin_list_points(*l);
		carre= l->carre;
		/*ajout du fond d'ecran et de l'image carree*/
    blit_background(d,state->background);
		blit_sprite(d,l->ball,400,300);
		/*affichage du carree sur les valeurs etrées dans la liste*/
    while(it){
	blit_img(d,carre,it->val.x,it->val.y,d->screen);
	it=it->next;
    }
    blit_text(d,"MENU",10,10);		
		/*affichage des textes quand le parcours est fini*/
		if(l->made){
			blit_text(d,"Save Path",300,175);
			blit_text(d,"Try again",300,400);
		}
    flip_screen(d);
}

/*initialisation de l'etat de jeu "editeur"*/
void init_editor(game_state* state,displayer* d)
{
		/*allocation de memoire pour une liste et construction de celle-ci*/
    list_points* l=malloc(sizeof(*l));
    construct_list_points(l);
   	/*on la place dans specific data*/
    state->specific_data=l;
    state->background=IMG_Load("./data/images/cadre.png"); 
    state->next=editor;
		/*etat initialise*/
    state->initialized=1;
}

/*construction d'une liste*/
void construct_list_points(list_points* l)
{
	/*on initialise un noeud en tete et queue et on charge les images*/
  node_point* p=malloc(sizeof(*p));
  p->next=NULL;
  p->previous=NULL;

  l->head=p;
  l->tail=p;
	l->made=0;
  l->size=0;
  l->carre = IMG_Load("./data/images/carre.png");
	l->ball = IMG_Load("./data/images/1/1.png");
}
/*sauvegarde de la liste dansun fichier texte*/
void save_list_points(list_points* l){

	FILE* flist = NULL;
	node_point* it;
	flist = fopen("./data/1.txt","w+");
	fprintf(flist,"%d",l->size);
	fputc('\n', flist);
	it=begin_list_points(*l);
    while(it)
    {
	fprintf(flist,"%d",it->val.x);
	fputc(' ', flist);
	fprintf(flist,"%d",it->val.y);
	fputc('\n', flist);
	it=it->next;
    }
	fclose(flist);
}
/*réinitialisation d'une liste*/
void clear_list_points(list_points* l)
{
		
    node_point* i=begin_list_points(*l);
    node_point* next=NULL;

    while(i!=NULL)
    {
	next=i->next;
	free(i);
	i=next;
    }
    
    l->head->next=0;
    l->tail=l->head;
    l->size=0;
}

/*ajout d'un point à la suite de la liste*/
void append_list_points(list_points* l,int x,int y)
{
	/* on alloue de la mémoire à un noeud et on le place en fin de liste*/
  node_point* p=malloc(sizeof(*p));

  p->val.x=x;
  p->val.y=y;
  p->next=NULL;
  p->previous=l->tail;
  /*n->val.nb=l->tail->val.nb+1;*/

  l->tail->next=p;
  l->tail=p;
  l->size++;
}

/*fonction d'interpolation de points d'une liste expliquee dans le rapport*/
void interpol(list_points* l){	
		node_point* it=NULL;
		int pos=1;
	point temp;
	it=begin_list_points(*l);
	
  if(size_list_points(*l)>1){
		 while(it->next){
				temp=it->val;
				it=it->next;
				if(fabs(temp.x-it->val.x)>1 || fabs(temp.y-it->val.y)>1){
							
				trace(l,temp,it->val,&pos);

				}		
		}
  } 
}
/*fonction traçage de points expliquee dans le rapport*/
void trace(list_points* l,point val1,point val2,int* current_pos){ 
  float lambda;
	point temp1=val1;
	point temp2=val1;
	node_point* node;
	for(lambda=0;lambda<=1;lambda+=0.001){
		temp1.x=(1-lambda)*val1.x+lambda*val2.x;
		temp1.y=(1-lambda)*val1.y+lambda*val2.y;
    if(fabs(temp1.x-temp2.x)==1 || fabs(temp1.y-temp2.y)==1){
		node= find_list_points(*l,temp2);
		insert2_list_points(l,node,temp1);
		(*current_pos)++;
		temp2=temp1;
		}
  } 
}  
/* ecriture dans le terminal d'une liste de points*/
void print_list_points(list_points* l)
{
    node_point* it=begin_list_points(*l);
    while(it)
    {
	printf("%d | %d | ",it->val.x,it->val.y);
	it=it->next;
    }
    printf("\n");
}

/*destruction complète d'une liste de points , liberation de la memoire*/
void destruct_list_points(list_points* l)
{
  clear_list_points(l);
  free(l->head);
	SDL_FreeSurface(l->carre);
}
/*fonctions de recuperation de tete et taile de liste*/
node_point* begin_list_points(list_points l)
{
    return l.head->next;
}
int size_list_points(list_points l)
{
  return l.size;
}
/*test de taille de liste, vide ou non*/
int empty_list_points(list_points l)
{
  return (l.size==0);
}

/*fonction d'insertion d'un point apres un noeud precis*/
void insert2_list_points(list_points* l,node_point* n,point value)
{
  node_point *i=l->head->next;

  while(i!=NULL)
    {
      if(i==n && i!=l->tail)
	{
	      node_point* new_node_point=malloc(sizeof(*n));
	      new_node_point->val=value;
		    new_node_point->next=i->next;
	      new_node_point->next->previous=new_node_point;
	      new_node_point->previous=i;
	      i->next=new_node_point;

	      
	      l->size++;
	      break;
	}
      else if(i==l->tail)
      {
	  append2_list_points(l,value);
	  break;
      }
      i=i->next;
    }

}
/*fonction qui retrouve un noeud à partir d'un point donne*/
node_point* find_list_points(list_points l,point value)
{
  node_point* r=NULL;
  node_point *i=l.head->next;

  while(i!=NULL)
    {
	if(i->val.x==value.x&&i->val.y==value.y)
	{
	  r=i;
	}      
      i=i->next;
    }
  
  return r;
}
/*autre fonction ajoutant un point à la suite de la liste*/
void append2_list_points(list_points* l,point value)
{
  node_point* n=malloc(sizeof(*n));

  n->val=value;
  n->next=NULL;
  n->previous=l->tail;

  l->tail->next=n;
  l->tail=n;
  l->size++;
}

