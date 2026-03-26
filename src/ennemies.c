#include "ennemies.h"

ennemies init_ennemies(int type, float x, float y, float z){
    vecteur v;
    ennemies e;
    v.x = x;
    v.y = y;
    v.z = z;
    e.type = type;
    e.position = v;
    /*Notre ennemie est un astéroide*/
    if(type == 1){
        
    }else{
        /*Notre ennemie est un vaisseau*/

    }
    return e;
}
void afficher_ennemi(ennemies e){
    glPushMatrix();
    glTranslatef(e.position.x, e.position.y, e.position.z);
    if(e.type == 1){
        glutSolidSphere(2, 40, 40);
    } else {
        // dessiner vaisseau
    }
    glPopMatrix();
}