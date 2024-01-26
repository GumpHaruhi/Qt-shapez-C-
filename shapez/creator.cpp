#include "creator.h"
#include "mappoint.h"
#include "gold.h"
#include "fruitcack.h"
#include "kunkun.h"
#include "water.h"

Creator::Creator(MapPoint* point, int index)
    :BaseTool(point, index){
    name = "creator";
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

Creator::~Creator(){
    m_pos = nullptr;
    grid = nullptr;
}

void Creator::deleself(){
    m_pos = nullptr;
    grid = nullptr;
}

Treasure* Creator::operate(){
    if(grid == nullptr || grid->can_addore()){
        return nullptr;
    }

    Treasure* ore = nullptr;
    QString posname = m_pos->getName();
    if(posname == "goldplace"){
        ore = new Gold(grid);
    }
    else if(posname == "cackplace"){
        ore = new FruitCack(grid);
    }
    else if(posname == "kunplace"){
        ore = new Kunkun(grid);
    }
    else if(posname == "waterplace"){
        ore = new Water(grid);
    }
    return ore;
}

QString& Creator::getName(){
    return name;
}

QString Creator::getDirection(){
    return direction[directionIndex];
}

void Creator::changeDirection(int temp){
    directionIndex += temp;
    if(directionIndex > 3){
        directionIndex = 0;
    }
    else if(directionIndex < 0){
        directionIndex = 3;
    }

    // grid 的新值可能是空指针，比如在地图越限的情况下
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

int Creator::getType(){
    return 1;
}
