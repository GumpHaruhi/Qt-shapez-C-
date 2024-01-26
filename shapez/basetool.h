#ifndef BASETOOL_H
#define BASETOOL_H

#include <QObject>
#include <QPoint>
#include <QPaintEvent>
#include <QPainter>
#include <QString>

class MapPoint;
class Treasure;

class BaseTool: public QObject
{
    Q_OBJECT

protected:
    MapPoint* m_pos;
    QString name;
    int directionIndex;
    int arrx, arry;

public:
    BaseTool(MapPoint* point, int index);
    virtual ~BaseTool();
    virtual void deleself() = 0;

    MapPoint* getPos();
    virtual Treasure* operate() = 0;
    virtual Treasure* mixPush();
    virtual QString& getName() = 0;
    virtual QString getDirection() = 0;
    int getDirectionIndex();
    virtual void changeDirection(int temp) = 0;
    virtual MapPoint* getFirPos();
    virtual MapPoint* getSecPos();
    virtual MapPoint* getCreatPos();
    virtual int getBenefit();
    virtual int getType() = 0;
    virtual void recieveOre(Treasure* ore);
    int arr_x();
    int arr_y();
};

#endif // BASETOOL_H
