#include "belt.h"
#include "mappoint.h"

Belt::Belt(MapPoint* point, int index)
    :BaseTool(point, index){
    name = "belt";
}

Belt::~Belt(){
    m_pos = nullptr;
}

void Belt::deleself(){
    m_pos = nullptr;
}

Treasure* Belt::operate(){
    return nullptr;
}

QString& Belt::getName(){
    return name;
}

QString Belt::getDirection(){
    return direction[directionIndex];
}

void Belt::changeDirection(int temp){
    directionIndex += temp;
    if(directionIndex > 11){
        directionIndex = 0;
    }
    else if(directionIndex < 0){
        directionIndex = 11;
    }
}

int Belt::getType(){
    return 3;
}
