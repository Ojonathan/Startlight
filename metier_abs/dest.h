#ifndef DEST_H
#define DEST_H

#include "point.h"
#include "objectStar.h"

#include <ostream>
#include <QGraphicsRectItem>

/**
 * Cette classe modélise la destination utilisée dans le jeu.
 * </p>
 * Une destination est un objet carré qui, quand traversé par
 * un rayon limuneux, fait remporter la partie au joueur.
 */
class Dest : public objectStar, public QGraphicsRectItem
{
    Point pos;
    int edge;
    bool light {false};

  public:
    /**
     * Intancie une destination, de position et rayon donné.
     * @param p le coin supérieur gauche du carré modélisant
     *        la destination.
     * @param e la longueur du côté du carré.
     */
    Dest(const Point & p, int e);

    /**
     * Retourne la position du coin supérieur gauche du carré
     * modélisant la destination.
     * @return la position de la destination.
     */
    const Point & getPosition() const;

    /**
     * Retourne la longueur du côté du carré.
     * @return la longueur du côté du carré.
     */
    int getEdge() const;

    /**
     * Retourne vrai si la destination est illuminée,
     * faux sinon.
     * @return vrai si la destination est illuminée,
     * faux sinon.
     */
    bool isLightedUp() const;

    /**
     * Illumine la destination ou non.
     * @param vrai si la destination doit être illuminée,
     * faux sinon.
     */
    void setLightedUp(const bool q);

    /**
     * reemplementation de la méthode strike
     * @param ray un rayon a modifer par l'objet
     * @param p le point trouve pour donner fin au rayon
     * @return un nouveau rayon si l'object autorise
     */
    Ray * strike(Ray *& ray, Point p);

    /**
     * Surcharge l'opérateur de flux de sortie pour afficher
     * un récapitulatif des caractéristiques de la destination
     * sous-jacente en console.
     * @return le flux dans lequel la destination a été imprimée.
     */
    friend std::ostream & operator<<(std::ostream & out,
                                     const Dest & s);
};

#endif // DEST_H
