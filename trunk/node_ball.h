#ifndef NODE_BALL_H 
#define NODE_BALL_H 
#include "sprite.h"


typedef struct node_ball node_ball;
struct node_ball
{
    sprite val;
    node_ball* next;
    node_ball* previous;
};
#endif
