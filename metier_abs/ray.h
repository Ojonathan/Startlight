#ifndef RAY_H
#define RAY_H

#include "point.h"

#include <iostream>
#include <QGraphicsLineItem>
#include <Qpainter>
#include <QColor>

/**
 * Cette classe modélise les rayons lumineux, concept central du jeu.
 * </p>
 * Un rayon lumineux est un segment de droite muni d'une longueur
 * d'onde.
 */
class Ray: public QGraphicsLineItem
{

    Point start;
    Point end;
    int wavelength;
    int lastwl;
    double angle;
    QColor colorRay;

  public:
    /**
     * Longueur d'onde minimum autorisée pour un rayon lumineux. Cette
     * valeur correspond à la longueur d'onde minimum (en nm) du
     * spectre visible de la lumière.
     */
    static const int WL_MIN {360};

    /**
     * Longueur d'onde maximum autorisée pour un rayon lumineux. Cette
     * valeur correspond à la longueur d'onde maximum (en nm) du
     * spectre visible de la lumière.
     */
    static const int WL_MAX {830};

    /**
     * Longueur d'onde par défaut pour un rayon lumineux. Cette
     * valeur correspond à la longueur d'onde (en nm) de la couleur
     * orangé-rouge du spectre visible de la lumière.
     */
    static const int WL_DFT {600};

    /**
     * Instancie un rayon lumineux de début et de fin donnés, et de
     * longueur d'onde spécifiée.
     * </p>
     * @param p1 le début du rayon lumineux
     * @param newangle la longueur d'onde du rayon.
     * @param wl la longueur d'onde du rayon lumineux.
     */
    Ray(const Point & p1, double newangle ,int wl);

    /**
     * Instancie un rayon lumineux de début et de fin donnés, et de
     * longueur d'onde spécifiée.
     * </p>
     * @param a le début du rayon lumineux
     * @param b la fin du rayon lumineux
     * @param wl la longueur d'onde du rayon lumineux.
     * @see Ray::WL_MIN
     * @see Ray::WL_MAX
     * @see Ray::WL_DFT
     */
    Ray(const Point & p1, const Point & p2, int wl);

    /**
     * Retourne le début du rayon.
     * @return le début du rayon.
     */
    const Point & getStart() const;

    /**
     * Retourne la fin du rayon.
     * @return la fin du rayon.
     */
    const Point & getEnd() const;

    /**
     * Retourne la longueur d'onde du rayon.
     * @return la longueur d'onde du rayon.
     */
    int getWavelength() const;

    /**
     * Change la coordonée du début du rayon.
     * @param p la nouvelle coordonée du début du rayon.
     */
    void setStart(const Point & p);

    /**
     * Change la coordonée de la fin du rayon.
     * @param p la nouvelle coordonée de la fin du rayon.
     */
    void setEnd(const Point & p);

    /**
     * Change la longueur d'onde du rayon. Si la longueur d'onde
     * spécifiée est en dehors des limites autorisées, laisse la
     * longueur d'onde inchangée.
     * </p> La longueur d'onde doit être comprise entre 360 et 830 nm.
     * @param f la nouvelle longueur d'onde du rayon
     * @return vrai si la longueur d'onde a bel et bien été changée,
     * retourne faux sinon.
     */
    bool setWavelength(int wl);

    /**
     * Retourne l'angle du rayon
     * @return l'angle du rayon
     */
    double getAngle() const;

    /**
     * Change l'angle du rayon.
     * @param value le nouveau angle du rayon.
     */
    void setAngle(double value);

    /**
     * reemplementaion de la méthode paint.
     * @param painter
     * @param option
     * @param widget
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    /**
     * permet calculer une couleur pour donner une representation selon la longeur d'onde
     * @brief color pour le rayon
     * @param wl la longeur d'onde du rayon
     * @return une couleur, cette couleur est en format RGB.
     */
    QColor color(int wl);

    /**
     * Surcharge l'opérateur de flux de sortie pour afficher un
     * récapitulatif des caractéristiques du rayon sous-jacent en
     * console.
     * @return le flux dans lequel le rayon a été imprimé.
     */
    friend std::ostream & operator<<(std::ostream & out, const Ray & p);

};

#endif // RAY_H
