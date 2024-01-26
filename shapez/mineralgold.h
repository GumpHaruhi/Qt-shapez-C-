#ifndef MINERALGOLD_H
#define MINERALGOLD_H
#include "mappoint.h"

class MineralGold: public MapPoint
{
public:
    MineralGold(World* world, int arrx, int arry);
    bool is_center();
    QString& getName();
};

#endif // MINERALGOLD_H
