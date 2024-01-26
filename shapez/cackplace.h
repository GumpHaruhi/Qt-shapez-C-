#ifndef CACKPLACE_H
#define CACKPLACE_H
#include "mappoint.h"

class CackPlace: public MapPoint
{
public:
    CackPlace(World* world, int arrx, int arry);
    bool is_center();
    QString& getName();
};

#endif // CACKPLACE_H
