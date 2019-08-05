#include "objectStar.h"

int objectStar::counter = 0;

objectStar::objectStar() {
    name = "UNKNOWN";
}

objectStar::objectStar(string Onename) {
    name = Onename;
    ++counter;// pour savoir quand un objet est touché
    index = counter;
}

Ray * objectStar::strike(Ray *& ray,Point p){
    return nullptr;
}

string objectStar::getName() {
     return name;
}

int objectStar::getIndex() {
     return index;
}
