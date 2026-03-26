#include "ennemies.h"

ennemies init_ennemies(int type, float x, float y, float z){
    vecteur v, cible;
    ennemies e;
    v.x = x;
    v.y = y;
    v.z = z;
    e.type = type;
    e.position = v;
    // cible aléatoire au sol

    cible.x = random_float(-5, 5);
    cible.y = random_float(-5, 5);
    cible.z = 0;

    // direction = cible - position
    e.direction = soustraction(cible, e.position);
    e.direction = normalisation(e.direction);
    e.velocite = 0.01;
    /*Notre ennemie est un astéroide*/
    if(type == 1){
        
    }else{
        /*Notre ennemie est un vaisseau*/

    }
    return e;
}
void afficher_ennemi(ennemies e){
    glColor3f(0.368, 0.275, 0.078);
    glPushMatrix();
    glTranslatef(e.position.x, e.position.y, e.position.z);
    glutSolidSphere(2, 20, 20);
    glPopMatrix();
}


float random_float(float min, float max){
    return min + (float)rand() / RAND_MAX * (max - min);
}

    

void update_ennemies(ennemies *e){
    e->position.x += e->direction.x * e->velocite;
    e->position.y += e->direction.y * e->velocite;
    e->position.z += e->direction.z * e->velocite;
}