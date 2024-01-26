#ifndef KUNKUN_H
#define KUNKUN_H

#include "treasure.h"
#include <QObject>

class Kunkun: public Treasure
{
    Q_OBJECT

    QString name;
    static int value;
public:
    Kunkun(MapPoint* pos);
    ~Kunkun();

    QString& getName();
    int getValue();
    void changeValue(int temp);
};

#endif // KUNKUN_H
