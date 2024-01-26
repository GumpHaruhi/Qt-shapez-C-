#include "mappoint.h"
#include "world.h"

MapPoint::MapPoint(World* world, int arrx, int arry, QString name)
    :name(name), my_world(world) {
    m_pos.setX(arry * 45);
    m_pos.setY(arrx * 45);
    m_tool = nullptr;
    m_treasure = nullptr;
    this->arrx = arrx;
    this->arry = arry;
    _zip.arr_x = arrx;
    _zip.arr_y = arry;
    _zip.gridtype = name;
    if(name == "barrier"){
        block = true;
    }
}

DataZip& MapPoint::getDataZip(){
    _zip.gridtype = name;
    return _zip;
}

QPoint MapPoint::getPos(){ // 这个获得的是像素坐标
    return m_pos;
}

MapPoint* MapPoint::get_UPpoint(){
    return my_world->get_UP(arrx, arry);
}

MapPoint* MapPoint::get_DOWNpoint(){
    return my_world->get_DOWN(arrx, arry);
}

MapPoint* MapPoint::get_LEFTpoint(){
    return my_world->get_LEFT(arrx, arry);
}

MapPoint* MapPoint::get_RIGHTpoint(){
    return my_world->get_RIGHT(arrx, arry);
}

QString& MapPoint::getName(){
    return name;
}

void MapPoint::addTool(BaseTool* newtool){
    if(!this->is_center() && !this->has_tool() && !this->block){
        m_tool = newtool;
    }
}

void MapPoint::addTreasure(Treasure* newore){
    if(!this->is_center() && !this->block){
        m_treasure = newore;
    }
}

BaseTool* MapPoint::getTool(){
    if(m_tool){
        return m_tool;
    }
    return nullptr;
}

BaseTool* MapPoint::removeTool(){
    BaseTool* tool = m_tool;
    m_tool = nullptr;
    block = false;
    return tool;
}

Treasure* MapPoint::removeTreasure(){
    Treasure* ore = m_treasure;
    m_treasure = nullptr;
    return ore;
}

bool MapPoint::has_tool(){
    if(m_tool){
        return true;
    }
    return false;
}

bool MapPoint::has_ore(){
    if(m_treasure){
        return true;
    }
    return false;
}

bool MapPoint::is_center(){
    return center;
}

bool MapPoint::is_block(){
    return block;
}

bool MapPoint::is_barrier(){
    return name == "barrier";
}

bool MapPoint::can_addore(){
    return this->is_center() || block || m_treasure;
}

bool MapPoint::can_addtool(){
    return this->is_center() || block || m_tool;
}

void MapPoint::set_block(){
    block = true;
}

void MapPoint::free_block(){
    block = false;
}

void MapPoint::make_center(){
    center = true;
}

void MapPoint::changeName(QString str){
    if(!is_center())  name = str;
}

MapPoint::~MapPoint(){
    m_tool = nullptr;
    m_treasure = nullptr;
    my_world = nullptr;
}
