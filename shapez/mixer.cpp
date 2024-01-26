#include "mixer.h"
#include "mappoint.h"
#include "noodles.h"

Mixer::Mixer(MapPoint *point, int index)
    :BaseTool(point, index){
    name = "mixer";
    riceNum = 0; breadNum = 0; waterNum = 0;
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

Mixer::~Mixer(){
    m_pos = nullptr;
    grid = nullptr;
}

void Mixer::deleself(){
    m_pos = nullptr;
    grid = nullptr;
}

void Mixer::recieveOre(Treasure* ore){
    if(ore == nullptr){ return ; }
    QString orename = ore->getName();
    if(orename == "gold"){
        riceNum = riceNum == 2 ? 2 : riceNum+1;
    }
    else if(orename == "cack"){
        breadNum = breadNum == 2 ? 2 : breadNum+1;
    }
    else if(orename == "water"){
        waterNum = waterNum > 6 ? 6 : waterNum +1;
    }
}

Treasure* Mixer::mixPush(){
    if(grid != nullptr && !grid->can_addore() && riceNum > 0 && breadNum > 0 && waterNum >= 3){
        riceNum--; breadNum--; waterNum -= 3;
        Treasure* ore = new Noodles(grid);
        return ore;
    }
    return nullptr;
}

Treasure* Mixer::operate(){
    return nullptr;
}

QString& Mixer::getName(){
    return name;
}

QString Mixer::getDirection(){
    return direction[directionIndex];
}

void Mixer::changeDirection(int temp){
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

int Mixer::getType(){
    return 6;
}
