#ifndef LEVEL_H 
#define LEVEL_H 
/*structure point contenant les coordonnees d'un point*/
typedef struct point point;
struct point{
	int x,y;
};
/*structure contenant les points d'un niveau dans un tableau et le nombre de points*/
typedef struct level level;
struct level
{
   /*nombre de point dans un niveau*/
    int size;
    point* points;

    int nb_ball_restante;
    int nb_ball_originale;

    int nb_color;
};

level* load_level(const char* name);
level* load_level2(const char* name);
void destroy_level(level* l);
void save_level(level l,const char* name);
#endif
