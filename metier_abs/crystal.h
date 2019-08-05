#ifndef CRYSTAL_H
#define CRYSTAL_H

#include "point.h"
#include "objectStar.h"

#include <ostream>
#include <QGraphicsEllipseItem>
#include <QPainter>

/**
 * Cette classe modélise les cristaux utilisés dans le jeu.
 * </p>
 * Un cristal est un objet circulaire centré en un point, et
 * d'un certain rayon.
 * </p>
 * Un rayon lumineux passant à travers un crystal modifie sa
 * longueur d'onde (en l'augmentant ou en la diminuant d'une
 * certaine valeur) mais pas sa trajectoire.
 */
class Crystal: public objectStar, public QGraphicsEllipseItem
{
    Point center;
    double rad;
    int mod;
    Point p2circle;

  public:
    /**
     * Instancie un cristal centré au point donné, d'un certain
     * rayon et modifiant la longueur d'onde des rayons qui le
     * traversent d'une valeur donnée.
     * @param p le centre du cristal
     * @param r le rayon du cristal
     * @param m le modificateur de longueur d'onde du cristal
     */
    Crystal(const Point & p, double r, int m);

    /**
     * Retourne la coordonée du centre du cristal
     * @return  la coordonée du centre du cristal
     */
    const Point & getCenter() const;

    /**
     * Retourne le modificateur de longueur d'onde du cristal
     * @return  le modificateur de longueur d'onde du cristal
     */
    int getModifier() const;

    /**
     * Retourne le rayon du cristal
     * @return le rayon du cristal
     */
    double getRadius() const;

    /**
     * reemplementation de la méthode strike
     * @param ray un rayon a modifer par l'objet
     * @param p le point trouve pour donner fin au rayon
     * @return un nouveau rayon si l'object autorise
     */
    Ray * strike(Ray *& ray, Point p);

    /**
     * modifie le deuxieme point d'intersection
     * @param value la nouvelle valeur à modifier.
     */
    void setP2circle(const Point value);

    /**
     * reemplementaion de la méthode paint.
     * @param painter
     * @param option
     * @param widget
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    /**
     * Surcharge l'opérateur de flux de sortie pour afficher
     * un récapitulatif des caractéristiques du cristal
     * sous-jacent en console.
     * @return le flux dans lequel le cristal à été imprimé.
     */
    friend std::ostream & operator<<(std::ostream &,
                                     const Crystal &);

};

#endif // CRYSTAL_H
