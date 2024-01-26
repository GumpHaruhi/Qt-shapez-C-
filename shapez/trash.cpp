#include "trash.h"
#include "mappoint.h"

Trash::Trash(MapPoint* point, int index)
    :BaseTool(point, index){
    name = "trash";
}

Trash::~Trash(){
    m_pos = nullptr;
}

void Trash::deleself(){
    m_pos = nullptr;
}

Treasure* Trash::operate(){
    return nullptr;
}

QString& Trash::getName(){
    return name;
}

QString Trash::getDirection(){
    return "no direction";
}

void Trash::changeDirection(int temp){
    return;
}

int Trash::getType(){
    return 4;
}
