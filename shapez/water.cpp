#include "water.h"

Water::Water(MapPoint* pos)
    :Treasure(pos){
    name = "water";
}

int Water::value = 0;

QString& Water::getName(){
    return name;
}

int Water::getValue(){
    return value;
}

void Water::changeValue(int temp){
    return;
}

Water::~Water(){

}
