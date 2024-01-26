#ifndef MAPPOINT_H
#define MAPPOINT_H

#include "basetool.h"
#include "treasure.h"
#include "DataZip.h"

#include <QObject>
#include <QPaintEvent>
#include <QPainter>
#include <QPoint>
#include <QSize>

class World;

class MapPoint
{
    QPoint m_pos;
    QString name;
    BaseTool* m_tool;
    Treasure* m_treasure;
    World* my_world;
    bool block = false;
    bool center = false;
    DataZip _zip;

public:
    MapPoint(World* world, int arrx, int arry, QString name);
    ~MapPoint();

    QPoint getPos();
    static const int pointSize = 45;
    MapPoint* get_UPpoint();
    MapPoint* get_DOWNpoint();
    MapPoint* get_LEFTpoint();
    MapPoint* get_RIGHTpoint();

    void addTool(BaseTool* newtool);
    void addTreasure(Treasure* newore);
    BaseTool* getTool();
    BaseTool* removeTool();
    Treasure* removeTreasure();
    void set_block();
    void free_block();
    bool is_block();
    bool is_center();
    bool is_barrier();
    QString& getName();
    void changeName(QString str);
    void make_center();
    bool has_tool();
    bool has_ore();
    bool can_addore();
    bool can_addtool();
    int arrx, arry;
    DataZip& getDataZip();
};

#endif // MAPPOINT_H
