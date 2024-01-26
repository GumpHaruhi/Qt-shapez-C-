#include "kitchen.h"
#include "mappoint.h"

Kitchen::Kitchen(MapPoint* point, int index)
    :BaseTool(point, index){
    name = "kitchen";
    if(index == 0){
        grid = m_pos->get_UPpoint();
    }
    else if(index == 1){
        grid = m_pos->get_LEFTpoint();
    }
    else if(index == 2){
        grid = m_pos->get_DOWNpoint();
    }
    else{
        grid = m_pos->get_RIGHTpoint();
    }
}

Kitchen::~Kitchen(){
    m_pos = nullptr;
    grid = nullptr;
}

void Kitchen::deleself(){
    m_pos = nullptr;
    grid = nullptr;
}

Treasure* Kitchen::operate(){
    return nullptr;
}

QString& Kitchen::getName(){
    return name;
}

int Kitchen::getBenefit(){
    return benefit;
}

QString Kitchen::getDirection(){
    return direction[directionIndex];
}

void Kitchen::changeDirection(int temp){
    directionIndex += temp;
    if(directionIndex > 3){
        directionIndex = 0;
    }
    else if(directionIndex < 0){
        directionIndex = 3;
    }

    if(directionIndex == 0){
        grid = m_pos->get_UPpoint();
    }
    else if(directionIndex == 1){
        grid = m_pos->get_LEFTpoint();
    }
    else if(directionIndex == 2){
        grid = m_pos->get_DOWNpoint();
    }
    else{
        grid = m_pos->get_RIGHTpoint();
    }
}

MapPoint* Kitchen::getCreatPos(){
    return grid;
}

int Kitchen::getType(){
    return 5;
}
