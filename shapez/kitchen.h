#ifndef KITCHEN_H
#define KITCHEN_H

#include "basetool.h"
#include <QObject>

class Kitchen: public BaseTool
{
    Q_OBJECT

    MapPoint* grid;
    QVector<QString> direction = {"UP", "LEFT", "DOWN", "RIGHT"};
    int benefit = 1;

public:
    Kitchen(MapPoint* point, int index);
    ~Kitchen();
    void deleself();
    Treasure* operate();
    QString& getName();
    QString getDirection();
    void changeDirection(int temp);
    MapPoint* getCreatPos();
    int getBenefit();
    int getType();
};

#endif // KITCHEN_H
