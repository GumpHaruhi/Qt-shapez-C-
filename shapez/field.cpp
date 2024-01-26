#include "field.h"

Field::Field(World* world, int arrx, int arry)
    :MapPoint(world, arrx, arry){
    name = "field";
}

bool Field::is_center(){
    return false;
}

QString& Field::getName(){
    return name;
}
