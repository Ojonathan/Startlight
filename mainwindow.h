#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <vector>
#include <string>
#include <QGraphicsItem>
#include <QAction>
#include <QHBoxLayout>

#include "gameview.h"
#include "metier_abs/lens.h"

#include <QWidget>
#include <QObject>

namespace Ui {
class MainWindow;
}
using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void conection();
    void afficherLaser();

private slots:
    void Aide();
    void observateurGameView(bool actif);
    void personaliserPartie();
    void generat();
    void partieDefaut();
    //void partieReussi();

private:
    Ui::MainWindow *ui;
    QAction *aide;
    Level * scene {nullptr};
    gameView * observateurView {nullptr};

};

#endif // MAINWINDOW_H
