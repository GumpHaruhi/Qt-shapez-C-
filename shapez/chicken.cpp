#include "chicken.h"

Chicken::Chicken(MapPoint* pos)
    :Treasure(pos){
    name = "chicken";
}

int Chicken::value = 1;

QString& Chicken::getName(){
    return name;
}

int Chicken::getValue(){
    return value;
}

void Chicken::changeValue(int temp){
    value += temp;
}

Chicken::~Chicken(){

}
