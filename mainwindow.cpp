#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "generateur.h"
#include <QMessageBox>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <QFileDialog>
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{ 
    ui->setupUi(this);
    scene = nullptr;
    observateurView = nullptr;

    ui->actionAffichage->setEnabled(false);                          //desactivé, il faut choisir le fichier
    ui->actionAffichage->setCheckable(true);                          //button generer gameView

    this->setMouseTracking(true);                                     //mouse move tracking.

    aide = ui->menuBar->addAction(tr("Aide"));                        //button aide

    ui->actionPersonnaliser->setShortcut(QKeySequence(tr("Ctrl+P"))); //shortcuts
    ui->actionQuitter->setShortcut(QKeySequence(tr("Ctrl+Q")));
    ui->actionDefaut->setShortcut(QKeySequence(tr("Ctrl+D")));

    //this->setStyleSheet("background-image: url(:resource/fondEcran.png)");
    //this->setsetBackgroundBrush(QBrush(QPixmap(":resource/fondEcran.png")));
    conection();
    //update();
}

void MainWindow::conection(){
    connect(ui->actionQuitter, &QAction::triggered,&QCoreApplication::quit);
    connect(ui->actionAffichage, &QAction::toggled,this,&MainWindow::observateurGameView);
    connect(ui->actionPersonnaliser, &QAction::triggered,this,&MainWindow::personaliserPartie);
    connect(ui->actionGenerateur, &QAction::triggered,this,&MainWindow::generat);
    connect(ui->actionDefaut, &QAction::triggered,this,&MainWindow::partieDefaut);
    connect(aide, &QAction::triggered,this,&MainWindow::Aide);
}

MainWindow::~MainWindow()
{
    //usar la misma tecnica como pendu para borrar.
    //delete observateurView;
    delete ui;
}

void MainWindow::Aide(){
    QMessageBox::information(this,"Aide","Règle du jeu " "<p>Starlight puzzle"
                             " est un jeu de plateau à deux Le jeu consiste a renvoyé "
                             "un rayon depuis une source vers la destination en déviant celui-ci à l’aide de miroirs. </p>"
                             "<p> Attention lorsque vous avez commencez à émmettre le rayon tanter d'évité quelques obstacles en fonction du niveau  choisi. </p>"
                             " Lorsque un mur est touché par un rayon, celui-ci n’est pas renvoyé. "
                             " Si le rayon touche une bombe, la partie est perdu et recommencez. "
                             " Si le rayon touche un crystal, la longueur d’onde du rayon est modifiée. "
                             " Si un rayon touche une lentille, il pourra la traversé uniquement si sa longueur d’onde "
                             " est comprise dans une intervalle accepter par la lentille. "
                             "<p>Pour activé et commencé à émettre un rayon depuis la source, cliqué deux fois sur celle-ci. </p>"
                             "<p>Pour déplacé un miroir, il faut maintenir bouton gauche souris et "
                              "le déplacé à la zone  voulue par contre pour le faire pivoté, il faut "
                             "maintenir le bouton droits souris appuié et se déplacé en fonction de l’angle voulus. </p>"
                             "<b>  Bon jeu </b>  ");
}

void MainWindow::generat(){
    generateur  gen(this);
    int retour = gen.exec();
    if (retour == QDialog::Rejected) {
        return;
    }else{

        std::stringstream saveFichier;
        saveFichier << QDir::currentPath().toStdString() << "/maps/" << gen.getNomFichier().toStdString() << ".mapl";
        QFile file(QString::fromStdString(saveFichier.str()));

        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

        QTextStream out(&file);

        out<< gen.getHauteurMap() << " " << gen.getLongeurMap()<<"\n";
        out<< "S "<<gen.getSrc()->getPosition().getX()<<" ";
        out<< gen.getSrc()->getPosition().getY()<<" ";
        out<< gen.getSrc()->getEdge()<<" ";
        out<< gen.getSrc()->getAngle()<< " ";
        out<< gen.getSrc()->getWavelength()<<"\n";

        out<< "D " << gen.getDest()->getPosition().getX()<<" ";
        out<< gen.getDest()->getPosition().getY()<<" ";
        out<< gen.getDest()->getEdge()<<"\n";

        if(gen.getWalls().size()-1>0&& gen.getWalls().size()-1<20){
            for(unsigned i=0;i<gen.getWalls().size()-1;i++){
                out<< "W " <<gen.getWalls()[i]->getStart().getX()<<" ";
                out<< gen.getWalls()[i]->getStart().getY()<<" ";
                out<<gen.getWalls()[i]->getEnd().getX()<<" ";
                out<<gen.getWalls()[i]->getEnd().getY()<<"\n";
            }
        }
        if(gen.getMirrors().size()-1>0 && gen.getMirrors().size()-1<20){
            for(unsigned i=0;i<gen.getMirrors().size()-1;i++){
                out<< "M " << gen.getMirrors()[i]->getPivot().getX()<< " ";
                out<< gen.getMirrors()[i]->getPivot().getY()<< " ";
                out<< gen.getMirrors()[i]->getLength()<< " ";
                out<< gen.getMirrors()[i]->getAngle()<< "\n";
            }
        }
        if(gen.getNukes().size()-1>0&& gen.getNukes().size()-1<20){
            for(unsigned i=0;i<gen.getNukes().size()-1;i++){
                out<< "N " << gen.getNukes()[i]->getLocation().getX() <<" ";
                out<< gen.getNukes()[i]->getLocation().getY() <<" ";
                out<< gen.getNukes()[i]->getRadius() <<"\n";

            }
        }
        if(gen.getCrystals().size()-1>0&& gen.getCrystals().size()-1<20){
            for(unsigned i=0;i<gen.getCrystals().size()-1;i++){
                out<< "C " << gen.getCrystals()[i]->getCenter().getX() <<" ";
                out<< gen.getCrystals()[i]->getCenter().getY() <<" ";
                out<< gen.getCrystals()[i]->getRadius() << " ";
                out<< gen.getCrystals()[i]->getModifier() <<"\n";
            }
        }
        if(gen.getLenses().size()-1>0 && gen.getLenses().size()-1<20){
            for(unsigned i=0;i<gen.getLenses().size()-1;i++){
                out<< "L " <<gen.getLenses()[i]->getPosition().getX() <<" ";
                out<<gen.getLenses()[i]->getPosition().getY() <<" ";
                out<< gen.getLenses()[i]->getWidth() << " ";
                out<< gen.getLenses()[i]->getHeight() <<" ";
                out<< gen.getLenses()[i]->getMinWavelength() << " ";
                out<< gen.getLenses()[i]->getMaxWavelength() << "\n";
            }
        }
        //std::cout<<"Fichier cree";
    }

}

//faire l'appel de gameView.
void MainWindow::observateurGameView(bool actif){
    if(actif){
        if(observateurView == nullptr){
            observateurView = new gameView(scene);
        }

        //ligne important pour l'utiliser avec mainWindow
        ui->verticalLayout_2->addWidget(observateurView);
        observateurView->show();

        //taille de le scene.
    }else {
        if(observateurView != nullptr){
            observateurView->hide();
        }
    }
}

void MainWindow::partieDefaut(){
    //supprimer l'observateur
    delete observateurView;
    observateurView = nullptr;

    //supprimer le jeu
    delete scene;
    scene = nullptr;

    string nomf = QDir::currentPath().toStdString();
    nomf = nomf + "/maps/test3.map";
    std::cout<<"directorio actual: "<<nomf<<std::endl;

    //lecture de la premiere ligne, pour controler la lecture de taille.
    const string file = nomf;
    ifstream fichier(file);
    string str;

    if(getline(fichier, str)){
        string buf;
        stringstream ss(str);                               //avoir un buffer string
        vector<string> tokens;
        while (ss >> buf){
            tokens.push_back(buf);
        }
        //creation de la scene.
        if(tokens.size() == 2){
            scene = new Level(stoi(tokens[0]),stoi(tokens[1]));
            ui->actionAffichage->setEnabled(true);
            ui->actionAffichage->setChecked(false);
        }else{
            std::cout<<"fichier incomplet!!!!"<<endl;
        }
    }
    fichier.close();
    //lecture des donnees restant.
    scene->lectureFichier(file);
    ui->actionAffichage->setChecked(true);
    observateurGameView(true);
}

void MainWindow::personaliserPartie(){
    bool isGood = true;
    //lecture de fichier.
    QString nomFichier = QFileDialog::getOpenFileName(this,"Choisir un fichier map",
                                                      QDir::currentPath(),"MAP (*.map *.mapl)");
    const string file = nomFichier.toStdString();

    if(nomFichier.isEmpty()){
        //la chaine de caracteres est vide pourtant l'utilisateur n'a pas choisi un fichier.
    }else{
        //supprimer l'observateur
        delete observateurView;
        observateurView = nullptr;

        //supprimer le jeu
        delete scene;
        scene = nullptr;

        //ui->actionAffichage->setEnabled(true);
        ui->actionAffichage->setChecked(false);
        try{
        //lecture de la premiere ligne, pour controler la lecture de taille.
        ifstream fichier(file);
        string str;

        if(getline(fichier, str)){
            string buf;
            stringstream ss(str);                               //avoir un buffer string
            vector<string> tokens;
            while (ss >> buf){
                tokens.push_back(buf);
            }
            //creation de la scene.
            if(tokens.size() == 2){
                scene = new Level(stoi(tokens[0]),stoi(tokens[1]));
            }else{
                isGood = false;
                std::cout<<"fichier incomplet!!!!"<<endl;
            }
        }
        fichier.close();

        } catch (std::exception & e){
            isGood = false;
            std::cout<<"Error de lecture premiere ligne "<<std::endl;
        }

        if(isGood == true){
            try{
                scene->lectureFichier(file);
            }catch(std::string e){
                isGood = false;
            }
        }

        if(isGood == true){
            ui->actionAffichage->setEnabled(true);
            ui->actionAffichage->setChecked(true);
        }else{
            ui->actionAffichage->setEnabled(false);
            ui->actionAffichage->setChecked(false);
        }
    }
}
