#include "joueur.h"

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