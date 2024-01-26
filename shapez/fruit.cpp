#include "fruit.h"

Fruit::Fruit(MapPoint* pos)
    :Treasure(pos){
    name = "fruit";
}

int Fruit::value = 1;

QString& Fruit::getName(){
    return name;
}

int Fruit::getValue(){
    return value;
}

void Fruit::changeValue(int temp){
    value += temp;
}

Fruit::~Fruit(){

}
