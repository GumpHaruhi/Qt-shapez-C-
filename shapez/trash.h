#ifndef TRASH_H
#define TRASH_H

#include "basetool.h"
#include <QObject>

class Trash: public BaseTool
{
    Q_OBJECT
public:
    Trash(MapPoint* point, int index);
    ~Trash();
    void deleself();
    Treasure* operate();
    QString& getName();
    QString getDirection();
    void changeDirection(int temp);
    int getType();
};

#endif // TRASH_H
