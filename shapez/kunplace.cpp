#include "kunplace.h"

KunPlace::KunPlace(World* world, int arrx, int arry)
    :MapPoint(world, arrx, arry){
    name = "kunplace";
}

bool KunPlace::is_center(){
    return false;
}

QString& KunPlace::getName(){
    return name;
}
