#ifndef LENS_H
#define LENS_H

#include "point.h"
#include "objectStar.h"

#include <ostream>
#include <QGraphicsEllipseItem>
#include <QPainter>


/**
 * Cette classe modélise les lentilles utilisées dans le jeu.
 * </p>
 * Une lentille est un objet rectangulaire qui ne laisse passer
 * les rayons lumineux que dans un certain intervalle de longueur
 * d'onde. Si un rayon lumineux se trouve dans l'intervalle de
 * longueur d'onde autorisé, il traverse la lentille sans subir
 * aucune modification. Sinon, la lentille se comporte comme un
 * mur.
 */
class Lens: public objectStar, public QGraphicsEllipseItem
{
    Point pos;

    int width;
    int height;

    int wlmin;
    int wlmax;

    Point p2ellipse;

  public:
    /**
     * Instancie une lentille à l'aide de toutes ses
     * caractéristiques.
     * @param p la position du coin supérieur gauche du
     *          rectangle modélisant la lentille.
     * @param w la largeur de la lentille
     * @param h la hauteur de la lentille
     * @param wlmin la longueur d'onde minimale des rayons
     *              autorisés à franchir la lentille
     * @param wlmax la longueur d'onde maximale des rayons
     *              autorisés à franchir la lentille
     */
    Lens(const Point & p, int w, int h, int min, int max);

    /**
     * Retourne la position du coin supérieur gauche du
     * rectangle modélisant la lentille.
     * @return la position du coin supérieur gauche du
     * rectangle modélisant la lentille.
     */
    const Point & getPosition() const;

    /**
     * Retourne la largeur de la lentille
     * @return la largeur de la lentille
     */
    int getWidth() const;

    /**
     * Retourne la hauteur de la lentille
     * @return la hauteur de la lentille
     */
    int getHeight() const;

    /**
     * Retourne la longueur d'onde minimale des rayons
     * autorisés à franchir la lentille
     * @return la longueur d'onde minimale des rayons
     * autorisés à franchir la lentille
     */
    int getMinWavelength() const;

    /**
     * Retourne la longueur d'onde maximale des rayons
     * autorisés à franchir la lentille
     * @return la longueur d'onde maximale des rayons
     * autorisés à franchir la lentille
     */
    int getMaxWavelength() const;

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
    void setP2ellipse(const Point value);

    /**
     * reemplementaion de la méthode paint.
     * @param painter
     * @param option
     * @param widget
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    /**
     * Surcharge l'opérateur de flux de sortie pour afficher
     * un récapitulatif des caractéristiques de la lentille
     * sous-jacente en console.
     * @return le flux dans lequel la lentille a été imprimée.
     */
    friend std::ostream & operator<<(std::ostream & out,
                                     const Lens & m);
};

#endif // LENS_H
