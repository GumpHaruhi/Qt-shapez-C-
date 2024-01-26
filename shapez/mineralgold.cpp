#include "mineralgold.h"

MineralGold::MineralGold(World* world, int arrx, int arry)
    :MapPoint(world, arrx, arry){
    name = "goldfield";
}

bool MineralGold::is_center(){
    return false;
}

QString& MineralGold::getName(){
    return name;
}
