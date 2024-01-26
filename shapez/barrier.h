#ifndef BARRIER_H
#define BARRIER_H
#include "mappoint.h"

class Barrier: public MapPoint
{
public:
    Barrier(World* world, int arrx, int arry, QString name);
    bool is_center();
    QString& getName();
};

#endif // BARRIER_H
