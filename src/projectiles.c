#include "projectiles.h"
#include "ennemies.h"

int nb_projectiles;
projectiles l_p[NB_MAX_PROJECTILES];

projectiles init_projectile(int type, vecteur p, vecteur direction) {
    projectiles proj;
    proj.type = type;
    proj.position = p;
    proj.velocite = 0.3;
    proj.direction = direction;
    proj.boucle = 0;
    return proj;
}

void init_liste_projectile() {
    for (int i = 0; i < NB_MAX_PROJECTILES; i++) {
        l_p[i].type = 0;
    }
}

void afficher_projectile(projectiles *proj) {
    glColor3f(1, 0, 0);
    glPushMatrix();
    glTranslatef(proj->position.x, proj->position.y, proj->position.z);
    glutSolidSphere(RAYON_PROJ, 20, 20);
    glPopMatrix();
}

// Retourne 1 si collision avec un ennemi (et détruit les deux)
int verifier_collision_projectile(projectiles *proj) {
    for (int i = 0; i < nb_ennemies; i++) {
        vecteur le_pos = l_e[i].position;

        if(l_e[i].type == 1){
            /*Asteroide */
            vecteur diff = soustraction(le_pos, proj->position);
            float distance = diff.x*diff.x + diff.y*diff.y + diff.z*diff.z;
            float seuil = (RAYON + RAYON_PROJ) * (RAYON + RAYON_PROJ);
            if(distance <= seuil){
                printf("IMPACT : missile a detruit un asteroide\n");
                l_e[i].type = 0;
                proj->type = 0;
                score += 100;
                return 1;
            }
        }
        else if(l_e[i].type == 2){
            /*Vaisseau*/
            float dx = fabs(le_pos.x - proj->position.x);
            float dy = fabs(le_pos.y - proj->position.y);
            float dz = fabs(le_pos.z - proj->position.z);
            if(dx < 6.5f + RAYON_PROJ && dy < 4.5f + RAYON_PROJ && dz < 1.8f + RAYON_PROJ){
                printf("IMPACT : missile a detruit un vaisseau\n");
                score += 300;
                l_e[i].type = 0;
                proj->type = 0;
                return 1;
            }
        }
    }
    return 0;
}
void update_projectile(projectiles *proj) {
    proj->position.x += proj->direction.x * proj->velocite;
    proj->position.y += proj->direction.y * proj->velocite;
    proj->position.z += proj->direction.z * proj->velocite;
    proj->boucle += 1;

    if (proj->boucle >= 500) {
        proj->type = 0;
        return;
    }

    verifier_collision_projectile(proj);
}

void update_projectiles() {
    for (int i = 0; i < NB_MAX_PROJECTILES; i++) {
        if (l_p[i].type != 0) {
            update_projectile(&l_p[i]);
        }
    }
}

void afficher_projectiles() {
    for (int i = 0; i < NB_MAX_PROJECTILES; i++) {
        if (l_p[i].type != 0) {
            afficher_projectile(&l_p[i]);
        }
    }
}

void tirer_projectile(vecteur p, vecteur direction) {
    for (int i = 0; i < NB_MAX_PROJECTILES; i++) {
        if (l_p[i].type == 0) {
            l_p[i] = init_projectile(1, p, direction);
            return;
        }
    }
}

void tirer_double_projectile(vecteur position, vecteur devant, vecteur droite, vecteur haut) {
    float dist_devant = 5.0;  /*distance devant le joueur*/
    float ecart       = 2.0;  // écart gauche/droite (en unités monde)
    float hauteur     = 1.5;  // décalage vers le bas

    vecteur base = addition(position, produit(devant, dist_devant));

    // Missile gauche
    vecteur pos_gauche = addition(
        base,
        addition(
            produit(droite, -ecart),
            produit(haut,   -hauteur)
        )
    );

    // Missile droit 
    vecteur pos_droite = addition(
        base,
        addition(
            produit(droite,  ecart),
            produit(haut,   -hauteur)
        )
    );

    tirer_projectile(pos_gauche, devant);
    tirer_projectile(pos_droite, devant);
}