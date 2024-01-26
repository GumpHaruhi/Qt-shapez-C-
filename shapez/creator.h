#ifndef CREATOR_H
#define CREATOR_H

#include "basetool.h"
#include <QObject>

class Creator: public BaseTool
{
    Q_OBJECT

    MapPoint* grid;
    QVector<QString> direction = {"UP", "LEFT", "DOWN", "RIGHT"};

public:
    Creator(MapPoint* point, int index);
    ~Creator();
    void deleself();
    Treasure* operate();
    QString& getName();
    QString getDirection();
    void changeDirection(int temp);
    int getType();
};

#endif // CREATOR_H
