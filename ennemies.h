#ifndef _ENNEMIES_H_
#define _ENNEMIES_H_

#include "stdio.h"
#include "stdlib.h"
#include "GL/gl.h"
#include "GL/glut.h"
#include "math.h"
#include "vecteur.h"

typedef struct {
    int type;
    float velocite;
    vecteur position, devant, haut, droite;
}ennemies;


#endif