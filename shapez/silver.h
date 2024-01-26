#ifndef SILVER_H
#define SILVER_H

#include "treasure.h"
#include <QObject>

class Silver: public Treasure
{
    Q_OBJECT

    QString name;
public:
    Silver(MapPoint* pos);
    ~Silver();

    void getCut();
    QString& getNmae();
};

#endif // SILVER_H
