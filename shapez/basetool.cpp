#include "basetool.h"
#include "mappoint.h"

BaseTool::BaseTool(MapPoint* point, int index)
    :m_pos(point), directionIndex(index){
    arrx = m_pos->arrx;
    arry = m_pos->arry;
}

MapPoint* BaseTool::getPos(){
    return m_pos;
}

MapPoint* BaseTool::getFirPos(){
    return nullptr;
}

MapPoint* BaseTool::getSecPos(){
    return nullptr;
}

MapPoint* BaseTool::getCreatPos(){
    return nullptr;
}

int BaseTool::getDirectionIndex(){
    return directionIndex;
}

int BaseTool::getBenefit(){
    return 0;
}

Treasure* BaseTool::mixPush(){
    return nullptr;
}

void BaseTool::recieveOre(Treasure* ore){
    return;
}

int BaseTool::arr_x(){
    return arrx;
}

int BaseTool::arr_y(){
    return arry;
}

BaseTool::~BaseTool(){
    m_pos = nullptr;
}
