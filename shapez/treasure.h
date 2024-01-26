#ifndef TREASURE_H
#define TREASURE_H

#include <QObject>
#include <QPoint>
#include <QPaintEvent>
#include <QPainter>
#include "basetool.h"

class MapPoint;

class Treasure: public QObject {
    Q_OBJECT
protected:
    MapPoint* m_pos;
    MapPoint* goalgrid;
    QPoint currentPos;
    QPoint destinyPos;

public:
    Treasure(MapPoint* point);
    ~Treasure();

    MapPoint* getPos();
    QPoint& getPixelPos();
    virtual int getValue() = 0;
    virtual void changeValue(int temp) = 0;
    bool move(int speed);
    bool is_arrival();
    void getRemove();
    virtual bool can_cut();
    BaseTool* check_tool();
    bool on_center();
    virtual QString& getName() = 0;
};

#endif // TREASURE_H
