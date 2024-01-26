#ifndef CUTTER_H
#define CUTTER_H

#include "basetool.h"
#include <QObject>

class Cutter: public BaseTool
{
    Q_OBJECT

    MapPoint* with_pos;
    QVector<QString> direction = {"UP", "LEFT", "DOWN", "RIGHT"};

public:
    Cutter(MapPoint* point, MapPoint* with_grid, int index);
    ~Cutter();
    void deleself();
    Treasure* operate();
    QString& getName();
    QString getDirection();
    void changeDirection(int temp);
    MapPoint* getFirPos();
    MapPoint* getSecPos();
    int getType();
};

#endif // CUTTER_H
