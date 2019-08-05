#include "gameview.h"
#include "ui_gameview.h"
#include "metier_abs/mirror.h"

#include <QPixmap>
#include <QMessageBox>
#include <iostream>
#include <QWidget>
#include <QObject>
#include <vector>
#include <cmath>

#define PI (3.141592653589793)

gameView::gameView(Level * level, QWidget * parent):QGraphicsView{parent},scene{level}
{
    this->setScene(scene);

    dlimit = new QGraphicsRectItem();

    setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );// pour désactiver le scroll lors du changement de map
    setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );

    //taille de gameView
    setFixedWidth(scene->getWidth() + 20);
    setFixedHeight(scene->getHeight() + 20);

    setMouseTracking(true);

    //attacher l'observateur.
    scene->attacher(this);

    setBackgroundBrush(QBrush(QPixmap(":resource/fond5.png")));

    //source
    connect(scene->getSrc(),SIGNAL(mesOn()),this,SLOT(compute()));
    scene->addItem(scene->getSrc());

    //destination
    scene->addItem(scene->getDest());

    //cristals
    for(unsigned i = 0; i<scene->getCrystals().size();i++){
        scene->addItem(scene->getCrystals()[i]);
    }

    //murs
    for(unsigned i = 0; i<scene->getWalls().size();i++){
        scene->addItem(scene->getWalls()[i]);
    }

    //bombes
    for(unsigned i = 0; i<scene->getNukes().size();i++){
        scene->addItem(scene->getNukes()[i]);
    }

    //lens
    for(unsigned i = 0; i<scene->getLenses().size();i++){
        scene->addItem(scene->getLenses()[i]);
    }

    //Mirrors
    //faire le connect pour chaque mirroir, c'est à dire, si un mirroir n'importe le quelle fait un mouvement
    //alors le mirroir emet une signal pour executer la methode computerays() de Level(c'est à fois le scene).
    for(unsigned i = 0; i<scene->getMirrors().size();i++){
        //connect(scene->getMirrors()[i],&Mirror::moved(),this,&gameView::compute());
        //connect(scene->getMirrors()[i],SIGNAL(moved()),this,SLOT(compute()));
        connect(scene->getMirrors()[i],SIGNAL(actionMouse()),this,SLOT(compute()));
        connect(scene->getMirrors()[i],SIGNAL(drawlimit(bool,Point,Point)),
                this,SLOT(limit(bool,Point,Point)));
        scene->addItem(scene->getMirrors()[i]);
    }

    //pour la premiere fois.
    scene->computeRays();
}

void gameView::limit(bool draw,Point p1,Point p2){
   if(draw){
       std::cout<<p1<<" "<<p2<<std::endl;
       //fonctionne uniquement si yMax est superieur a yMin
       QPen penlimit(Qt::white,2);
       dlimit->setPen(penlimit);
       dlimit->setRect(p1.getX(),p1.getY(),p2.getX() - p1.getX(),p2.getY() - p1.getY());
       scene->addItem(dlimit);
   }else{
       scene->removeItem(dlimit);
   }
}

void gameView::compute()
{
    scene->computeRays();
}

gameView::~gameView()
{
    scene->detacher(this);
    delete dlimit;
}

//utilisée pour visualizer les changements.
void gameView::rafraichir(SujetDObservation* sdo)
{
    //mettre en scene les rayon creés.
    for(unsigned i = 0; i< scene->getRays().size();i++){
        scene->addItem(scene->getRays()[i]);
    }


    //verifier si la destination a été touchée.
    if(scene->getDest()->isLightedUp()){
        QMessageBox::information(this,"Felicitations","Vous avez gagné");
        setEnabled(false);
    }

    //verifier si une bombe a été touchée.
    for(unsigned i = 0; i < scene->getNukes().size(); i++){
        if(scene->getNukes()[i]->isLightedUp()){
            QMessageBox::critical(this,"Desolé ...","Vous avez perdu");
            setEnabled(false);
        }
    }

}
