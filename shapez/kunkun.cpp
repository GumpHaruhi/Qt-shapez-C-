#include "kunkun.h"

Kunkun::Kunkun(MapPoint* pos)
    :Treasure(pos){
    name = "kunkun";
}

int Kunkun::value = -5;

QString& Kunkun::getName(){
    return name;
}

int Kunkun::getValue(){
    return value;
}

void Kunkun::changeValue(int temp){
    value += temp;
}

Kunkun::~Kunkun(){

}
