#ifndef SOURCE_H
#define SOURCE_H

#include "point.h"
#include "ray.h"

#include <iostream>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
/**
 * Modélise la source lumineuse utilisée dans le jeu.
 * </p>
 * La source est un objet carré qui, si allumée, emet un rayon
 * lumineux de longueur d'onde donnée dont l'angle ne peut pas
 * être changé.
 * </p>
 * Le rayon lumineux est émis depuis la position, i.e., le coin
 * supérieur gauche, de la source.
 */
class Source :public QObject, public QGraphicsRectItem
{
    Q_OBJECT

private:
    bool on {false};
    Point pos;
    double alpha;
    int edge;
    int wavelength;

  public:
    /**
     * Instance une nouvelle source de position, de côté et de
     * longueur d'onde donnée.
     * </p>
     * La position dénote la coordonée du coin supérieur gauche
     * du carré modélisant la source.
     * </p>
     * La source est intialement éteinte.
     * </p> Si la longueur d'onde du rayon lumineux émis n'est
     * pas comprise entre 360 nm et 830 nm, elle est réglée
     * sur 600 nm.
     * @param p la position de la source.
     * @param e la longueur du côté de la source.
     * @param wl la longueur d'onde du rayon lumineux émis.
     * @see Ray::WL_MIN
     * @see Ray::WL_MAX
     * @see Ray::WL_DFT
     */
    Source(const Point & p, int e, double a, int wl);

    /**
     * Retourne la coordonée du coin supérieur gauche du carré
     * modélisant la destination.
     * @return la coordonée du coin supérieur gauche du carré
     * modélisant la destination.
     */
    const Point & getPosition() const;

    /**
     * Retourne l'anle du rayon émis.
     * @return l'anle du rayon émis.
     */
    double getAngle() const;

    /**
     * Retourne la longueur du côté du carré.
     * @return la longueur du côté du carré.
     */
    int getEdge() const;

    /**
     * Retourne la longueur d'onde du rayon émis.
     * @return la longueur d'onde du rayon émis.
     */
    int getWavelength() const;

    /**
     * Retourne vrai si la source émet un rayon lumineux,
     * faux sinon.
     * @return vrai si la source émet un rayon lumineux,
     * faux sinon.
     */
    bool isOn() const;

    /**
     * Allume ou éteint la source.
     * @param q vrai si la source doit être allumée,
     * faux sinon.
     */
    void setOn(bool q);

    /**
     * reemplementation de la méthode mousePressEvent();
     * @param event
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    /**
     * Surcharge l'opérateur de flux de sortie pour afficher
     * un récapitulatif des caractéristiques de la source
     * sous-jacente en console.
     * @return le flux dans lequel la source a été imprimée.
     */
    friend std::ostream & operator<<(std::ostream & out,
                                     const Source & s);
signals:

    //pour indiquer que la source emet.
    void mesOn();
};

#endif // SOURCE_H
