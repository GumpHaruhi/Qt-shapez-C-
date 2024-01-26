#include "fruitcack.h"

FruitCack::FruitCack(MapPoint* pos)
    :Treasure(pos){
    name = "fruitcack";
}

int FruitCack::value = 1;

QString& FruitCack::getName(){
    return name;
}

bool FruitCack::can_cut(){
    return true;
}

int FruitCack::getValue(){
    return value;
}

void FruitCack::changeValue(int temp){
    value += temp;
}

FruitCack::~FruitCack(){

}
