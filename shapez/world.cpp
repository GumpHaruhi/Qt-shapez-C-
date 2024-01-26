#include "world.h"
#include <QDebug>

World::World() {
    my_map.resize(20);
    for(int i=0;i < 20;++i){
        my_map[i].resize(32);
    }
}

void World::addPoint(MapPoint* newpoint, int arrx, int arry){
    my_map[arrx][arry] = newpoint;
    if(!findCenter && newpoint->is_center()){
        centerIndex.first = arrx;
        centerIndex.second = arry;
        findCenter = true;
    }
}

MapPoint* World::get_Grid(QPoint& pos){
    int arry = (pos.x() - pos.x() % gridSize) / gridSize;
    int arrx = (pos.y() - pos.y() % gridSize) / gridSize;
    if(arry >= 0 && arry < 32 && arrx >= 0 && arrx < 20){
        return my_map[arrx][arry];
    }
    else{
        qDebug() << " 格子超限 ";
        return nullptr;
    }
}

MapPoint* World::get_Grid(QPair<int, int>& pos){
    return my_map[pos.first][pos.second];
}

bool World::legalUP(int arrx, int arry){
    return arrx > 0;
}

bool World::legalDOWN(int arrx, int arry){
    return arrx < my_map.size()-1;
}

bool World::legalLEFT(int arrx, int arry){
    return arry > 0;
}

bool World::legalRIGHT(int arrx, int arry){
    return arry < my_map[0].size()-1;
}

MapPoint* World::get_UP(int arrx, int arry){
    if(arrx > 0){
        return my_map[arrx-1][arry];
    }
    return nullptr;
}

MapPoint* World::get_DOWN(int arrx, int arry){
    if(arrx < my_map.size()-1){
        return my_map[arrx+1][arry];
    }
    return nullptr;
}

MapPoint* World::get_LEFT(int arrx, int arry){
    if(arry > 0){
        return my_map[arrx][arry-1];
    }
    return nullptr;
}

MapPoint* World::get_RIGHT(int arrx, int arry){
    if(arry < my_map[0].size()-1){
        return my_map[arrx][arry+1];
    }
    return nullptr;
}

QTextStream& World::save_world(QTextStream& out){
    for(int i=0;i < 20;++i){
        for(int j=0;j < 32;++j){
            DataZip _zip = my_map[i][j]->getDataZip();
            out << 'g' << " " << _zip.arr_x << " " << _zip.arr_y << " " << _zip.gridtype << Qt::endl;
        }
    }

    return out;
}

QVector<MapPoint*> World::centerArround(){
    QVector<MapPoint *> grids;
    grids.push_back(my_map[centerIndex.first-1][centerIndex.second-1]);
    grids.push_back(my_map[centerIndex.first-1][centerIndex.second]);
    grids.push_back(my_map[centerIndex.first-1][centerIndex.second+1]);
    grids.push_back(my_map[centerIndex.first-1][centerIndex.second+2]);
    grids.push_back(my_map[centerIndex.first][centerIndex.second-1]);
    grids.push_back(my_map[centerIndex.first][centerIndex.second+2]);
    grids.push_back(my_map[centerIndex.first+1][centerIndex.second-1]);
    grids.push_back(my_map[centerIndex.first+1][centerIndex.second+2]);
    grids.push_back(my_map[centerIndex.first+2][centerIndex.second-1]);
    grids.push_back(my_map[centerIndex.first+2][centerIndex.second]);
    grids.push_back(my_map[centerIndex.first+2][centerIndex.second+1]);
    grids.push_back(my_map[centerIndex.first+2][centerIndex.second+2]);
    return grids;
}
