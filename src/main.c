#include "stdio.h"
#include "stdlib.h"
#include "GL/gl.h"
#include "GL/glut.h"
#include "math.h"

int taille_fenetre = 800;
float t = 0;
float deg = 0.1;
int eyex = 1;
int eyey = 0;
int eyez = 10;

float centerx = 10;
float centery = 5;
float centerz = 10;

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
    glColor3f(0.9, 0.9, 0.9);
    glVertex3f(10000, 10000, 0);
    glVertex3f(-10000, 10000, 0);
    glVertex3f(-10000, -10000, 0);
    glVertex3f(10000, -10000, 0);
}

void Affichage(){
    int nbr, upx, upy, upz;
    int left, right, bottom, top, near, far;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
    gluLookAt(eyex, eyey, eyez, eyex+10, eyey+5, eyez+10, upx, upy, upz);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glBegin(GL_QUADS);
    afficherCube(20,20,20,30,30,30);
    //affichage_sol();
    glEnd();
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0,0,0);
    glVertex3f(1000,0,0);

    glColor3f(0, 1, 0);
    glVertex3f(0,0,0);
    glVertex3f(0,1000,0);

    glColor3f(0, 0, 1);
    glVertex3f(0,0,0);
    glVertex3f(0,0,1000);
    glEnd();
    glutSwapBuffers();
}

void Animer(){
    glutPostRedisplay();
}

void GererClavier(unsigned char touche, int x, int y){
    float rayon = 10;
    printf(" Touche: %c Souris : %d %d \n",touche,x,y);

    /* Avancer, reculer*/
    if (touche == 'z'){
        eyex += 1;
        eyey += 1;
    }
    if (touche == 's'){
        eyex -= 1;
        eyey -= 1;
    }

    /* Gauche, droite*/
    if (touche == 'q'){
        t += deg;
        centerx = rayon * cos(t);
        centery = rayon * sin(t);
    }
    if (touche == 'd'){
        t -= deg;
        centerx = rayon * cos(t);
        centery = rayon * sin(t);
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