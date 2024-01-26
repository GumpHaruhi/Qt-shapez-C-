#ifndef WORLD_H
#define WORLD_H

#include "mappoint.h"

#include <QWidget>
#include <QTextStream>

class World
{
    QVector<QVector<MapPoint *>> my_map;
    int windowWidth = 1440;
    int windowHigh = 900;
    int gridSize = 45;
    int centerSize = 2;
    QPair<int, int> centerIndex;
    bool findCenter = false;

public:
    World();

    void addPoint(MapPoint* newpoint, int arrx, int arry);
    QVector<MapPoint *> centerArround();
    bool legalUP(int arrx, int arry);
    bool legalDOWN(int arrx, int arry);
    bool legalLEFT(int arrx, int arry);
    bool legalRIGHT(int arrx, int arry);
    MapPoint* get_Grid(QPoint& pos);
    MapPoint* get_Grid(QPair<int, int>& pos);
    MapPoint* get_UP(int arrx, int arry);
    MapPoint* get_DOWN(int arrx, int arry);
    MapPoint* get_LEFT(int arrx, int arry);
    MapPoint* get_RIGHT(int arrx, int arry);

    QTextStream& save_world(QTextStream& out);
};

#endif // WORLD_H
