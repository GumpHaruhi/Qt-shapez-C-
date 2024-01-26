#include "cackplace.h"

CackPlace::CackPlace(World* world, int arrx, int arry)
    :MapPoint(world, arrx, arry){
    name = "cackplace";
}

bool CackPlace::is_center(){
    return false;
}

QString& CackPlace::getName(){
    return name;
}
