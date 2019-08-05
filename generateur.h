#ifndef GENERATEUR_H
#define GENERATEUR_H

#include <QDialog>

#include "metier_abs/level.h"
#include "metier_abs/ray.h"
#include "metier_abs/mirror.h"
#include "metier_abs/crystal.h"
#include "metier_abs/dest.h"
#include "metier_abs/source.h"
#include "metier_abs/lens.h"
#include "metier_abs/nuke.h"
#include "metier_abs/wall.h"
#include "string.h"

namespace Ui {
class generateur;
}

class generateur : public QDialog
{
    Q_OBJECT

public:
    explicit generateur(QWidget *parent = 0);
    ~generateur();

    QString getNomFichier() const;
    void setNomFichier(const QString &value);

    int getLongeurMap() const;
    void setLongeurMap(int value);

    int getHauteurMap() const;
    void setHauteurMap(int value);

    Source *getSrc() const;
    void setSrc(Source *value);

    Dest *getDest() const;
    void setDest(Dest *value);

    std::vector<Wall *> getWalls() const;
    void setWalls(const std::vector<Wall *> &value);

    std::vector<Mirror *> getMirrors() const;
    void setMirrors(const std::vector<Mirror *> &value);

    std::vector<Crystal *> getCrystals() const;
    void setCrystals(const std::vector<Crystal *> &value);

    std::vector<Lens *> getLenses() const;
    void setLenses(const std::vector<Lens *> &value);

    std::vector<Nuke *> getNukes() const;
    void setNukes(const std::vector<Nuke *> &value);

private slots:
    void remplirSource();
    void remplirDest();
    void remplirMirrors();
    void remplirLens();
    void remplirNukes();
    void remplirCrystal();
    void remplirWall();
    void viderMirrors();
    void viderLens();
    void viderNukes();
    void viderCrystal();
    void viderWall();
    void ajoutNomFichier();

private:
    Ui::generateur *ui;

    QString nomFichier;
    int longeurMap;
    int hauteurMap;

    Source *src;                                        //la source
    Dest *dest;                                         //la destination

    std::vector<Wall *> walls;                          //tous les murs
    std::vector<Mirror *> mirrors;                      //tous les mirroirs
    std::vector<Crystal *> crystals;                    //tous les crystaux
    std::vector<Lens *> lenses;                         //toutes les lentilles
    std::vector<Nuke *> nukes;                          //toutes les bombes


};

#endif // GENERATEUR_H
