#include "mineralsilver.h"

MineralSilver::MineralSilver(World* world, int arrx, int arry)
    :MapPoint(world, arrx, arry){
    name = "silverfield";
}

bool MineralSilver::is_center(){
    return false;
}

QString& MineralSilver::getName(){
    return name;
}
