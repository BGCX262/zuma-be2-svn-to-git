#ifndef UPDATE_WORLD_H 
#define UPDATE_WORLD_H 


#include "sprite.h"
#include "data_jeu.h"
#include "discontinuity.h"
#include "list_ball.h"
struct game_state;
/*PROTOTYPE DES FONCTIONS LOCALE A L'UNITE DE COMPILATION*/
int distance2(int x,int y);
int distance_point(point* p1,point* p2);

void add_ball(data_jeu* tmp_data);
void avancer_balls(node_ball* it,list_ball* l);

void update_world(struct game_state *param);
void update_list_ball(list_ball* l);

void check_colision(data_jeu* d); 
void merge_discontinuity(data_jeu* tmp);
void reset_projectile(data_jeu* d);
void research_discontinuity(data_jeu* d);
#endif
