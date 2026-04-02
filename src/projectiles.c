#include "projectiles.h"

int nb_projectiles;
projectiles l_p[NB_MAX_PROJECTILES];

projectiles init_projectile(int type, vecteur p, vecteur devant){
    projectiles proj; proj.type = type; 
    vecteur p_bis;
    p_bis.y = p.y-2.5;
    p_bis.x = p.x;
    p_bis.z = p.z-2.5;
    proj.position = p_bis; 
    proj.velocite = 0.1; 
    proj.direction = devant; 
    proj.boucle = 0; 
    return proj;
}
void init_liste_projectile(){
    for(int i = 0; i < NB_MAX_PROJECTILES; i++){
        l_p[i].type = 0;
    }
}
void afficher_projectile(projectiles *proj){
    glColor3f(1, 0, 0);
    glPushMatrix();
    glTranslatef(proj->position.x, proj->position.y, proj->position.z);
    glutSolidSphere(RAYON_PROJ, 20, 20);
    glPopMatrix();
}

void update_projectile(projectiles* proj){
    proj->position.x += proj->direction.x * proj->velocite;
    proj->position.y += proj->direction.y * proj->velocite;
    proj->position.z += proj->direction.z * proj->velocite;
    proj->boucle+=1;
    if(proj->boucle >= 200){
        printf("Disparition\n");
        proj->type = 0;
    }
}

void update_projectiles(){
    for(int i = 0; i < NB_MAX_PROJECTILES; i++){
        if(l_p[i].type != 0){
            update_projectile(&l_p[i]);
        }
    }
}

void afficher_projectiles(){
    for(int i = 0; i < NB_MAX_PROJECTILES; i++){
        if(l_p[i].type != 0){
            afficher_projectile(&l_p[i]);
        }
    }
}

void tirer_projectile(vecteur p, vecteur devant){
    for(int i = 0; i < NB_MAX_PROJECTILES; i++){
        if(l_p[i].type == 0){ 
            l_p[i] = init_projectile(1, p, devant);
            return;
        }
    }
}

void tirer_double_projectile(vecteur position, vecteur devant, vecteur droite, vecteur haut){
    float dist_devant = 2.0; 
    float ecart = 4;    
    float hauteur = 0.5;

    // point de départ devant le joueur
    vecteur base = addition(position, produit(devant, dist_devant));

    // missile gauche
    vecteur gauche = addition(
        base,
        addition(
            produit(droite, -ecart),
            produit(haut, -hauteur)
        )
    );

    // missile droite
    vecteur droite_missile = addition(
        base,
        addition(
            produit(droite, ecart),
            produit(haut, -hauteur)
        )
    );

    // tirer les deux missiles
    tirer_projectile(gauche, devant);
    tirer_projectile(droite_missile, devant);
}