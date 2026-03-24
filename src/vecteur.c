#include "vecteur.h"

vecteur addition(vecteur vect1, vecteur vect2){
    vecteur res = {vect1.x + vect2.x, vect1.y + vect2.y, vect1.z + vect2.z};
    return res;
}

vecteur soustraction(vecteur vect1, vecteur vect2){
    vecteur res = {vect1.x - vect2.x, vect1.y - vect2.y, vect1.z - vect2.z};
    return res;
}

vecteur produit(vecteur vect1, float f){
    vecteur res = {vect1.x *f, vect1.y *f, vect1.z *f};
    return res;
}

float produit_scalaire(vecteur vect1, vecteur vect2){
    return vect1.x * vect2.x + vect1.y * vect2.y + vect1.z * vect2.z;
}

vecteur produit_vectoriel(vecteur vect1, vecteur vect2){
    vecteur res;
    res.x = vect1.y*vect2.z - vect1.z*vect2.y;
    res.y = vect1.z*vect2.x - vect1.x*vect2.z;
    res.z = vect1.x*vect2.y - vect1.y*vect2.x;

    return res;
}

vecteur normalisation(vecteur vect){
    float norme = sqrt(vect.x * vect.x + vect.y * vect.y + vect.z * vect.z);

    if (norme == 0){
        vecteur res = {0,0,0};
        return res;
    }
    vecteur res = {vect.x / norme, vect.y / norme, vect.z / norme};
    return res;
}