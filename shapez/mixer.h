#ifndef MIXER_H
#define MIXER_H

#include "basetool.h"
#include <QObject>

class Mixer: public BaseTool
{
    Q_OBJECT

    MapPoint* grid;
    int riceNum, breadNum, waterNum;
    QVector<QString> direction = {"UP", "LEFT", "DOWN", "RIGHT"};
public:
    Mixer(MapPoint* point, int index);
    ~Mixer();
    void deleself();
    Treasure* mixPush();
    Treasure* operate();
    QString& getName();
    QString getDirection();
    void changeDirection(int temp);
    int getType();
    void recieveOre(Treasure* ore);
};

#endif // MIXER_H
