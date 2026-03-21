#ifndef _VECTEUR_H_
#define _VECTEUR_H_

#include "stdio.h"
#include "stdlib.h"
#include "GL/gl.h"
#include "GL/glut.h"
#include "math.h"

typedef struct vecteur{
    float x,y,z;
}vecteur;

vecteur addition(vecteur vect1, vecteur vect2);
vecteur soustraction(vecteur vect1, vecteur vect2);
vecteur produit_vect(vecteur vect1, float f);
vecteur normalisation(vecteur vect);

#endif