#ifndef FRUIT_H
#define FRUIT_H

#include "treasure.h"
#include <QObject>

class Fruit: public Treasure
{
    Q_OBJECT

    QString name;
    static int value;
public:
    Fruit(MapPoint* pos);
    ~Fruit();

    QString& getName();
    int getValue();
    void changeValue(int temp);
};

#endif // FRUIT_H
