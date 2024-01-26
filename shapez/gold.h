#ifndef GOLD_H
#define GOLD_H

#include "treasure.h"
#include <QObject>

class Gold: public Treasure
{
    Q_OBJECT

    QString name;
    static int value;
public:
    Gold(MapPoint* pos);
    ~Gold();

    QString& getName();
    int getValue();
    void changeValue(int temp);
};

#endif // GOLD_H
