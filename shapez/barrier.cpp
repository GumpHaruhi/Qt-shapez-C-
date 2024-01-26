#include "barrier.h"

Barrier::Barrier(World* world, int arrx, int arry, QString name)
    :MapPoint(world, arrx, arry, name){
    block = true;
}

bool Barrier::is_center(){
    return false;
}

QString& Barrier::getName(){
    return name;
}
