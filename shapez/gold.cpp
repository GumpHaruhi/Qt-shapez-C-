#include "gold.h"

Gold::Gold(MapPoint* pos)
    :Treasure(pos) {
    name = "gold";
}

int Gold::value = 1;

QString& Gold::getName(){
    return name;
}

int Gold::getValue(){
    return value;
}

void Gold::changeValue(int temp){
    value += temp;
}

Gold::~Gold(){

}
