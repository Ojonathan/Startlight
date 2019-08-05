#ifndef LEVEL_H
#define LEVEL_H

#include "crystal.h"
#include "dest.h"
#include "lens.h"
#include "mirror.h"
#include "ray.h"
#include "source.h"
#include "wall.h"
#include "point.h"
#include "nuke.h"
#include "objectStar.h"
#include "o_sdo/sujetdobservation.h"

#include <QGraphicsScene>
#include <vector>
#include <QPixmap>
#include <string>

using namespace std;

/**
 * Modélise une carte telle qu'utilisée dans le jeu.
 * </p>
 * Une carte est un ensemble de composant tels que des murs,
 * des miroirs, etc.
 */
//colocar sujeto de observacion.
class  Level :public SujetDObservation, public QGraphicsScene
{
    int width;                                          //largeur
    int height;                                         //hauteur

    int maxd; //diagonal
    int lastIndexObjectTouched;

    Source *src;                                        //la source
    Dest *dest;                                         //la destination

    std::vector<objectStar * > objetsCollided;
    //Point p2circle;

    std::vector<Wall *> walls;                          //tous les murs
    std::vector<Mirror *> mirrors;                      //tous les mirroirs
    std::vector<Crystal *> crystals;                    //tous les crystaux
    std::vector<Lens *> lenses;                         //toutes les lentilles
    std::vector<Nuke *> nukes;                          //toutes les bombes
    std::vector<Ray *> rays;                            //tous les rayons
    Ray * ray;                                          //rayon current pour faire les calculs

  public:

    /**
     * Instancie une carte de largeur et hauteur donnée.
     * </p>
     * Quand une carte est crée, quatre murs dénotant ses bords sont
     *  automatiquement ajoutés à la carte.
     * </p>
     * La source et la destination sont initialisées à des valeurs
     * par défaut inutilisables.
     * Vous devez manuellement initialiser la source et la destination
     * via les fonctions
     * appropriées.
     * @param w la largeur de la carte
     * @param h la heuteur de la carte
     */
    Level(int w, int h);

    /**
     * Retourne la source de la carte.
     * @return la source de la carte.
     */
    Source *getSrc() const;

    /**
     * Change la source de la carte
     * @param value la nouvelle source
     */

    void setSrc(Source *value);

    /**
     * Retourne la desination de la carte
     * @return la destination de la carte
     */

    Dest *getDest() const;

    /**
     * Change la destination de la carte
     * @param value la destination de la carte
     */

    void setDest(Dest *value);

    /**
     * Retourne l'ensemble des murs de la carte
     * @return l'ensemble des murs de la carte
     */
    const std::vector<Wall*> & getWalls() const;

    /**
     * Retourne l'ensemble des miroirs de la carte
     * @return l'ensemble des miroirs de la carte
     */
    const std::vector<Mirror*> & getMirrors() const;

    /**
     * @brief getNukes
     * @return
     */
    const std::vector<Nuke*> & getNukes() const;

    /**
     * Retourne l'ensemble des cristaux de la carte
     * @return l'ensemble des cristaux de la carte
     */
    const std::vector<Crystal*> & getCrystals() const;

    /**
     * Retourne l'ensemble des lentilles de la carte
     * @return l'ensemble des lentilles de la carte
     */
    const std::vector<Lens*> & getLenses() const;

    /**
     * Retourne l'ensemble des rayons de la carte
     * @return l'ensemble des rayons de la carte
     */
    //const std::vector<QGraphicsLineItem *> & getRays() const;
    const std::vector<Ray*> & getRays() const;

    /**
     * Change l'ensemble des rayons de la carte
     * @param le nouvel ensemble de rayons de la carte
     */
    //void setRays(const std::vector<Ray*> & v);

    /**
     * Calcule les rayons lumineux de la carte.
     * </p>
     * Cette fonction doit être surchargée obligatoirement.
     */
    void computeRays();

    /**
     * @brief lectureFichier
     * @param nFichier
     */
    void lectureFichier(const string & nFichier);

    /**
     * permet de faire le calcul pour chaque rayon.
     * @brief traceBeam
     * @param beam
     */
    void traceBeam(Ray *& beam);

    /**
     * permet de savoir quel est l'intersection la plus proche ansi que son objet
     * @brief collide
     * @param ray
     * @param p
     * @return
     */
    objectStar * collide(Ray *& ray, Point & p);

    /**
     * @brief get_line_intersection
     * @param p0
     * @param p1
     * @param p2
     * @param p3
     * @param p
     * @return
     */
    bool get_line_intersection(Point p0, Point p1, Point p2, Point p3 , Point & p);

    /**
     * @brief get_circle_intersections
     * @param p1
     * @param p2
     * @param sc
     * @param r
     * @param points
     * @return
     */
    bool get_circle_intersections(Point p1, Point p2, Point sc, double r, std::vector<Point> &points);

    /**
     * @brief get_ellipse_intersections
     * @param p1
     * @param p2
     * @param Width
     * @param Height
     * @param pos
     * @param points
     * @return
     */
    bool get_ellipse_intersections(Point p1, Point p2, double Width, double Height,
                                         Point pos, std::vector<Point> &points);

    /**
     * @brief get_square_intersections
     * @param p1
     * @param p2
     * @param pos
     * @param edge
     * @param p
     * @return
     */
    bool get_square_intersections(Point p1,Point p2,Point pos, int edge,Point & p);

    /**
     * @brief getLastIndexObjectTouched
     * @return
     */
    int getLastIndexObjectTouched() const;

    /**
     * Retourne la valeur de la longeur de level
     * @return
     */
    int getWidth() const;

    /**
     * Retourne la valeur de l'hauteur de level
     * @return
     */
    int getHeight() const;
};




#endif // LEVEL_H
