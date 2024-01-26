#ifndef KUNPLACE_H
#define KUNPLACE_H
#include "mappoint.h"

class KunPlace: public MapPoint
{
public:
    KunPlace(World* world, int arrx, int arry);
    bool is_center();
    QString& getName();
};

#endif // KUNPLACE_H
