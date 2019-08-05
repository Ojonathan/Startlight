#ifndef NUKE_H
#define NUKE_H

#include "point.h"
#include "objectStar.h"

#include <ostream>
#include <QGraphicsEllipseItem>
#include <QPainter>

/**
 * Cette classe modélise les bombes utilisées dans le jeu.
 * </p>
 * Une bomnbe est un objet circulaire qui, si illuminé par
 * un rayon, fait perdre la partie au joueur.
 */
class Nuke : public objectStar, public QGraphicsEllipseItem
{
    Point pos;
    int rad;
    bool light {false};

  public:
    /**
     * Instancie une bombe en une position donnée avec un rayon
     * déterminé.
     * @param p la position de la bombe
     * @param r le rayon de la bombe
     */
    Nuke(const Point & p, int r);

    /**
     * Retourne la position de la bombe.
     * @return la position de la bombe.
     */
    const Point & getLocation() const;

    /**
     * Retourne le rayon de la bombe.
     * @return le rayon de la bombe.
     */
    int getRadius() const;

    /**
     * Retourne vrai si la bombe est illuminée, faux sinon.
     * @return vrai si la bombe est illuminée, faux sinon.
     */
    bool isLightedUp() const;

    /**
     * Illumine la bombe ou non.
     * @param q vrai si la bombe est illuminée, faux sinon.
     */
    void setLightedUp(bool q);

    /**
     * reemplementation de la méthode strike
     * @param ray un rayon a modifer par l'objet
     * @param p le point trouve pour donner fin au rayon
     * @return un nouveau rayon si l'object autorise
     */
    Ray * strike(Ray *& ray, Point p);

    /**
     * reemplementaion de la méthode paint.
     * @param painter
     * @param option
     * @param widget
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    /**
     * Surcharge l'opérateur de flux de sortie pour afficher un
     * récapitulatif des caractéristiques de la bombe
     * sous-jacente en console.
     * @return le flux dans lequel la bombe a été imprimée.
     */
    friend std::ostream & operator<<(std::ostream & out,
                                     const Nuke & s);
};

#endif // NUKE_H
