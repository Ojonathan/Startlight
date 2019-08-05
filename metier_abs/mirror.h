#ifndef MIRROR_H
#define MIRROR_H

#include "point.h"
#include "objectStar.h"
#include "ray.h"

#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>
#include <iostream>
#include <QPainter>

/**
 * Cette classe modélise les miroirs utilisés dans le jeu.
 * </p>
 * Un miroir est un segment de droite dont la propriété est
 * de réfléchir la lumière d'un seul côté uniquement. Si un
 * rayon lumineux touche un miroir du côté non réfléchissant,
 * le miroir se comporte comme un mur.
 * </p>
 * Les miroirs sont capables d'être déplacés et pivotés dans
 *  une certaine limite.
 */
class Mirror:public QObject, public QGraphicsLineItem, public objectStar
{
    Q_OBJECT
private:
    Point pivot;
    int length;
    int xpad;
    int xMin {0};
    int xMax {0};
    int yMin {0};
    int yMax {0};
    double alpha;
    double alphaMin {0};
    double alphaMax {0};

    Point start;
    Point end;

    //utisées pour verifier le click.
    bool m_left;
    bool m_right;

public:

    /**
     * Instancie un miroir en une position donnée, d'une certaine
     * longueur et orienté d'un certain angle.
     * </p>
     * Ce constructeur permet également aux miroirs de pivoter
     * dans une certaine limite.
     * </p>
     * Si l'intervalle de limite de déplacement (e.g., sur les
     * abscisses) [a,b] est tel que a = b, le miroir ne peut
     * être déplacé sur l'axe considéré.
     * </p>
     * Si l'intervalle de limite d'inclinaison [a,b] est tel que
     * a < b, le miroir pivote dans le sens horloger, si a = b le
     * miroir ne peut pas pivoter, si a > b, le miroir
     * pivote dans le sens anti-horloger.
     * @param p la position (et le point de pivot) du miroir
     * @param len la longueur du miroir
     * @param x le décallage du pivot par rapport au bord gauche
     *          du miroir
     * @param a l'angle d'inclinaison du miroir
     * @param min l'abscisse et l'ordonnée minimum du miroir.
     * @param max l'abscisse et l'ordonnée maximum du miroir.
     * @param amin l'angle d'inclinaison minimum du miroir.
     * @param amax l'angle d'inclinaison maximum du miroir.
     */
    Mirror(const Point & p, int len, int x, double a, Point min,
           Point max, double amin, double amax);

    /**
     * Retourne la position (et le pivot) du miroir.
     * @return la position (et le pivot) du miroir.
     */
    const Point & getPivot() const;

    /**
     * Retourne la longueur du miroir
     * @return la longueur du miroir
     */
    int getLength() const;

    /**
     * Retourne le décallage du pivot par rapport au bord gauche
     * du miroir.
     * @return le décallage du pivot par rapport au bord gauche
     * du miroir.
     */
    int getXPad() const;

    /**
     * Retourne l'inclinaison du miroir.
     * @return l'inclinaison du miroir.
     */
    double getAngle() const;

    /**
     * Retourne l'inclinaison minimum du miroir.
     * </p>
     * Si l'intervalle de limite d'inclinaison [a,b] est tel que
     * a < b, le miroir pivote dans le sens horloger, si a = b
     * le miroir ne peut pas pivoter, si a > b, le miroir pivote
     * dans le sens anti-horloger. Si a = b = 0, le miroir peut
     * être pivoté librement.
     * @return l'inclinaison minimum du miroir.
     */
    double getMinAngle() const;

    /**
     * Retourne l'inclinaison maximum du miroir.
     * </p>
     * Si l'intervalle de limite d'inclinaison [a,b] est tel
     * que a < b, le miroir pivote dans le sens horloger, si
     * a = b le miroir ne peut pas pivoter, si a > b, le miroir
     * pivote dans le sens anti-horloger. Si a = b = 0, le miroir
     * peut être pivoté librement.
     * @return l'inclinaison minimum du miroir.
     */
    double getMaxAngle() const;

    /**
     * Retourne la position minimum du miroir.
     * </p>
     * Si l'intervalle de limite de déplacement (e.g., sur les
     * abscisses) [a,b] est tel que a = b, le miroir ne peut
     * être déplacé sur l'axe considéré. Si a = b = 0, le miroir
     * peut être déplacé librement.
     * @return la position minimum du miroir.
     */
    Point getMinPivot() const;

    /**
     * Retourne la position maximum du miroir.
     * </p>
     * Si l'intervalle de limite de déplacement (e.g., sur les
     * abscisses) [a,b] est tel que a = b, le miroir ne peut
     * être déplacé sur l'axe considéré. Si a = b = 0, le miroir
     * peut être déplacé librement.
     * @return la position minimum du miroir.
     */
    Point getMaxPivot() const;

    /**
     * Déplace le miroir en la position donnée, si c'est
     * autorisé. Retourne vrai si le déplacement a été
     * effectué correctement, retourne faux sinon.
     * @return vrai si le déplacement a été effectué
     * correctement, retourne faux sinon.
     * @see Mirror::getPivot()
     */
    bool setPivot(const Point &);

    /**
     * Pivote le miroir sur un angle donné, si c'est
     * autorisé. Retourne vrai si la rotation a été effectuée
     * correctement, retourne faux sinon.
     * @return vrai si la rotation a été effectuée
     * correctement, retourne faux sinon.
     * @see Mirror::getAngle()
     */
    bool setAngle(double);

    /**
     * Retoune vrai si le miroir peut être pivoté sur
     * l'angle donné, retourne faux sinon.
     * @return vrai si le miroir peut être pivoté sur
     * l'angle donné, retourne faux sinon.
     * @see Mirror::getAngle()
     */
    bool checkAngleRange(double) const;

    /**
     * Retoune vrai si le miroir peut être déplacé en la
     * position donnée, retourne faux sinon.
     * @return vrai si le miroir peut être déplacé en
     * la position donnée, retourne faux sinon.
     * @see Mirror::getPivot()
     */
    bool checkPivotRange(const Point &) const;

    /**
     * reemplementation de la méthode strike
     * @param ray un rayon a modifer par l'objet
     * @param p le point trouve pour donner fin au rayon
     * @return un nouveau rayon si l'object autorise
     */
    Ray * strike(Ray *& ray, Point p);

    /** permet calculer la position de la ligne ansi que les points de depart et final.
     * @param p point de pivot pour calculer la nouvelle position
     */
    void traceline(Point & p);

    /**
     * @brief getStart
     * @return
     */
    Point getStart() const;

    /**
     * @brief setStart
     * @param value
     */
    void setStart(const Point &value);

    /**
     * @brief getEnd
     * @return
     */
    Point getEnd() const;

    /**
     * @brief setEnd
     * @param value
     */
    void setEnd(const Point &value);

    /**
     * reemplementaion de la méthode mouseMoveEvent();
     * @brief mouseMoveEvent
     * @param event
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event);

    /**
     * reemplementaion de la méthode mousePressEvent();
     * @brief mousePressEvent
     * @param event
     */
    void mousePressEvent(QGraphicsSceneMouseEvent * event);

    /**
     * reemplementaion de la méthode mouseReleaseEvent();
     * @brief mouseReleaseEvent
     * @param event
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);

    /**
     * reemplementaion de la méthode paint.
     * @param painter
     * @param option
     * @param widget
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    /**
     * Surcharge l'opérateur de flux de sortie pour
     * afficher un récapitulatif des caractéristiques du
     * miroir sous-jacent en console.
     * @return le flux dans lequel le miroir a été imprimé.
     */
    friend std::ostream & operator<<(std::ostream & out,
                                     const Mirror & m);

signals:
    void actionMouse();
    void drawlimit(bool draw,Point p1,Point p2);
    //void rotated();
    //void moved();
};

#endif // MIRROR_H
