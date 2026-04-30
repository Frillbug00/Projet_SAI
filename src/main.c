#include "stdio.h"
#include "stdlib.h"
#include "GL/gl.h"
#include "GL/glut.h"
#include "math.h"
#include "vecteur.h"
#include "joueur.h"
#include "ennemies.h"
#include "projectiles.h"
#define NEAR 5
#define V_MAX 0.03
#include "../lib/stb_image.h"

int taille_fenetre = 800;
float taille_joueur = 1;
float rota_z = 0.1; // Rotation autour de z
int touches[256] = {0};
/*Représentation joueur*/
float velocite = 0.015;
float vitesse = 0.0001;
vecteur position = {0,0,40};
vecteur devant = {1,0,0};
vecteur haut = {0,0,1};
vecteur droite = {0,1,0};
int invulnerabilite = 0; // nbr de cycles d'invulnérabilité restant.
int cooldown = 0; // Nbr de cycles restants avant de pouvoir tirer à nouveau
/*---------------------------*/
/*Différentes stats*/
int vie_vaisseau = 10;
int vie_carte = 100;
int score = 0;
/*---------------------------*/
int texture_sol;

void vaisseau_touche(){
    if (invulnerabilite == 0){
        vie_vaisseau --;
        invulnerabilite = 60;
    }
}

int colision(){
    if (position.z <=0+NEAR){
        printf("COLISION : Sous la map\n");
        vaisseau_touche();
        position = addition(position, produit(devant, -velocite));
        velocite = 0;
        printf("Vie restante vaisseau : %d\n", vie_vaisseau);
    }
    for(int i=0;i<nb_ennemies;i++){
        vecteur le_pos = l_e[i].position;
        if(l_e[i].type == 1){
            float d_centre = pow((le_pos.x-position.x), 2)+pow((le_pos.y-position.y), 2)+pow((le_pos.z-position.z), 2);
            float d_rayons = pow(taille_joueur, 2)+pow(RAYON, 2);
            if(d_rayons+5>d_centre){
                printf("COLISION : Asteroide\n");
                vaisseau_touche();
                printf("Vie restante vaisseau : %d\n", vie_vaisseau);
            }
        }else if(l_e[i].type == 2){
            float dx = fabs(le_pos.x - position.x);  /*fuselage+cone : de -4 à +6.5*/
            float dy = fabs(le_pos.y - position.y);  /*ailes : de -4.5 à +4.5*/
            float dz = fabs(le_pos.z - position.z);  /*dérive : de -0.3 à +1.8*/

            if(dx < 6.5f && dy < 4.5f && dz < 1.8f){
                printf("COLISION : Vaisseau\n");
                vaisseau_touche();
                printf("Vie restante vaisseau : %d\n", vie_vaisseau);
            }
        }
    }
}

void affichage_score(){
    char* str_score = "Score :";
    int aff = 0;
    char str_nbr[10];
    char bout;
    float pos_sup;
    int max_taille = 700;

    /*Affichage du mot "score"*/
    sprintf(str_nbr, "%d", score);
    glColor3f(1, 1, 1);
    for (aff = 0; aff < 7; aff++){
        glRasterPos2f(700 + aff * 10,taille_fenetre - 10);
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str_score[aff]);
    }

    /*Affichage du score via un nombre*/
    aff = 0;
    while ((bout = str_nbr[aff]) != '\0'){
        glRasterPos2f(700 + aff * 10,taille_fenetre - 20);
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str_nbr[aff]);
        aff++;
    }
}

void affichage_fin(int raison){
    char* str_raison1 = "Vous etes mort.";
    char* str_raison2 = "La planete a ete detruite.";
    char* str_score = "Score :";
    int aff = 0;
    char str_nbr[10];
    char bout;
    float pos_sup;
    int max_taille = 700;

    /*Affichage de la raison*/

    glColor3f(1, 1, 1);

    if (raison == 0){
        for (aff = 0; aff < 15; aff++){
        glRasterPos2f(taille_fenetre/2-taille_fenetre/4 + aff * 10,taille_fenetre/2);
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str_raison1[aff]);
        }
    }
    else{
        for (aff = 0; aff < 26; aff++){
        glRasterPos2f(taille_fenetre/2-taille_fenetre/4 + aff * 10,taille_fenetre/2);
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str_raison2[aff]);
        }
    }

    /*Affichage du mot "score"*/
    glColor3f(1, 1, 1);
    for (aff = 0; aff < 7; aff++){
        glRasterPos2f(taille_fenetre/2-taille_fenetre/4 + aff * 10,taille_fenetre/2 - 100);
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str_score[aff]);
    }

    /*Affichage du score*/
    sprintf(str_nbr, "%d", score);
    aff = 0;
    while ((bout = str_nbr[aff]) != '\0'){
        glRasterPos2f(taille_fenetre/2-taille_fenetre/4 + aff * 10,taille_fenetre/2 - 110);
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str_nbr[aff]);
        aff++;
    }
}

void affichage_vitesse(){
    char* str_vitesse = "vitesse :";
    int aff = 0;
    char str_nbr[10];
    char bout;
    float pos_sup;
    int max_taille = 700;

    /*Affichage du mot "vitesse"*/
    sprintf(str_nbr, "%f", velocite);
    glColor3f(1, 1, 1);
    for (aff = 0; aff < 9; aff++){
        glRasterPos2f(10 + aff * 10,taille_fenetre - 10);
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str_vitesse[aff]);
    }

    /*Affichage de la vitesse via un nombre*/
    aff = 0;
    while ((bout = str_nbr[aff]) != '\0'){
        glRasterPos2f(10 + aff * 10,taille_fenetre - 20);
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str_nbr[aff]);
        aff++;
    }

    /* Affichage du rectangle de vitesse*/
    glBegin(GL_QUADS);
    
    //pos_sup = velocite*25000;
    if (vitesse == 0){
        pos_sup = 0;
    }
    else{
        pos_sup = (velocite / V_MAX) * max_taille;
    }

    if (pos_sup < 0){
        glColor3f(1, 0, 0);
        glVertex2f(10,10+max_taille);
        glVertex2f(30,10+max_taille);
        glVertex2f(30,10+max_taille+pos_sup);
        glVertex2f(10,10+max_taille+pos_sup);
    }
    else{
        glVertex2f(10,10);
        glVertex2f(30,10);
        glVertex2f(30,10+pos_sup);
        glVertex2f(10,10+pos_sup);
    }

    glColor3f(1, 1, 1);
    glEnd();

    /* Affichage du rectangle de la limite de la vitesse */
    glBegin(GL_LINE_LOOP);
    glVertex2f(10,10);
    glVertex2f(30,10);
    glVertex2f(30,10+max_taille);
    glVertex2f(10,10+max_taille);
    glEnd();
}

void affichage_vie_vaisseau(){
    float pos_sup;
    int max_taille = 700;
    int vie_max = 10*70;

    /* Affichage du rectangle de vie du vaisseau*/
    glBegin(GL_QUADS);
    
    pos_sup = vie_vaisseau*70;

    glColor3f(1, 0, 0);
    glVertex2f(770,10);
    glVertex2f(790,10);
    glVertex2f(790,10+pos_sup);
    glVertex2f(770,10+pos_sup);
    glColor3f(1, 1, 1);
    glEnd();

    /* Affichage du rectangle de la limite de la vitesse */
    glBegin(GL_LINE_LOOP);
    glColor3f(1, 0, 0);
    glVertex2f(770,10);
    glVertex2f(790,10);
    glVertex2f(790,10+vie_max);
    glVertex2f(770,10+vie_max);
    glColor3f(1, 1, 1);
    glEnd();
}

void affichage_vie_carte(){
    float pos_sup;
    int max_taille = 700;
    int vie_max = 100*7;

    /* Affichage du rectangle de vie du vaisseau*/
    glBegin(GL_QUADS);
    
    pos_sup = vie_carte*7;

    glColor3f(1, 0.5, 0.5);
    glVertex2f(750,10);
    glVertex2f(770,10);
    glVertex2f(770,10+pos_sup);
    glVertex2f(750,10+pos_sup);
    glColor3f(1, 1, 1);
    glEnd();

    /* Affichage du rectangle de la limite de la vitesse */
    glBegin(GL_LINE_LOOP);
    glColor3f(1, 0.5, 0.5);
    glVertex2f(750,10);
    glVertex2f(770,10);
    glVertex2f(770,10+vie_max);
    glVertex2f(750,10+vie_max);
    glColor3f(1, 1, 1);
    glEnd();
}

void afficher_axes(){
    glColor3f(1, 0, 0);
    glVertex3f(0,0,0);
    glVertex3f(1000,0,0);

    glColor3f(0, 1, 0);
    glVertex3f(0,0,0);
    glVertex3f(0,1000,0);

    glColor3f(0, 0, 1);
    glVertex3f(0,0,0);
    glVertex3f(0,0,1000);
}

void affichage_sol(){
    float taille = 1000.0f; // moitié de la largeur et longueur du sol
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_sol);
    glBegin(GL_QUADS);

    glColor3f(1,1,1);


    // coin bas gauche
    //glColor3f(0.6f, 0.6f, 0.5f); // sable un peu foncé

    glTexCoord2f(0,0);
    glVertex3f(-taille, -taille, 0.0f);

    // coin bas droit
    glTexCoord2f(10,0);
    glVertex3f(taille, -taille, 0.0f);

    // coin haut droit
    glTexCoord2f(10,10);
    glVertex3f(taille, taille, 0.0f);

    // coin haut gauche
    glTexCoord2f(0,10);
    glVertex3f(-taille, taille, 0.0f);

    glEnd();
    glDisable(GL_TEXTURE_2D);
}
void affichage_etoile(float x, float y, float z, float rayon, float r, float g, float b){
    glPushMatrix();
    glTranslatef(x, y, z);
    glColor3f(r, g, b);
    glutSolidSphere(rayon, 20, 20);
    glPopMatrix();
}

void affichage_ciel(){
    float taille = 500.0f;
    float r_haut = 0.08f, g_haut = 0.08f, b_haut = 0.12f, r_bas = 0.12f, g_bas = 0.12f, b_bas = 0.27f;

    /*Desac la profondeur pour pas clipper avec les autres objets*/
    glDepthMask(GL_FALSE);
    glDisable(GL_DEPTH_TEST);

    /*Positione notre matrice de dessin sur la position*/
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);

    glShadeModel(GL_SMOOTH); /*Ce qui fait notre degradé, GL calcul les colors inter entre face haut/basse*/
    glBegin(GL_QUADS);

    /*Face avant (Y+)*/
    glColor3f(r_bas, g_bas, b_bas);
    glVertex3f(-taille,  taille, -taille);
    glVertex3f( taille,  taille, -taille);
    glColor3f(r_haut, g_haut, b_haut);
    glVertex3f( taille,  taille,  taille);
    glVertex3f(-taille,  taille,  taille);

    /*Face arrière (Y-)*/
    glColor3f(r_bas, g_bas, b_bas);
    glVertex3f( taille, -taille, -taille);
    glVertex3f(-taille, -taille, -taille);
    glColor3f(r_haut, g_haut, b_haut);
    glVertex3f(-taille, -taille,  taille);
    glVertex3f( taille, -taille,  taille);

    /*Face droite (X+)*/
    glColor3f(r_bas, g_bas, b_bas);
    glVertex3f( taille,  taille, -taille);
    glVertex3f( taille, -taille, -taille);
    glColor3f(r_haut, g_haut, b_haut);
    glVertex3f( taille, -taille,  taille);
    glVertex3f( taille,  taille,  taille);

    /*Face gauche (X-)*/
    glColor3f(r_bas, g_bas, b_bas);
    glVertex3f(-taille, -taille, -taille);
    glVertex3f(-taille,  taille, -taille);
    glColor3f(r_haut, g_haut, b_haut);
    glVertex3f(-taille,  taille,  taille);
    glVertex3f(-taille, -taille,  taille);

    /*Dessus (Z+)*/
    glColor3f(r_haut, g_haut, b_haut);
    glVertex3f(-taille,  taille,  taille);
    glVertex3f( taille,  taille,  taille);
    glVertex3f( taille, -taille,  taille);
    glVertex3f(-taille, -taille,  taille);

    glEnd();

    /*TOur soleil blanc*/
    affichage_etoile(300, 300, 250, 30, 1.0f, 0.95f, 0.6f);

    /*centre soleil orangé*/
    affichage_etoile(300, 300, 250, 25, 0.9f, 0.5f, 0.1f);

    /*Planète bleue*/
    affichage_etoile(-350, 200, 150, 18, 0.3f, 0.4f, 0.8f);

    /*Planète rouge*/
    affichage_etoile(100, -400, 100, 12, 0.7f, 0.25f, 0.15f);

    glPopMatrix(); /*Restaure la matrice d'avant*/

    /*Reac la profondeur pour les autres objets*/
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
}

void charger_texture_sol(){
    int width, height, nrChannels;
    /*Gestion de la texture :*/

    unsigned char *data = stbi_load("./img/texture_lune.jpg", &width, &height, &nrChannels, 0);
    glGenTextures(1, &texture_sol);  
    glBindTexture(GL_TEXTURE_2D, texture_sol); 

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (!data){
        printf("Erreur chargement d'image\n"); // Si ça affiche ça, alors l'image est mal chargée
    }
    else{
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    }
    stbi_image_free(data);
}

void Affichage(){
    int nbr, upx, upy, upz;
    int left, right, bottom, top, near, far;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*Gestion de l'invulnérabilité*/
    if (invulnerabilite > 0){
        invulnerabilite--;
    }
    /*Gestion du cooldown*/
    if (cooldown > 0){
        cooldown--;
    }
    
    if ((vie_vaisseau <= 0)||(vie_carte <= 0)){
        /*Interface 2D*/
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0,taille_fenetre,0,taille_fenetre, 0, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        /*Contenu de l'interface 2D*/
        if (vie_vaisseau <= 0){
            affichage_fin(0);
        }
        else{
            affichage_fin(1);
        }
    }
    else{
        /* Interface 3D*/
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        upx = 0;
        upy = 0;
        upz = 1;
        
        left = -5;
        right = 5;
        bottom = -5;
        top = 5;
        near = 5;
        far = 1000;
    
        glFrustum(left, right, bottom, top, near, far);
        gluLookAt(position.x, position.y, position.z, 
            position.x+devant.x, position.y+devant.y, position.z+devant.z,
            haut.x, haut.y, haut.z);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glBegin(GL_QUADS);
        glEnd();
        affichage_ciel();
        affichage_sol();
        afficher_ennemies();
        afficher_projectiles();

        glBegin(GL_LINES);
        /*afficher_axes();*/
        glEnd();
        int i = colision();
        /*Interface 2D*/
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0,taille_fenetre,0,taille_fenetre, 0, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        /*Contenu de l'interface 2D*/
        affichage_vitesse();
        affichage_vie_vaisseau();
        affichage_vie_carte();
        affichage_score();
    }

    
    glutSwapBuffers();
}

void Animer(){
    float rayon = 10;
    /*Gestion des touches*/
    if ((touches[' ']) && (cooldown == 0)){
        tirer_double_projectile(position, devant, droite, haut);
        cooldown = 15;
    }
    /* Avancer, reculer */
    if (touches['z']){
        if(velocite < V_MAX){
            velocite += vitesse;
        }
    }
    if (touches['s']){
        if(velocite > -V_MAX){
            velocite -= vitesse;
        }
    }

    // Rotation sur l'axe Z
    if (touches['q']){
        devant = rodriguez(devant, haut, rota_z);
        droite = rodriguez(droite, haut, rota_z);

        devant = normalisation(devant);
        droite = normalisation(droite);

        printf("Devant : %f, %f, %f", devant.x, devant.y, devant.z);
        printf(" |Droite : %f, %f, %f\n", droite.x, droite.y, droite.z);
    }
    if (touches['d']){
        devant = rodriguez(devant, haut, -rota_z);
        droite = rodriguez(droite, haut, -rota_z);

        devant = normalisation(devant);
        droite = normalisation(droite);

        printf("Devant : %f, %f, %f", devant.x, devant.y, devant.z);
        printf(" |Droite : %f, %f, %f\n", droite.x, droite.y, droite.z);
    }

    // Rotation sur l'axe Y
    if (touches['a']){
        devant = rodriguez(devant, droite, -rota_z);
        haut = rodriguez(haut, droite, -rota_z);

        devant = normalisation(devant);
        haut = normalisation(haut);

        printf("Devant : %f, %f, %f", devant.x, devant.y, devant.z);
        printf(" |Haut : %f, %f, %f\n", haut.x, haut.y, haut.z);
    }
    if (touches['e']){
        devant = rodriguez(devant, droite, rota_z);
        haut = rodriguez(haut, droite, rota_z);

        devant = normalisation(devant);
        haut = normalisation(haut);

        printf("Devant : %f, %f, %f", devant.x, devant.y, devant.z);
        printf(" |Haut : %f, %f, %f\n", haut.x, haut.y, haut.z);
    }

    // Rotation sur l'axe X
    if (touches['w']){
        haut = rodriguez(haut, devant, rota_z);
        droite = rodriguez(droite, devant, rota_z);

        haut = normalisation(haut);
        droite = normalisation(droite);

        printf("Haut : %f, %f, %f", haut.x, haut.y, haut.z);
        printf(" |Droite : %f, %f, %f\n", droite.x, droite.y, droite.z);
    }
    if (touches['c']){
        haut = rodriguez(haut, devant, -rota_z);
        droite = rodriguez(droite, devant, -rota_z);

        haut = normalisation(haut);
        droite = normalisation(droite);

        printf("Haut : %f, %f, %f", haut.x, haut.y, haut.z);
        printf(" |Droite : %f, %f, %f\n", droite.x, droite.y, droite.z);
    }

    position = addition(position, produit(devant, velocite));
    update_ennemies(devant, position);
    update_projectiles();
    glutPostRedisplay();
}

void GererClavier(unsigned char touche, int x, int y){
    printf(" Touche: %c Souris : %d %d \n",touche,x,y);
}

void keyDown(unsigned char key, int x, int y){
    touches[key] = 1;
}

void keyUp(unsigned char key, int x, int y){
    touches[key] = 0;
}

int main(int argc, char* argv[]){
    init_liste_projectile();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(taille_fenetre, taille_fenetre);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Une fenetre OpenGL");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(Affichage);
    glutIdleFunc(Animer);
    //glutKeyboardFunc(GererClavier);
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
    charger_texture_sol();
    glutMainLoop();
    return 0;
}