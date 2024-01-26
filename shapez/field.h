#ifndef FIELD_H
#define FIELD_H
#include "mappoint.h"

class Field: public MapPoint
{
public:
    Field(World* world, int arrx, int arry);
    bool is_center();
    QString& getName();
};

#endif // FIELD_H
