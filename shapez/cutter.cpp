#include "cutter.h"
#include "mappoint.h"

Cutter::Cutter(MapPoint* point, MapPoint* with_grid, int index)
    :BaseTool(point, index){
    name = "cutter";
    with_pos = with_grid;
    with_pos->set_block();
}

Cutter::~Cutter(){
    m_pos = nullptr;
    with_pos->free_block();
    with_pos = nullptr;
}

void Cutter::deleself(){
    with_pos->free_block();
}

Treasure* Cutter::operate(){
    return nullptr;
}

MapPoint* Cutter::getFirPos(){
    if(directionIndex == 0){
        return m_pos->get_UPpoint();
    }
    else if(directionIndex == 1){
        return m_pos->get_LEFTpoint();
    }
    else if(directionIndex == 2){
        return m_pos->get_DOWNpoint();
    }
    else{
        return m_pos->get_RIGHTpoint();
    }
}

MapPoint* Cutter::getSecPos(){
    if(with_pos == nullptr){
        return nullptr;
    }

    if(directionIndex == 0){
        return with_pos->get_UPpoint();
    }
    else if(directionIndex == 1){
        return with_pos->get_LEFTpoint();
    }
    else if(directionIndex == 2){
        return with_pos->get_DOWNpoint();
    }
    else{
        return with_pos->get_RIGHTpoint();
    }
}

QString& Cutter::getName(){
    return name;
}

QString Cutter::getDirection(){
    return direction[directionIndex];
}

void Cutter::changeDirection(int temp){
    MapPoint* beta = nullptr;
    directionIndex += temp;

    // beta 可能继续是空指针
    if(directionIndex == 1){
        beta = m_pos->get_UPpoint();
    }
    else if(directionIndex == 2){
        beta = m_pos->get_LEFTpoint();
    }
    else if(directionIndex == 3 || directionIndex == -1){
        beta = m_pos->get_DOWNpoint();
    }
    else if(directionIndex == 0 || directionIndex == 4){
        beta = m_pos->get_RIGHTpoint();
    }

    if(beta == nullptr || (beta->is_center() || beta->is_block() || beta->has_tool())){
        directionIndex -= temp;
        return;
    }

    if(directionIndex < 0){
        directionIndex = 3;
    }
    else if(directionIndex > 3){
        directionIndex = 0;
    }
    with_pos->free_block();
    with_pos = beta;
    with_pos->set_block();
}

int Cutter::getType(){
    return 2;
}
