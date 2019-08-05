#include "generateur.h"
#include "ui_generateur.h"

#include <iostream>

#define PI (3.141592653589793)

generateur::generateur(QWidget *parent) :QDialog(parent),ui(new Ui::generateur)
{
    setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    ui->setupUi(this);
    longeurMap=0;
    hauteurMap=0;

    src= new Source(Point(0,0),0,0,0);
    dest= new Dest(Point(0,0),0);

    nomFichier=ui->nomFichier->text();

    connect(ui->ajouterSource,&QPushButton::clicked,this,&generateur::remplirSource);
    connect(ui->ajouterDest,&QPushButton::clicked,this,&generateur::remplirDest);
    connect(ui->ajouterMirroir,&QPushButton::clicked,this,&generateur::remplirMirrors);
    connect(ui->ajouterLen,&QPushButton::clicked,this,&generateur::remplirLens);
    connect(ui->ajouterBombe,&QPushButton::clicked,this,&generateur::remplirNukes);
    connect(ui->ajouterCrystal,&QPushButton::clicked,this,&generateur::remplirCrystal);
    connect(ui->ajouterMur,&QPushButton::clicked,this,&generateur::remplirWall);

    //terminer pour source et destination
    connect(ui->supprimerMirroir,&QPushButton::clicked,this,&generateur::viderMirrors);
    connect(ui->supprimerLen,&QPushButton::clicked,this,&generateur::viderLens);
    connect(ui->supprimerBombe,&QPushButton::clicked,this,&generateur::viderNukes);
    connect(ui->supprimerCrystal,&QPushButton::clicked,this,&generateur::viderCrystal);
    connect(ui->supprimerMur,&QPushButton::clicked,this,&generateur::viderWall);

    connect(ui->buttonBox,&QDialogButtonBox::accepted,this,&generateur::ajoutNomFichier);

    update();
}

generateur::~generateur()
{
    delete ui;
}

void generateur::ajoutNomFichier(){
    nomFichier = ui->nomFichier->text();
}

void generateur::remplirSource(){
    src = new Source(Point(ui->sourceX->value(),ui->sourceY->value()),ui->sourceEdge->value(),ui->sourceAngle->value(), ui->sourceWlength->value());
    ui->nbrSource->setText(QString::number(1));
    longeurMap=ui->longeurMap->value();
    hauteurMap=ui->hauteurMap->value();
   // nomFichier=ui->nomFichier->text();
}

void generateur::remplirDest(){
    dest= new Dest(Point(ui->DestX->value(),ui->DestY->value()),ui->DestEdge->value());
    ui->nbrDest->setText(QString::number(1));
    longeurMap=ui->longeurMap->value();
    hauteurMap=ui->hauteurMap->value();
   // nomFichier=ui->nomFichier->text();
}

void generateur::remplirMirrors(){
    Mirror * mir = new Mirror(Point(ui->mirX->value(),ui->mirY->value()),ui->mirTaille->value()/2,
                              ui->mirTaille->value(),ui->mirAngle->value(),Point(0,0),
                              Point(longeurMap,hauteurMap),0,2*PI);
    mirrors.push_back(mir);
    ui->nbrMirroir->setText(QString::number(mirrors.size()-1));

}

void generateur::remplirLens(){
    Lens * len = new Lens(Point(ui->lenX->value(),ui->lenY->value()),ui->lenWidth->value(),
                          ui->lenHeight->value(),ui->lenWlmin->value(),ui->lenWlmax->value());
    lenses.push_back(len);
    ui->nbrLen->setText(QString::number(lenses.size()-1));
}

void generateur::remplirNukes(){
    Nuke * nuk = new Nuke(Point(ui->bombeX->value(),ui->bombeY->value()),ui->bombeRad->value());
    nukes.push_back(nuk);
    ui->nbrBombe->setText(QString::number(nukes.size()-1));
}
void generateur::remplirCrystal(){
    Crystal *cry = new Crystal(Point(ui->crystalX->value(),ui->crystalY->value()),ui->crystalRad->value(),ui->crystalMod->value());
    crystals.push_back(cry);
    ui->nbrCrystal->setText(QString::number(crystals.size()-1));

}
void generateur::remplirWall(){
    Wall * mur = new Wall(Point(ui->murP1X->value(),ui->murP1Y->value()),Point(ui->murP2X->value(),ui->murP2Y->value()));
    walls.push_back(mur);
    ui->nbrMur->setText(QString::number(walls.size()-1));
}

void generateur::viderMirrors(){
    if(mirrors.size()-1>0){
        mirrors.pop_back();
        ui->nbrMirroir->setText(QString::number(mirrors.size()-1));
    }
}
void generateur::viderLens(){
    if(lenses.size()-1>0){
        lenses.pop_back();
        ui->nbrLen->setText(QString::number(lenses.size()-1));
    }
}
void generateur::viderNukes(){
    if(nukes.size()-1>0){
        nukes.pop_back();
        ui->nbrBombe->setText(QString::number(nukes.size()-1));

    }
}
void generateur::viderCrystal(){
    if(crystals.size()-1>0){
        crystals.pop_back();
        ui->nbrCrystal->setText(QString::number(crystals.size()-1));
    }
}
void generateur::viderWall(){
    if(walls.size()-1>0){
        walls.pop_back();
        ui->nbrMur->setText(QString::number(walls.size()-1));
    }
}
QString generateur::getNomFichier() const
{
    return nomFichier;
}

void generateur::setNomFichier(const QString &value)
{
    nomFichier = value;
}

Dest *generateur::getDest() const
{
    return dest;
}

void generateur::setDest(Dest *value)
{
    dest = value;
}

Source *generateur::getSrc() const
{
    return src;
}

void generateur::setSrc(Source *value)
{
    src = value;
}

int generateur::getHauteurMap() const
{
    return hauteurMap;
}

void generateur::setHauteurMap(int value)
{
    hauteurMap = value;
}

int generateur::getLongeurMap() const
{
    return longeurMap;
}

void generateur::setLongeurMap(int value)
{
    longeurMap = value;
}

std::vector<Nuke *> generateur::getNukes() const
{
    return nukes;
}

void generateur::setNukes(const std::vector<Nuke *> &value)
{
    nukes = value;
}

std::vector<Lens *> generateur::getLenses() const
{
    return lenses;
}

void generateur::setLenses(const std::vector<Lens *> &value)
{
    lenses = value;
}

std::vector<Crystal *> generateur::getCrystals() const
{
    return crystals;
}

void generateur::setCrystals(const std::vector<Crystal *> &value)
{
    crystals = value;
}

std::vector<Mirror *> generateur::getMirrors() const
{
    return mirrors;
}

void generateur::setMirrors(const std::vector<Mirror *> &value)
{
    mirrors = value;
}

std::vector<Wall *> generateur::getWalls() const
{
    return walls;
}

void generateur::setWalls(const std::vector<Wall *> &value)
{
    walls = value;
}

