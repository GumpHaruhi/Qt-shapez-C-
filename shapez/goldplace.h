#ifndef GOLDPLACE_H
#define GOLDPLACE_H
#include "mappoint.h"

class GoldPlace: public MapPoint
{
public:
    GoldPlace(World* world, int arrx, int arry, QString name);
    bool is_center();
    QString& getName();
};

#endif // GOLDPLACE_H
