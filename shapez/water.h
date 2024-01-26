#ifndef WATER_H
#define WATER_H

#include "treasure.h"
#include <QObject>

class Water: public Treasure
{
    Q_OBJECT

    QString name;
    static int value;
public:
    Water(MapPoint* pos);
    ~Water();

    QString& getName();
    int getValue();
    void changeValue(int temp);
};

#endif // WATER_H
