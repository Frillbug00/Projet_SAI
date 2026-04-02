#include "ennemies.h"
int nb_ennemies = 0;
ennemies l_e[NB_MAX_ENNEMIES];

ennemies init_ennemi(int type, float x, float y, float z){
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
    e.velocite = 0.05;
    /*Notre ennemie est un astéroide*/
    if(type == 1){
        
    }else{
        /*Notre ennemie est un vaisseau*/

    }
    return e;
}
void afficher_ennemi(ennemies *e){
    glColor3f(0.368, 0.275, 0.078);
    glPushMatrix();
    glTranslatef(e->position.x, e->position.y, e->position.z);
    glutSolidSphere(RAYON, 20, 20);
    glPopMatrix();
}


float random_float(float min, float max){
    return min + (float)rand() / RAND_MAX * (max - min);
}
    

void update_ennemi(ennemies* e){
    e->position.x += e->direction.x * e->velocite;
    e->position.y += e->direction.y * e->velocite;
    e->position.z += e->direction.z * e->velocite;
    if(e->position.z+RAYON <=0){
        printf("Disparition\n");
        e->type = 0;
    }
}

void update_ennemies(vecteur devant, vecteur p){
    for(int i = 0; i < nb_ennemies; i++){
        update_ennemi(&l_e[i]);

        /*Si l'ennemi est mort*/
        if(l_e[i].type == 0){
            vecteur spawn;
            float distance = random_float(15, 100);

            spawn.x = p.x + devant.x * distance;
            spawn.y = p.y + devant.y * distance;
            spawn.z = p.z + devant.z * distance;

            /*Bruit de spawn*/
            spawn.x += random_float(-15, 15);
            spawn.y += random_float(-15, 15);
            spawn.z += random_float(-20, 20);

            l_e[i] = init_ennemi(1, spawn.x, spawn.y, spawn.z);
        }
    }

    // Initialisation au début seulement
    while(nb_ennemies < NB_MAX_ENNEMIES){
        vecteur spawn;
        float distance = random_float(15, 100);

        spawn.x = p.x + devant.x * distance;
        spawn.y = p.y + devant.y * distance;
        spawn.z = p.z + devant.z * distance;
        spawn.x += random_float(-15, 15);
            spawn.y += random_float(-15, 15);
            spawn.z += random_float(-20, 20);

        l_e[nb_ennemies] = init_ennemi(1, spawn.x, spawn.y, spawn.z);
        nb_ennemies++;
    }
}

void afficher_ennemies(){
    for(int i=0; i<nb_ennemies;i++){
        afficher_ennemi(&l_e[i]);
    }
}