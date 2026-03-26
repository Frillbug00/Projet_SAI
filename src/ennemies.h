#ifndef _ENNEMIES_H_
#define _ENNEMIES_H_

#include "stdio.h"
#include "stdlib.h"
#include "GL/gl.h"
#include "GL/glut.h"
#include "math.h"
#include "vecteur.h"
#define NB_MAX_ENNEMIES 20
#define RAYON 2
typedef struct ennemies{
    int type;
    float velocite;
    vecteur position, direction;
}ennemies;
int nb_ennemies = 0;
ennemies l_e[];
ennemies init_ennemi(int type, float x, float y, float z);

void afficher_ennemi(ennemies e);

void update_ennemi(ennemies *e);

void afficher_ennemies(ennemies e);

void update_ennemies(ennemies *e);

float random_float(float min, float max);

#endif