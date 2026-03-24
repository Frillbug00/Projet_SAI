#ifndef _JOUEUR_H_
#define _JOUEUR_H_

#include "stdio.h"
#include "stdlib.h"
#include "GL/gl.h"
#include "GL/glut.h"
#include "math.h"
#include "vecteur.h"

/*--------------OBSOLETE------------------*/
vecteur rota_autour_Z(vecteur v, float angle);
vecteur rota_autour_Y(vecteur v, float angle);
vecteur rota_autour_X(vecteur v, float angle);
/*--------------OBSOLETE------------------*/
vecteur rodriguez(vecteur vect, vecteur axe, float angle);

#endif