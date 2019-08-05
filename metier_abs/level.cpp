#include "level.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <exception>
#include <cmath>
#include <iomanip>

#define PI (3.141592653589793)

using namespace std;

//zona de inicializacion para las variables constantes.
Level::Level(int w, int h) : width {w}, height {h}
{
    //verifier width
    if(width == 0){
        width = 750;
    }else if(width < 0){
        width = abs(width);
    }

    //verifier height
    if(height == 0){
        height = 580;
    }else if(height < 0 ){
        height = abs(height);
    }

    this->setSceneRect(0,0,width,height);                               //taille de la scene.
    maxd = hypot(width,height);

    //4 murs par defaut
    walls.push_back(new Wall(Point(0,0),Point(width,0)));               //  -----
    walls.push_back(new Wall(Point(0,0),Point(0,height)));              //  |
    walls.push_back(new Wall(Point(width,height),Point(width,0)));      //      |
    walls.push_back(new Wall(Point(width,height),Point(0,height)));     //  _____

    lastIndexObjectTouched = 0;
    src = nullptr;
    dest = nullptr;
}

//getters
const vector<Wall *> & Level::getWalls() const
{
    return walls;
}

const vector<Mirror *> & Level::getMirrors() const
{
    return mirrors;
}

const vector<Crystal *> & Level::getCrystals() const
{
    return crystals;
}

const vector<Lens *> & Level::getLenses() const
{
    return lenses;
}

const vector<Ray *> & Level::getRays() const{
    return rays;
}

const vector<Nuke *> & Level::getNukes() const
{
    return nukes;
}

Source * Level::getSrc() const
{
    return src;
}

Dest *Level::getDest() const
{
    return dest;
}

void Level::setSrc(Source *value)
{
    src = value;
}

void Level::setDest(Dest *value)
{
    dest = value;
}

void Level::computeRays()
{
    //nettoyer l'interface et recommencer.
    for(unsigned i = 0; i< rays.size();i++){
        removeItem(rays[i]);
    }

    //nettoyer le vecteur pour recommencer.
    rays.clear();

    //si la source est allumée alors on fait le calcule
    if(src->isOn()){
        std::cout<<"la source est allumée pourtant je lance le rayon"<<std::endl;
        ray = new Ray(Point((src->getPosition().getX() + src->getEdge()/2),(src->getPosition().getY() + src->getEdge()/2)),
                      src->getAngle(),src->getWavelength());

        lastIndexObjectTouched = 0;
        traceBeam(ray);

        std::cout<<"nombre des rayons a desiner: "<<rays.size()<<std::endl;
        notifierChangement();
    }

    //delete ray;
}

//cette methode reagit avec le laser en fonction de chaque objet dans la scene

void Level::traceBeam(Ray *& beam){
    Ray * child = nullptr;
    objectStar * nearest = nullptr;
    int counter = 0;                      //utilisé pour eviter un bucle infinit.c-t-d on va un max de 500 rayon.

    do {
        double rcos = cos(beam->getAngle());            //calculo de la direction que tomara el punto
        double rsin = -1 * sin(beam->getAngle());       //para cambiar el sentido del rayo.

        Point pEnd(beam->getStart().getX() + maxd * rcos,beam->getStart().getY() + maxd * rsin);

        beam->setEnd(pEnd);            //donner au rayon actuel un point final pour faire le calcul d'intersection

        nearest = collide(beam,pEnd); //rayon et point qui sera modifie avec le point le plus proche.
                                        //rayon touche un object star
        child = nearest->strike(beam,pEnd);

        rays.push_back(new Ray(beam->getStart(),beam->getEnd(),beam->getWavelength()));
        beam = child; //remplacement du rayon courant
        child = nullptr;
        //nearest = nullptr;
        counter++; //faire ceci tant que la methode strike renvoi pas un nullptr (source, bombe, dest, mur)
    } while (beam != nullptr && counter < 500 );

    delete child;
    //delete nearest;//tester.
}

//pEnd reçoit à la fin le point d'intersection le plus proche.
objectStar * Level::collide(Ray *& ray, Point & p){
    std::vector<double> distancias;
    objetsCollided.clear();
    std::vector<Point> points;
    double dis;

    //collision destination.
    if(get_square_intersections(ray->getStart(),ray->getEnd(),dest->getPosition(),dest->getEdge(),p) &&
            dest->getIndex() != lastIndexObjectTouched){

        dis = sqrt(pow(p.getX()-ray->getStart().getX(), 2) + pow(p.getY()-ray->getStart().getY(), 2)); //calcule distance entre deux point
        objetsCollided.push_back(dest);
        distancias.push_back(dis);
        points.push_back(p);
        std::cout<<"OUI destination !!!!"<<std::endl;
    }else{
        std::cout<<"NON destination !!!!"<<std::endl;
    }

    //collision Murs
    for(unsigned i = 0; i < walls.size(); i++){
        if(get_line_intersection(ray->getStart(),ray->getEnd(),walls[i]->getStart(),walls[i]->getEnd(),p) &&
                                 walls[i]->getIndex() != lastIndexObjectTouched){

            dis = sqrt(pow(p.getX()-ray->getStart().getX(), 2) + pow(p.getY()-ray->getStart().getY(), 2));//calcule distance
            objetsCollided.push_back(walls[i]);
            distancias.push_back(dis);
            points.push_back(p);
        }
    }
    //collision Mirroirs
    for(unsigned i = 0; i < mirrors.size(); i++){
        if(get_line_intersection(ray->getStart(),ray->getEnd(),
                                 mirrors[i]->getStart(),mirrors[i]->getEnd(),p) &&
                                 mirrors[i]->getIndex() != lastIndexObjectTouched){

            dis = sqrt(pow(p.getX()-ray->getStart().getX(), 2) + pow(p.getY()-ray->getStart().getY(), 2));
            objetsCollided.push_back(mirrors[i]);
            distancias.push_back(dis);
            points.push_back(p);
        }
    }

    //collision Crystaux
    for(unsigned i = 0; i < crystals.size(); i++){
        //std::cout<<"dentro del for cristales: "<<*ray<<std::endl;
        std::vector<Point> pIntersections;
        if(get_circle_intersections(ray->getStart(),ray->getEnd(),crystals[i]->getCenter(),
                  crystals[i]->getRadius(),pIntersections) && crystals[i]->getIndex() != lastIndexObjectTouched){

            std::cout<<"OUI crystal !!!!!!!!";
            for(unsigned i = 0; i < pIntersections.size(); i++){
                std::cout<<" p"<<i+1<<" "<<pIntersections[i]<<" ";
            } //il y a toujour deux point d'interscetion verifie ou un point qui passe par la lentille
            std::cout<<std::endl;
            if(pIntersections.size() == 1){
                crystals[i]->setP2circle(pIntersections[0]);
                p = pIntersections[0];
            }else if(pIntersections.size() == 2){
                crystals[i]->setP2circle(pIntersections[0]);
                p = pIntersections[1];              //end
            }
            dis = sqrt(pow(p.getX()-ray->getStart().getX(), 2) + pow(p.getY()-ray->getStart().getY(), 2)); //calcule de distance
            objetsCollided.push_back(crystals[i]);
            distancias.push_back(dis);
            points.push_back(p);
        }else{
            std::cout<<"NON crystal !!!!!!!!"<<std::endl;
        }
    }
    //collision bombes
    for(unsigned i = 0; i < nukes.size(); i++){
        std::vector<Point> pIntersections;
        if(get_circle_intersections(ray->getStart(),ray->getEnd(),nukes[i]->getLocation(),
                  nukes[i]->getRadius(),pIntersections) && nukes[i]->getIndex() != lastIndexObjectTouched){

            std::cout<<"OUI bombe !!!!!!!!!!"<<std::endl;
            if(pIntersections.size() == 1){
                p = pIntersections[0];
            }else if(pIntersections.size() == 2){
                p = pIntersections[1];
            }
            dis = sqrt(pow(p.getX()-ray->getStart().getX(), 2) + pow(p.getY()-ray->getStart().getY(), 2));
            objetsCollided.push_back(nukes[i]);
            distancias.push_back(dis);
            points.push_back(p);
        }else{
            std::cout<<"NON bombe !!!!!!!!!!"<<std::endl;
        }
    }

    //collision lentilles.
    for(unsigned i = 0; i < lenses.size(); i++){
        std::vector<Point> pIntersections;
        if(get_ellipse_intersections(ray->getStart(),ray->getEnd(),lenses[i]->getWidth(),
                           lenses[i]->getHeight(),lenses[i]->getPosition(),pIntersections) &&
                           lenses[i]->getIndex() != lastIndexObjectTouched){
            std::cout<<"OUI lentille !!!!!!!";
            for(unsigned i = 0; i < pIntersections.size(); i++){
                std::cout<<" p"<<i+1<<" "<<pIntersections[i]<<" ";
            }
            std::cout<<std::endl;
            if(pIntersections.size() == 1){
                lenses[i]->setP2ellipse(pIntersections[0]);
                p = pIntersections[0];
            }else if(pIntersections.size() == 2){
                lenses[i]->setP2ellipse(pIntersections[0]);
                p = pIntersections[1];
            }
            dis = sqrt(pow(p.getX()-ray->getStart().getX(), 2) + pow(p.getY()-ray->getStart().getY(), 2));
            objetsCollided.push_back(lenses[i]);
            distancias.push_back(dis);
            points.push_back(p);
        }else{
            std::cout<<"NON lentille !!!!!!!"<<std::endl;
        }
    }

    //identifier la distance la plus court
    const std::vector<double>::iterator iter_min = std::min_element(distancias.begin(),distancias.end() ) ;
    const double min_element = *iter_min ;        //element MIN
    const int min_element_pos = iter_min - distancias.begin() ;

    std::cout<<"--- Le dernier rayon: "<< *ray << " a des INTERSECTIONS AVEC LES ELEMENTS SUIVANTS ---"<<std::endl;

    //afficher les objets collisionés.
    for( std::size_t i = 0 ; i < distancias.size() ; i++ ) {
        std::cout<<i<<"   "<<std::setw(13)<<std::left<<objetsCollided[i]->getName()<<"point d'intersection: "<<
                   points[i]<<"   distance: "<<distancias[i]<<std::endl;

    }

    //afficher donnees pour verifier.
    std::cout<<"---- l'element le plus proche est: "<<min_element_pos<<std::endl;
    std::cout<<"---- la distance la plus courte est: "<<min_element<<std::endl;
    std::cout<<"---- le point d'intersection le plus proche est: "<<points[min_element_pos]<<std::endl;
    std::cout<<std::endl;

    //p reçoit le point le plus proche, et on retourne l'element le plus proche.
    p = points[min_element_pos];
    lastIndexObjectTouched = objetsCollided[min_element_pos]->getIndex();
    return objetsCollided[min_element_pos];
}

bool Level::get_line_intersection(Point p0, Point p1, Point p2, Point p3 , Point & p)
{
    //segment 1 .. rayon
    double p0_x = p0.getX();
    double p0_y = p0.getY();
    double p1_x = p1.getX();
    double p1_y = p1.getY();
    //segment 2 .. Mirroir
    double p2_x = p2.getX();
    double p2_y = p2.getY();
    double p3_x = p3.getX();
    double p3_y = p3.getY();

    double s1_x, s1_y, s2_x, s2_y;
    s1_x = p1_x - p0_x;     s1_y = p1_y - p0_y;
    s2_x = p3_x - p2_x;     s2_y = p3_y - p2_y;

    double s, t;
    s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
    t = ( s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
    {
        p.setX(p0_x + (t * s1_x));//*i_x = p0_x + (t * s1_x);
        p.setY(p0_y + (t * s1_y));//*i_y = p0_y + (t * s1_y);
        return true;   //collision
    }
    return false; // Non collision
}

bool Level::get_circle_intersections(Point p1, Point p2, Point sc, double r,std::vector<Point> & points) {

      double    a, b, c;
      Point     dp;

      dp.setX(p2.getX() - p1.getX());
      dp.setY(p2.getY() - p1.getY());

      a = dp.getX() * dp.getX() + dp.getY() * dp.getY();
      b = 2 * (dp.getX() * (p1.getX() - sc.getX()) + dp.getY() * (p1.getY() - sc.getY()));
      c = sc.getX() * sc.getX() + sc.getY() * sc.getY();
      c += p1.getX() * p1.getX() + p1.getY() * p1.getY();
      c -= 2 * (sc.getX() * p1.getX() + sc.getY() * p1.getY());
      c -= r * r;

      double bb4ac = b * b - 4 * a * c;

      if(a <= 0.0000001 || bb4ac < 0) {
          return false;
      }

      double mu1 = (-b + sqrt(bb4ac)) / (2 * a);
      double mu2 = (-b - sqrt(bb4ac)) / (2 * a);

      // no intersection
      if((mu1 < 0 || mu1 > 1) && (mu2 < 0 || mu2 > 1)) {
        return false;
      }
      // one point on mu1
      else if(mu1 > 0 && mu1 < 1 && (mu2 < 0 || mu2 > 1)) {
        points.push_back(Point(p1.getX() + mu1 * dp.getX(), p1.getY() + mu1 * dp.getY()));
        return true;
      }
      // one point on mu2
      else if(mu2 > 0 && mu2 < 1 && (mu1 < 0 || mu1 > 1)) {
        points.push_back(Point(p1.getX() + mu2 * dp.getX(), p1.getY() + mu2 * dp.getY()));
        return true;
      }
      //  one or two points
      else if(mu1 > 0 && mu1 < 1 && mu2 > 0 && mu2 < 1) {

        //  tangential
        if(mu1 == mu2) {
          points.push_back(Point(p1.getX() + mu1 * dp.getX(), p1.getY() + mu1 * dp.getY()));
        }
        //  two points
        else {
          points.push_back(Point(p1.getX() + mu1 * dp.getX(), p1.getY() + mu1 * dp.getY()));
          points.push_back(Point(p1.getX() + mu2 * dp.getX(), p1.getY() + mu2 * dp.getY()));
        }
        return true;
      }
      else {
        return false;
      }
      return false;
}

bool Level::get_ellipse_intersections(Point p1, Point p2,double Width, double Height,
                                            Point pos,std::vector<Point> & points)
{
    bool res = false;
    std::vector<double > t_values;

    // Translate so the ellipse is centered at the origin.
    double cx = pos.getX() + Width / 2;
    double cy = pos.getY() + Height / 2;

    //pos.setX(pos.getX() - cx);
    //pos.setY(pos.getY() - cx);

    p1.setX(p1.getX() - cx);// -= cx;
    p1.setY(p1.getY() - cy);// -= cy;
    p2.setX(p2.getX() - cx);// -= cx;
    p2.setY(p2.getY() - cy);// -= cy;

    // Get the semimajor and semiminor axes.
    double a = Width / 2;
    double b = Height / 2;

    // Calculate the quadratic parameters.
    double A = (p2.getX() - p1.getX()) * (p2.getX() - p1.getX()) / a / a +
        (p2.getY() - p1.getY()) * (p2.getY() - p1.getY()) / b / b;
    double B = 2 * p1.getX() * (p2.getX() - p1.getX()) / a / a +
        2 * p1.getY() * (p2.getY() - p1.getY()) / b / b;
    double C = p1.getX() * p1.getX() / a / a + p1.getY() * p1.getY() / b / b - 1;

    // Calculate the discriminant.
    double discriminant = B * B - 4 * A * C;

    if (discriminant == 0)
    {
        // One real solution.
        t_values.push_back(-B / 2 / A);
    }
    else if (discriminant > 0)
    {
        // Two real solutions.
        t_values.push_back((double)((-B + sqrt(discriminant)) / 2 / A));
        t_values.push_back((double)((-B - sqrt(discriminant)) / 2 / A));
    }

    for(unsigned i = 0; i < t_values.size(); i++){
        double t = t_values[i];
        // If the points are on the segment (or we
        // don't care if they are), add them.
        if ((t >= 0) && (t <= 1)){
            double x = p1.getX() + (p2.getX() - p1.getX()) * t + cx;
            double y = p1.getY() + (p2.getY() - p1.getY()) * t + cy;
            points.push_back(Point(x,y));
            res = true;
        }
    }
    return res;
}

bool Level::get_square_intersections(Point p1,Point p2,Point pos, int edge,Point & p) {
    std::vector<Point > points;
    std::vector<double> distances;
    double dis;
    bool res = false;

    // Top line.....coté superieur
    if(get_line_intersection(p1,p2,pos,Point(pos.getX() + edge,pos.getY()),p)){

        dis = sqrt(pow(p.getX()-p1.getX(), 2) + pow(p.getY()- p1.getY(), 2));
        distances.push_back(dis);
        points.push_back(p);
        res = true;
    }

    //Bottom line...coté inferieur
    if(get_line_intersection(p1,p2,Point(pos.getX(),pos.getY() + edge),
                             Point(pos.getX() + edge,pos.getY() + edge),p)){

        dis = sqrt(pow(p.getX()-p1.getX(), 2) + pow(p.getY()- p1.getY(), 2));
        distances.push_back(dis);
        points.push_back(p);
        res = true;
    }

    //Left side...coté gauche
    if(get_line_intersection(p1,p2,pos,Point(pos.getX(),pos.getY() + edge),p)){

        dis = sqrt(pow(p.getX()-p1.getX(), 2) + pow(p.getY()- p1.getY(), 2));
        distances.push_back(dis);
        points.push_back(p);
        res = true;
    }

    //Right side...coté droite
    if(get_line_intersection(p1,p2,Point(pos.getX() + edge,pos.getY()),
                             Point(pos.getX() + edge,pos.getY() + edge),p)){

        dis = sqrt(pow(p.getX()-p1.getX(), 2) + pow(p.getY()- p1.getY(), 2));
        distances.push_back(dis);
        points.push_back(p);
        res =true;
    }

    //verifier le point le plus proche.
    if(res == true){
        //identifier la distance la plus court
        const std::vector<double>::iterator iter_min = std::min_element(distances.begin(),distances.end() ) ;
        const int min_element_pos = iter_min - distances.begin();

        p = points[min_element_pos];
    }
    return res;
}


int Level::getLastIndexObjectTouched() const
{
    return lastIndexObjectTouched;
}


int Level::getWidth() const
{
    return width;
}

int Level::getHeight() const
{
    return height;
}

void Level::lectureFichier(const string & nFichier){
    ifstream fichier(nFichier);
    vector<string> vMot;
    string str;                                            //Represente la ligne de texte

    try{

    while (getline(fichier, str))                          //lectures de lignes du fichier jusqu'a la dernier.
    {
        vMot.push_back(str);                               //mettre dans le vector.
        string buf;                                        //avoir un buffer string
        stringstream ss(str);
        vector<string> tokens;                             //les lettres.

        while (ss >> buf){
             tokens.push_back(buf);
             //cout<<buf<<endl;
        }
        cout<<tokens.size()<<endl;
        if(tokens.size() > 0){
            switch(tokens[0][0]){
                case 'S':
                    cout<<tokens[0]<<endl;
                    src = new Source(Point(stoi(tokens[1]),stoi(tokens[2])),stoi(tokens[3]),
                            stod(tokens[4]),stoi(tokens[5]));
                    break;
                case 'D':
                    cout<<tokens[0]<<endl;
                    dest = new Dest(Point(stoi(tokens[1]),stoi(tokens[2])),stoi(tokens[3]));
                    break;
                case 'C':
                    cout<<tokens[0]<<endl;
                    crystals.push_back(new Crystal(Point(stoi(tokens[1]),stoi(tokens[2])),stod(tokens[3]),
                            stoi(tokens[4])));
                    break;
                case 'N':
                    cout<<tokens[0]<<endl;
                    nukes.push_back(new Nuke(Point(stoi(tokens[1]),stoi(tokens[2])),stoi(tokens[3])));
                    break;
                case 'L':
                    cout<<tokens[0]<<endl;
                    lenses.push_back(new Lens(Point(stoi(tokens[1]),stoi(tokens[2])),stoi(tokens[3]),
                            stoi(tokens[4]),stoi(tokens[5]),stoi(tokens[6])));
                    break;
                case 'W':
                    cout<<tokens[0]<<endl;
                    walls.push_back(new Wall(Point(stoi(tokens[1]),stoi(tokens[2])),
                            Point(stoi(tokens[3]),stoi(tokens[4]))));
                    break;
                case 'M':
                    if(tokens.size() > 5){
                        cout<<tokens[0]<<endl;
                        mirrors.push_back(new Mirror(Point(stoi(tokens[1]),stoi(tokens[2])),
                                stoi(tokens[3]),stoi(tokens[4]),stod(tokens[5]),
                                Point(stoi(tokens[6]),stoi(tokens[7])),Point(stoi(tokens[8]),stoi(tokens[9])),
                                stod(tokens[10]),stod(tokens[11])));
                    }else{
                        mirrors.push_back(new Mirror(Point(stoi(tokens[1]),stoi(tokens[2])),
                                stoi(tokens[3])/2,stoi(tokens[3]),stod(tokens[4]),
                                Point(0,0),Point(width,height),0,2*PI));
                    }
                    break;
                default :
                    cout<<tokens[0] << " " << tokens[1]<<endl;
                    break;
            }
        }
    }

    }catch(std::invalid_argument e){
        std::cout<<"error al convertir 1"<<std::endl;
        string msg{"error al convertir jjjj"};
        throw msg;
    }catch(std::out_of_range e){
        std::cout<<"error al convertir 2"<<std::endl;
        string msg{"error al convertir jjjj"};
        throw msg;
    }catch(std::exception e){
        std::cout<<"error al convertir 3"<<std::endl;
        string msg{"error al convertir jjjj"};
        throw msg;
    }catch(...){
        std::cout<<"error al convertir 4"<<std::endl;
        string msg{"error al convertir jjjj"};
        throw msg;
    }

    fichier.close();
}
