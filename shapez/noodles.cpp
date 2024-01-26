#include "noodles.h"

Noodles::Noodles(MapPoint* pos)
    :Treasure(pos){
    name = "noodles";
}

int Noodles::value = 10;

QString& Noodles::getName(){
    return name;
}

int Noodles::getValue(){
    return value;
}

void Noodles::changeValue(int temp){
    value += temp;
}

Noodles::~Noodles(){

}
