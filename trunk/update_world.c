#include "list_ball.h"
#include "sprite.h"
#include "discontinuity.h"
#include "data_jeu.h"
#include "constante.h"

#include "update_world.h"

int distance2(int x,int y){return x*x+y*y;}
int distance_point(point* p1,point* p2)
{
    return distance2(p1->x-p2->x,p1->y-p2->y);
}

/*Remet le projectile au centre en en changeant l'image */
void reset_projectile(data_jeu* tmp_data)
{
    projectile* p=&(tmp_data->cannonball);
    int image_sprite=rand()%(tmp_data->current_level->nb_color);
    int size=size_list_ball(tmp_data->file_balls);

    /*Permet en fin de niveau de n'avoir que de balles qui existent dans le cortege*/
    if( size>0 && size< 10 && tmp_data->current_level->nb_ball_restante == 0 )
    {
	while(tmp_data->nb_type_playing[image_sprite]==0)
	{
	    image_sprite=rand()%(tmp_data->current_level->nb_color);
	}
    }   

    tmp_data->throw_projectile=1;
    p->img=tmp_data->img_ball[image_sprite];
    p->pos.x=largeur/2;
    p->pos.y=hauteur/2;
    p->u=0;
    p->v=0;
}

/*Ce code marche car au moment de l'insertin it et balle_inseree sont au meme point courant*/
void avancer_balls(node_ball* it,list_ball* l)
{
    int i=0;
    while(it!=l->head )
    {
	for(i=0;i<32;++i)
	{
	    go_forward(&(it->val));
	}
	it=it->previous;
    }
}

/*Permet de trouver l'index de l'image du projectile */
int find_index_projectile(SDL_Surface* projectile_img, SDL_Surface** img_ball)
{
    int i=0;

    while(*(img_ball+i)!=projectile_img)
	i++;

    return i;
}

/*Reconstruit la liste des discontinuite depuis 0*/
void research_discontinuity(data_jeu* d)
{
    list_ball* l=&(d->file_balls);
    node_ball* it2=begin_list_ball(*l);
    clear_list_discontinuity(&(d->discontinuity));       
    it2=begin_list_ball(*l);
    while(it2 && it2->next)
    {
	if(distance_point(it2->val.point_courant,it2->next->val.point_courant)>=(32*32*COEFF_MAGIQUE))
	{
	    append_list_discontinuity(&(d->discontinuity),it2);
	    append_list_discontinuity(&(d->discontinuity),it2->next);
	}
	it2=it2->next;
    }
}

/*
  TODO : Ne pas hardcoder 32 mais se baser sur la largeur d'une image

  Algoritme.
  On regarde si le projectile a touche une balle (notee it) [recherche en O(n)]; #1
  Si oui, on avance toutes (jusqu'a la premire discontinuite du cortege) les balles entre head et it de 32 px (largeur d'une image) #2
  Apres, on compte les balles de la meme couleur qui sont avant et apres  #3
  Si y'en a plus de 3, on les supprimes de la liste,  #4
  sinon on en fait rien
  Apres, on compare les nouvelles boules. #5
  Si meme couleur, le cortege avant recule pendant que l'autre s'arrete.
  Si pas meme couleur, le cortege avant s'arrete pendant que le cortege arriere continue d'avancer.
*/

void check_colision(data_jeu* d)
{
    list_ball* l=&(d->file_balls);
    projectile* p=&(d->cannonball);

    node_ball* it=begin_list_ball(*l);
    node_ball* balle_inseree=0;

    while(it)
    {
        /*#1*/
        if((distance2(p->pos.x-it->val.point_courant->x,p->pos.y-it->val.point_courant->y)<32*32*1.4))
        {
	    int trouve =0;
            int nb_same_ball=1;
            node_ball* it_forward=0;
            node_ball* it_backward=0;
            node_ball* begin=0;
	    
	    node_discontinuity* r;
	    
	    /*On insere une balle au meme point courant que it*/
            insert2_list_ball(l,it,create_sprite(p->img,it->val.point_courant));
            d->nb_type_playing[find_index_projectile(p->img,d->img_ball)]++;
            
            begin=begin_list_ball(*l);
            balle_inseree=it->next; /*On pointe sur la balle inseree puis on lui donne le meme mouvement que celle avant*/
            balle_inseree->val.current_movement=it->val.current_movement;

            /*comptage du nombre de boule*/
            it_forward=balle_inseree;
            while(it_forward->next && it_forward->next->val.img==balle_inseree->val.img)
            {       
                nb_same_ball++;
                it_forward=it_forward->next;
            }

            it_backward=balle_inseree;
            while(it_backward->previous !=begin->previous && it_backward->previous->val.img==balle_inseree->val.img)
            {
                nb_same_ball++;
                it_backward=it_backward->previous;
            }

          
                /*
                  Si une balle qu'on touche est deja dans les discontinuite
                    si elle a une position paire (ie est a droite du trou)
                        on on avance la discontinuité (car la balle se place APRES it)
                 */
	    r=find_list_discontinuity(d->discontinuity,it);
	    if(r)
	      {
		int idx=index_list_discontinuity(d->discontinuity,r);
		if(idx%2==0)
		  {
		    r->val=it->next;
		  }
	      }
	      
            /*besoin de supprimer des balles*/
            if(nb_same_ball>2)
            {

		node_ball* first_discontinuity=it_backward;
		node_ball* second_discontinuity=it_forward;
		node_ball* r1=0;
		node_ball* r2=0;

		d->score+=base_score*(nb_same_ball-2);

                /*Pour gerer les cas ou au final il n'y plus qu'une balle seule*/
		if(it_backward!=it_forward)
		{
		    first_discontinuity=it_backward->previous;
		    second_discontinuity=it_forward->next;
		}
		
		r1=first_discontinuity;
		r2=second_discontinuity;
                
                /*Si une des balles qu'on supprime est une discontinuite, on indique
                qu'on va devoir reconstruire depuis zero la liste des discontinuite*/
		while(r1!=r2)
		{
		    if(find_list_discontinuity(d->discontinuity,r1))
		      {trouve=1;break;}
			r1=r1->next;
		}

                /*On retire les boules*/
		d->nb_type_playing[find_index_projectile(p->img,d->img_ball)]-=nb_same_ball;
		remove_range_list_ball(l,it_backward,it_forward);

		if(trouve)
		  {
		    research_discontinuity(d);
		  }
	
		if(size_list_ball(*l)!=0)
		{
		    /*
		    Si on est sur la tete ou sur la queue, besoin de rien faire
		    */
		    if(first_discontinuity!=l->head && second_discontinuity)
		    {        
		        /*Si on a pas shoote une discontinuite, on les ajoute normalement*/
			if(!trouve)
			{
			append_list_discontinuity(&(d->discontinuity),first_discontinuity);
			append_list_discontinuity(&(d->discontinuity),second_discontinuity);
			}

			if(first_discontinuity->val.img==second_discontinuity->val.img)
			{
			  /*On arrete de jeter des balles et on definit les mouvements*/
			  d->throw_projectile=0;  
			  do{
				first_discontinuity->val.current_movement=backward;
				first_discontinuity=first_discontinuity->previous;
			    }
			    while(first_discontinuity!=l->head);

			    do{
				second_discontinuity->val.current_movement=stay_still;
				second_discontinuity=second_discontinuity->next;
			    }
			    while(second_discontinuity && !find_list_discontinuity(d->discontinuity,second_discontinuity));

                            /*Si second_discontinuity n'est plus valide, cela signifie que la 
                            dernière boule du cortege est au niveau du début du chemin, donc il ne faut pas en ajouter tant qu'on re avance pas*/
			    if (!second_discontinuity)
			    {
				d->adding_ball=0;
			    }
			}
			/*boules differentes ; l'avant s'arrête */
			else
			{
			    do{
				first_discontinuity->val.current_movement=stay_still;
				first_discontinuity=first_discontinuity->previous;
			    }                           
			    while(first_discontinuity!=l->head);                        
			}
                    
		    }
		}/*si le cortege est non vide*/
		else
		{
		    printf("cortege vide !!");
		}
            } /*fin nb_same_ball>2: ie aucune boule a supprimer*/
            else
            {
                /*#2 : on avance les boules*/
                if(size_list_ball(*l)!=0)
                    avancer_balls(it,l);
            }
            reset_projectile(d);
            break;
            
        } /*fin check colision*/
        it=it->next;
    } /*fin boucle principale*/

} /*fin fonction*/



void merge_discontinuity(data_jeu* tmp)
{

    list_discontinuity* l=0;
    node_discontinuity* it=0;
    list_ball* file_balls=0 ;int* adding_ball=0 ;
/*
    SDL_mutex* mutex =tmp->mutex;
    SDL_LockMutex(mutex);*/

    l=&(tmp->discontinuity);
    it=begin_list_discontinuity(*l);
    file_balls=&(tmp->file_balls);adding_ball=&(tmp->adding_ball);

    if(size_list_discontinuity(*l)>1)
    {

        while(it && it->next)
        {
            if(it->next && (distance_point(it->next->val->val.point_courant,it->val->val.point_courant)<32*32*COEFF_MAGIQUE)&& it->next->val->val.nb!=it->val->val.nb)
            {

                node_discontinuity* next=it->next->next;
                node_ball* it_ball=it->val;     
                
                /*On retire les discontinuites*/
                remove_node_list_discontinuity(l,it->next);
                remove_node_list_discontinuity(l,it);

                if(it_ball->val.current_movement==backward)
                {
                    /*On dit a la tete de cortege de s'arrete */
                    node_ball* it2_ball=end_list_ball(*file_balls);
                    do
                    {
                        it_ball->val.current_movement=stay_still;
                        it_ball=it_ball->previous;
                    }               while(it_ball!=file_balls->head && !(find_list_discontinuity(*l,it_ball)));
                    
                    /*On dit a l'arriere du cortege de demarer */
                    do
                    {
                        it2_ball->val.current_movement=forward;
                        it2_ball=it2_ball->previous;
                    }   
                    while( (!find_list_discontinuity(*l,it2_ball) )&& it2_ball!=file_balls->head);
                        
                    print2_list_discontinuity(l);                               
                    *adding_ball=1;
		    tmp->throw_projectile=1;
                }
                else if(it_ball->val.current_movement==stay_still)
                {
                    /*On demande au bout de cortege qui s'était arrete avant de repartir*/
                    node_ball* it2_ball=end_list_ball(*file_balls);
                    do
                    {
                        it2_ball->val.current_movement=forward;
                        it2_ball=it2_ball->previous;
                    }                while( (!find_list_discontinuity(*l,it2_ball->next)) && it2_ball!=file_balls->head);
                }
                else
                {
                    printf("SOUCIS \n");
                }
                it=next;
            }
            else
            {
                it=it->next;
            }
        }
    }

   /* SDL_UnlockMutex(mutex);*/
}


