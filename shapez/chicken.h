#ifndef CHICKEN_H
#define CHICKEN_H

#include "treasure.h"
#include <QObject>

class Chicken: public Treasure
{
    Q_OBJECT

    QString name;
    static int value;
public:
    Chicken(MapPoint* pos);
    ~Chicken();

    QString& getName();
    int getValue();
    void changeValue(int temp);
};

#endif // CHICKEN_H
