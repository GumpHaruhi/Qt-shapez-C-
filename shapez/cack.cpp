#include "cack.h"

Cack::Cack(MapPoint* pos)
    :Treasure(pos){
    name = "cack";
}

int Cack::value = 1;

QString& Cack::getName(){
    return name;
}

int Cack::getValue(){
    return value;
}

void Cack::changeValue(int temp){
    value += temp;
}

Cack::~Cack(){

}
