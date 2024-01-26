#ifndef FRUITCACK_H
#define FRUITCACK_H

#include "treasure.h"
#include <QObject>

class FruitCack: public Treasure
{
    Q_OBJECT

    QString name;
    static int value;
public:
    FruitCack(MapPoint* pos);
    ~FruitCack();

    QString& getName();
    bool can_cut();
    int getValue();
    void changeValue(int temp);
};

#endif // FRUITCACK_H
