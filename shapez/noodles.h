#ifndef NOODLES_H
#define NOODLES_H

#include "treasure.h"
#include <QObject>

class Noodles: public Treasure
{
    Q_OBJECT

    QString name;
    static int value;
public:
    Noodles(MapPoint* pos);
    ~Noodles();

    QString& getName();
    int getValue();
    void changeValue(int temp);
};

#endif // NOODLES_H
