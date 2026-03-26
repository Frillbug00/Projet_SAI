#ifndef _ENNEMIES_H_
#define _ENNEMIES_H_

#include "stdio.h"
#include "stdlib.h"
#include "GL/gl.h"
#include "GL/glut.h"
#include "math.h"
#include "vecteur.h"

typedef struct ennemies{
    int type;
    float velocite;
    vecteur position, direction;
}ennemies;

ennemies init_ennemies(int type, float x, float y, float z);

void afficher_ennemi(ennemies e);

void update_ennemies(ennemies *e);

float random_float(float min, float max);

#endif