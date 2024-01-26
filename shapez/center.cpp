#include "center.h"

Center::Center(World* world, int arrx, int arry, QString name)
    :MapPoint(world, arrx, arry, name){
    block = false;
}

bool Center::is_center(){
    return true;
}

QString& Center::getName(){
    return name;
}
