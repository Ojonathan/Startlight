#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsScene>
#include <QGraphicsLineItem>        //para pruebas
#include <QGraphicsView>
#include <QMouseEvent>

#include <QWidget>
#include <QObject>

#include "metier_abs/level.h"
#include "metier_abs/ray.h"
#include "metier_abs/mirror.h"
#include "metier_abs/point.h"
#include "o_sdo/observateur.h"

class gameView : public QGraphicsView , public Observateur
{
    Q_OBJECT
private:
    Level * scene {nullptr};
    QGraphicsRectItem * dlimit {nullptr};

public:
    //gameView(QWidget *parent = nullptr);
    gameView(Level * level, QWidget * parent = nullptr);
    ~gameView();
    void rafraichir(SujetDObservation* sdo);

public slots:
    void compute();
    void limit(bool draw,Point p1,Point p2);
};

#endif // GAMEVIEW_H
