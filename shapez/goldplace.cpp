#include "goldplace.h"

GoldPlace::GoldPlace(World* world, int arrx, int arry, QString name)
    :MapPoint(world, arrx, arry, name){
}

bool GoldPlace::is_center(){
    return false;
}

QString& GoldPlace::getName(){
    return name;
}
