#ifndef CACK_H
#define CACK_H

#include "treasure.h"
#include <QObject>

class Cack: public Treasure
{
    Q_OBJECT

    QString name;
    static int value;
public:
    Cack(MapPoint* pos);
    ~Cack();

    QString& getName();
    int getValue();
    void changeValue(int temp);
};

#endif // CACK_H
