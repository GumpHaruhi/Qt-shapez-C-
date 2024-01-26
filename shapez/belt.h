#ifndef BELT_H
#define BELT_H

#include "basetool.h"
#include <QObject>

class Belt: public BaseTool
{
    Q_OBJECT

    QVector<QString> direction = {"UD","DU","LR","RL","UR","RU","RD","DR","DL","LD","LU","UL"};
public:
    Belt(MapPoint* point, int index);
    ~Belt();
    void deleself();
    Treasure* operate();
    QString& getName();
    QString getDirection();
    void changeDirection(int temp);
    int getType();
};

#endif // BELT_H
