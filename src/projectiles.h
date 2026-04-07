#ifndef _PROJECTILES_H_
#define _PROJECTILES_H_
#include "math.h"
#include "vecteur.h"
#define NB_MAX_PROJECTILES 100
#define RAYON_PROJ 0.1
typedef struct projectiles{
    int boucle;
    int type;
    float velocite;
    vecteur position, direction;
}projectiles;

extern projectiles l_p[NB_MAX_PROJECTILES];

projectiles init_projectile(int type, vecteur p, vecteur devant);

void init_liste_projectile();

void afficher_projectile(projectiles *proj);

void update_projectile(projectiles *proj);

void afficher_projectiles();

void update_projectiles();

void tirer_projectile(vecteur p, vecteur devant);

void tirer_double_projectile(vecteur position, vecteur devant, vecteur droite, vecteur haut);

int verifier_collision_projectile(projectiles *proj);
#endif