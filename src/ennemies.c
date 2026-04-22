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

    /* direction initiale */
    if(type == 1){
        cible.x = random_float(x-MARGE, x+MARGE);
        cible.y = random_float(y-MARGE, y+MARGE);
        cible.z = 0;
    }else if(type == 2){
        cible.x = random_float(x-MARGE, x+MARGE);
        cible.y = random_float(y-MARGE, y+MARGE);
        cible.z = z;
    }

    e.direction = normalisation(soustraction(cible, e.position));
    e.velocite = VELOCITE;

    return e;
}
void afficher_vaisseau(ennemies *e){
    glPushMatrix();
    glTranslatef(e->position.x, e->position.y, e->position.z);

    /*Orientation dans la direction du déplacement*/
    float angle = atan2(e->direction.y, e->direction.x) * 180.0 / 3.14;
    glRotatef(angle, 0, 0, 1);

    /*Corps*/
    glColor3f(0.25f, 0.25f, 0.30f);
    glPushMatrix();
    glScalef(4.0, 0.8, 0.6);
    glutSolidCube(2);
    glPopMatrix();

    /*Nez*/
    glColor3f(0.35f, 0.35f, 0.40f);
    glPushMatrix();
    glTranslatef(4, 0, 0);
    glRotatef(90, 0, 1, 0);
    glutSolidCone(0.6, 2.5, 12, 4);
    glPopMatrix();

    /*Cockpit bulle bleu*/
    glColor3f(0.2f, 0.7f, 1.0f);
    glPushMatrix();
    glTranslatef(1.5, 0, 0.7);
    glScalef(1.2, 0.8, 0.5);
    glutSolidSphere(0.8, 12, 12);
    glPopMatrix();

    /*Aile gauche */
    glColor3f(0.20f, 0.20f, 0.25f);
    glBegin(GL_TRIANGLES);
    glVertex3f( 2.0f, 0.0f,  0.0f);   /*base avant*/
    glVertex3f(-2.5f, -4.5f,  0.0f);   /*pointe extérieure*/
    glVertex3f(-2.0f, 0.0f,  0.0f);   /*base arrière*/
    glEnd();

    /*Aile droite : symétrique*/
    glBegin(GL_TRIANGLES);
    glVertex3f( 2.0f,  0.0f,  0.0f);
    glVertex3f(-2.5f,  4.5f,  0.0f);
    glVertex3f(-2.0f,  0.0f,  0.0f);
    glEnd();

   

    glPopMatrix();
}
void afficher_ennemi(ennemies *e){

    if(e->type == 1){
        /* astéroïde */
        glColor3f(0.368, 0.275, 0.078);
        glPushMatrix();
        glTranslatef(e->position.x, e->position.y, e->position.z);
        glutSolidSphere(RAYON, 20, 20);
        glPopMatrix();
    }

    else if(e->type == 2){
        /* vaisseau */
        afficher_vaisseau(e);
    }
}


float random_float(float min, float max){
    return min + (float)rand() / RAND_MAX * (max - min);
}
    

void update_ennemi(ennemies* e){
    e->position.x += e->direction.x * e->velocite;
    e->position.y += e->direction.y * e->velocite;
    e->position.z += e->direction.z * e->velocite;
    if(e->position.z+RAYON <=0){
        e->type = 0;
    }
}

void update_ennemies(vecteur devant, vecteur p){
    int type, alea;
    for(int i = 0; i < nb_ennemies; i++){
        update_ennemi(&l_e[i]);

        /* Si l'ennemi est mort */
        if(l_e[i].type == 0){
            vecteur spawn;
            vecteur dir;

            /* direction aléatoire autour du joueur */
            dir.x = random_float(-1, 1);
            dir.y = random_float(-1, 1);
            dir.z = random_float(0.2, 1);
            dir = normalisation(dir);

            float distance = random_float(30, 120);

            spawn.x = p.x + dir.x * distance;
            spawn.y = p.y + dir.y * distance;
            spawn.z = p.z + dir.z * distance;

            type = 1;
            alea = rand() % TAUX_VAISSEAUX;

            if(alea == 1){
                type = 2;
            }
            l_e[i] = init_ennemi(type, spawn.x, spawn.y, spawn.z);
        }
    }

    /* Initialisation au début seulement */
    while(nb_ennemies < NB_MAX_ENNEMIES){
        vecteur spawn;
        vecteur dir;

        dir.x = random_float(-1, 1);
        dir.y = random_float(-1, 1);
        dir.z = random_float(0.2, 1);
        dir = normalisation(dir);

        float distance = random_float(30, 120);

        spawn.x = p.x + dir.x * distance;
        spawn.y = p.y + dir.y * distance;
        spawn.z = p.z + dir.z * distance;
        type = 1;
        alea = rand() % TAUX_VAISSEAUX;

        if(alea == 1){
            type = 2;
        }
        l_e[nb_ennemies] = init_ennemi(type, spawn.x, spawn.y, spawn.z);
        nb_ennemies++;
    }
}


void afficher_ennemies(){
    for(int i=0; i<nb_ennemies;i++){
        afficher_ennemi(&l_e[i]);
    }
}