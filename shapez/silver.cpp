#include "silver.h"

Silver::Silver(MapPoint* pos)
    :Treasure(pos) {
    name = "silver";
    could_cut = false;
    had_cut = false;
    value = 1;
}

QString& Silver::getNmae(){
    return name;
}

void Silver::getCut(){

}
