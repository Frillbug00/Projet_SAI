#include "joueur.h"

/*--------------OBSOLETE------------------*/
vecteur rota_autour_Z(vecteur v, float angle){
    vecteur res;
    res.x = v.x * cos(angle) - v.y * sin(angle);
    res.y = v.x * sin(angle) + v.y * cos(angle);
    res.z = v.z;
    return res;
}

vecteur rota_autour_Y(vecteur v, float angle){
    vecteur res;
    res.y = v.y;
    res.z = v.x * sin(angle) + v.z * cos(angle);
    res.x = v.x * cos(angle) - v.z * sin(angle);
    return res;
}

vecteur rota_autour_X(vecteur v, float angle){
    vecteur res;
    res.y = v.y * cos(angle) - v.z * sin(angle);
    res.z = v.y * sin(angle) + v.z * cos(angle);
    res.x = v.x;
    return res;
}
/*--------------OBSOLETE------------------*/

vecteur rodriguez(vecteur vect, vecteur axe, float angle){
    // A voir si la normalisation change quelque chose ???
    axe = normalisation(axe);

    vecteur res;
    res = produit(vect, cos(angle));
    res = addition(res, produit(produit_vectoriel(axe, vect), sin(angle)));
    res = addition(res, produit(produit(axe, produit_scalaire(axe, vect)), 1-cos(angle)));

    return res;
}