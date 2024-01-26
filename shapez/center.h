#ifndef CENTER_H
#define CENTER_H
#include "mappoint.h"

class Center: public MapPoint
{
public:
    Center(World* world, int arrx, int arry, QString name);
    bool is_center();
    QString& getName();
};


#endif // CENTER_H
