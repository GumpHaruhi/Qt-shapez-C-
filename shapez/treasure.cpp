#include "treasure.h"
#include "mappoint.h"

Treasure::Treasure(MapPoint* point): m_pos(point) {
    if(point != nullptr){
        m_pos->addTreasure(this);
        goalgrid = point;
        currentPos = m_pos->getPos();
        destinyPos = currentPos;
    }
}

MapPoint* Treasure::getPos(){
    return m_pos;
}

QPoint& Treasure::getPixelPos(){
    return currentPos;
}

bool Treasure::is_arrival(){
    int k1, k2, k3;
    QPoint gridPos = m_pos->getPos();
    if(currentPos.x() != gridPos.x()){
        k1 = gridPos.x();
        k2 = currentPos.x();
        k3 = destinyPos.x();
    }
    else {
        k1 = gridPos.y();
        k2 = currentPos.y();
        k3 = destinyPos.y();
    }

    if((k2 >= k3 && k3 >= k1) || (k2 <= k3 && k3 <= k1)){
        return true;
    }
    return false;
}

bool Treasure::move(int speed){
    // 如果目标点和当前位置相同，需要更新一些属性
    if(this->is_arrival()){
        // 将位置更新
        m_pos->removeTreasure();
        m_pos = goalgrid;
        // 如果当前位置已经有货物了，出现货物重叠，则返回true，告诉gamewindow应该删除this
        if(m_pos->has_ore()){
            return true;
        }
        m_pos->addTreasure(this);
        // 获得当前所处格点上的工具，可能为空
        BaseTool* tool = m_pos->getTool();
        // 如果不是传送带或染色器，不做任何操作
        if(tool == nullptr || (tool->getName() != "belt" && tool->getName() != "kitchen")){
            return false;
        }

        // 获得传送带或染色器的朝向，并更新目标点 goalgrid
        QString direct = tool->getDirection();
        if(direct == "DU" || direct == "LU" || direct == "RU" || direct == "UP"){
            goalgrid = m_pos->get_UPpoint();
        }
        else if(direct == "RL" || direct == "UL" || direct == "DL" || direct == "LEFT"){
            goalgrid = m_pos->get_LEFTpoint();
        }
        else if(direct == "UD" || direct == "RD" || direct == "LD" || direct == "DOWN"){
            goalgrid = m_pos->get_DOWNpoint();
        }
        else if(direct == "LR" || direct == "UR" || direct == "DR" || direct == "RIGHT"){
            goalgrid = m_pos->get_RIGHTpoint();
        }

        // goalgrid 可能为空（超出地图界限），处理这种特殊情况
        if(goalgrid == nullptr || goalgrid->is_block() || goalgrid->has_ore()){
            goalgrid = m_pos;
            return false;
        }

        // 更新目标位置
        destinyPos = goalgrid->getPos();
    }

    // 实现“移动”，从当前位置向目标位置移动一步
    if(currentPos.x() == destinyPos.x()){
        int y0 = currentPos.y(), y1 = destinyPos.y();
        if(y0 < y1){
            currentPos.setY(y0 + speed);
        }
        else{
            currentPos.setY(y0 - speed);
        }
    }
    else{
        int x0 = currentPos.x(), x1 = destinyPos.x();
        if(x0 < x1){
            currentPos.setX(x0 + speed);
        }
        else{
            currentPos.setX(x0 - speed);
        }
    }
    return false;
}

void Treasure::getRemove(){
    m_pos->removeTreasure();
    this->~Treasure();
}

BaseTool* Treasure::check_tool(){
    return m_pos->getTool();
}

bool Treasure::on_center(){
    return m_pos->is_center();
}

bool Treasure::can_cut(){
    return false;
}

Treasure::~Treasure(){
    m_pos->removeTreasure();
    m_pos = nullptr;
}
