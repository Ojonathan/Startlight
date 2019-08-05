#ifndef OBJECTSTAR_H
#define OBJECTSTAR_H

#include "point.h"
#include "ray.h"

#include <iostream>
#include <string>
using namespace std;

class objectStar{
private:
    string name;
    static int counter;
    int index;
public:
    objectStar();
    objectStar(string Onename);

    /**
     * strike permet recevoir un rayon et le modifie selon le type d'objet
     * @param ray un rayon a modifer par l'objet
     * @param p le point trouve pour donner fin au rayon
     * @return un nouveau rayon si l'object autorise
     */
    virtual Ray * strike(Ray *& ray,Point p);

    /**
     * Retourne le nom de de l'object un façon de savoir le libellé
     * @return le nom de l'objet
     */
    string getName();

    /**
     * Retourne l'index d'un objet creé
     * @return l'index de l'objet
     */
    int getIndex();

};

#endif // OBJECTSTAR_H
