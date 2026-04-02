#include "stdio.h"
#include "stdlib.h"
#include "GL/gl.h"
#include "GL/glut.h"
#include "math.h"
#include "vecteur.h"
#include "joueur.h"
#include "ennemies.h"
#define NEAR 5
int taille_fenetre = 800;
float taille_joueur = 1;
float rota_z = 0.1; // Rotation autour de z

/*Représentation joueur*/
float velocite = 0;
float vitesse = 0.0001;
vecteur position = {-20,-20,10};
vecteur devant = {1,0,0};
vecteur haut = {0,0,1};
vecteur droite = {0,1,0};
/*---------------------------*/

int colision(){
    if (position.z <=0+NEAR){
        printf("COLISION : Sous la map\n");
    }
    for(int i=0;i<nb_ennemies;i++){
        vecteur le_pos = l_e[i].position;
        float d_centre = pow((le_pos.x-position.x), 2)+pow((le_pos.y-position.y), 2)+pow((le_pos.z-position.z), 2);
        float d_rayons = pow(taille_joueur, 2)+pow(RAYON, 2);
        if(d_rayons+5>d_centre){
            printf("COLISION : Asteroide\n");
        }
    }
}
void affichage_vitesse(){
    char* str_vitesse = "vitesse :";
    int aff = 0;
    char str_nbr[10];
    char bout;
    float pos_sup;

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
    
    pos_sup = velocite*25000;

    glVertex2f(10,10);
    glVertex2f(30,10);
    glVertex2f(30,10+pos_sup);
    glVertex2f(10,10+pos_sup);

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

void afficherCube(int xmin, int ymin, int zmin, int xmax, int ymax, int zmax){

    // face basse
    glColor3f(1, 0, 0);
    glVertex3f(xmin, ymin, zmin);
    glVertex3f(xmin, ymax, zmin);
    glVertex3f(xmax, ymax, zmin);
    glVertex3f(xmax, ymin, zmin);

    //face avant
    glColor3f(0, 1, 0);
    glVertex3f(xmin, ymin, zmin);
    glVertex3f(xmin, ymin, zmax);
    glVertex3f(xmax, ymin, zmax);
    glVertex3f(xmax, ymin, zmin);

    //face gauche
    glColor3f(0, 0, 1);
    glVertex3f(xmin, ymin, zmin);
    glVertex3f(xmin, ymax, zmin);
    glVertex3f(xmin, ymax, zmax);
    glVertex3f(xmin, ymin, zmax);

    //face droite
    glColor3f(1, 1, 0);
    glVertex3f(xmax, ymin, zmin);
    glVertex3f(xmax, ymax, zmin);
    glVertex3f(xmax, ymax, zmax);
    glVertex3f(xmax, ymin, zmax);

    //face arrière
    glColor3f(0, 1, 1);
    glVertex3f(xmin, ymax, zmin);
    glVertex3f(xmax, ymax, zmin);
    glVertex3f(xmax, ymax, zmax);
    glVertex3f(xmin, ymax, zmax);

    //face dessus
    glColor3f(1, 0, 1);
    glVertex3f(xmin, ymin, zmax);
    glVertex3f(xmax, ymin, zmax);
    glVertex3f(xmax, ymax, zmax);
    glVertex3f(xmin, ymax, zmax);
}

void affichage_sol(){
    float taille = 1000.0f; // moitié de la largeur et longueur du sol

    glBegin(GL_QUADS);

    // coin bas gauche
    glColor3f(0.6f, 0.6f, 0.5f); // sable un peu foncé
    glVertex3f(-taille, -taille, 0.0f);

    // coin bas droit
    glVertex3f(taille, -taille, 0.0f);

    // coin haut droit
    glVertex3f(taille, taille, 0.0f);

    // coin haut gauche
    glVertex3f(-taille, taille, 0.0f);

    glEnd();
}

void Affichage(){
    int nbr, upx, upy, upz;
    int left, right, bottom, top, near, far;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
    afficherCube(20,20,20,30,30,30);
    affichage_sol();
    glEnd();
    afficher_ennemies();

    glBegin(GL_LINES);
    afficher_axes();
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

    glutSwapBuffers();
}

void Animer(){
    position = addition(position, produit(devant, velocite));
    update_ennemies(devant, position);

    glutPostRedisplay();
}

void GererClavier(unsigned char touche, int x, int y){
    float rayon = 10;
    printf(" Touche: %c Souris : %d %d \n",touche,x,y);

    
    /* Avancer, reculer */
    if (touche == 'z'){
        //position = addition(position, devant);
        velocite += vitesse;
    }
    if (touche == 's'){
        //position = soustraction(position, devant);
        velocite -= vitesse;
    }

    /* Version 1 :
    // Gauche, droite 
    if (touche == 'q'){
        devant = rota_autour_Z(devant, rota_z);
        droite = rota_autour_Z(droite, rota_z);

        devant = normalisation(devant);
        droite = normalisation(droite);

        printf("Devant : %f, %f, %f", devant.x, devant.y, devant.z);
        printf(" |Droite : %f, %f, %f\n", droite.x, droite.y, droite.z);
    }
    if (touche == 'd'){
        devant = rota_autour_Z(devant, -rota_z);
        droite = rota_autour_Z(droite, -rota_z);

        devant = normalisation(devant);
        droite = normalisation(droite);

        printf("Devant : %f, %f, %f", devant.x, devant.y, devant.z);
        printf(" |Droite : %f, %f, %f\n", droite.x, droite.y, droite.z);
    }

    if (touche == 'a'){
        devant = rota_autour_Y(devant, rota_z);
        haut = rota_autour_Y(haut, rota_z);

        devant = normalisation(devant);
        haut = normalisation(haut);

        printf("Devant : %f, %f, %f", devant.x, devant.y, devant.z);
        printf(" |Haut : %f, %f, %f\n", haut.x, haut.y, haut.z);
    }

    if (touche == 'e'){
        haut = rota_autour_X(haut, rota_z);
        droite = rota_autour_X(droite, rota_z);

        haut = normalisation(haut);
        droite = normalisation(droite);

        printf("Haut : %f, %f, %f", haut.x, haut.y, haut.z);
        printf(" |Droite : %f, %f, %f\n", droite.x, droite.y, droite.z);
    }

    /*Version 2*/

    // Rotation sur l'axe Z
    if (touche == 'q'){
        devant = rodriguez(devant, haut, rota_z);
        droite = rodriguez(droite, haut, rota_z);

        devant = normalisation(devant);
        droite = normalisation(droite);

        printf("Devant : %f, %f, %f", devant.x, devant.y, devant.z);
        printf(" |Droite : %f, %f, %f\n", droite.x, droite.y, droite.z);
    }
    if (touche == 'd'){
        devant = rodriguez(devant, haut, -rota_z);
        droite = rodriguez(droite, haut, -rota_z);

        devant = normalisation(devant);
        droite = normalisation(droite);

        printf("Devant : %f, %f, %f", devant.x, devant.y, devant.z);
        printf(" |Droite : %f, %f, %f\n", droite.x, droite.y, droite.z);
    }

    // Rotation sur l'axe Y
    if (touche == 'a'){
        devant = rodriguez(devant, droite, -rota_z);
        haut = rodriguez(haut, droite, -rota_z);

        devant = normalisation(devant);
        haut = normalisation(haut);

        printf("Devant : %f, %f, %f", devant.x, devant.y, devant.z);
        printf(" |Haut : %f, %f, %f\n", haut.x, haut.y, haut.z);
    }
    if (touche == 'e'){
        devant = rodriguez(devant, droite, rota_z);
        haut = rodriguez(haut, droite, rota_z);

        devant = normalisation(devant);
        haut = normalisation(haut);

        printf("Devant : %f, %f, %f", devant.x, devant.y, devant.z);
        printf(" |Haut : %f, %f, %f\n", haut.x, haut.y, haut.z);
    }

    // Rotation sur l'axe X
    if (touche == 'w'){
        haut = rodriguez(haut, devant, rota_z);
        droite = rodriguez(droite, devant, rota_z);

        haut = normalisation(haut);
        droite = normalisation(droite);

        printf("Haut : %f, %f, %f", haut.x, haut.y, haut.z);
        printf(" |Droite : %f, %f, %f\n", droite.x, droite.y, droite.z);
    }
    if (touche == 'c'){
        haut = rodriguez(haut, devant, -rota_z);
        droite = rodriguez(droite, devant, -rota_z);

        haut = normalisation(haut);
        droite = normalisation(droite);

        printf("Haut : %f, %f, %f", haut.x, haut.y, haut.z);
        printf(" |Droite : %f, %f, %f\n", droite.x, droite.y, droite.z);
    }
}

int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(taille_fenetre, taille_fenetre);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Une fenetre OpenGL");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(Affichage);
    glutIdleFunc(Animer);
    glutKeyboardFunc(GererClavier);
    glutMainLoop();
    return 0;
}