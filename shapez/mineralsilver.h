#ifndef MINERALSILVER_H
#define MINERALSILVER_H
#include "mappoint.h"

class MineralSilver: public MapPoint
{
public:
    MineralSilver(World* world, int arrx, int arry);
    bool is_center();
    QString& getName();
};


#endif // MINERALSILVER_H
