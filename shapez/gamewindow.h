#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class GameWinow; }
QT_END_NAMESPACE

#include "ui_gamewindow.h"
#include "basetool.h"
#include "mappoint.h"
#include "treasure.h"
#include "world.h"
#include "soundplayer.h"

#include <QWidget>
#include <QAbstractItemModel>
#include <QPoint>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QPushButton>
#include <QToolBar>
#include <QLabel>
#include <QTimer>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMediaPlayer>

class GameWindow : public QMainWindow
{
    Q_OBJECT

    bool victory = false;
    int gridSize = 45;
    bool find_center = false;
    bool shopVisiable = true;
    bool magicVisiable = true;
    SoundPlayer* musicPlayer;

    // 任务与奖励
    int money = 0, goldmoney = 0, cackmoney = 0, fruitmoney = 0, fruitcackmoney = 0, chickenmoney = 0;
    int coin = 0, creatorLevel = 0, beltLevel = 0, cutterLevel = 0, centerLevel = 0;
    int assignRice[2] = {10, 20}; int assignCack[2] = {10, 20};
    int assignFruit[2] = {10, 20}; int assignChicken[2] = {5, 15};
    int assignRicePointer = 0, assignCackPointer = 0, assignFruitPointer = 0, assignChickPointer = 0;

    // 时间与速度属性
    int creatorSpeed = 2000;
    int beltSpeed = 1;
    int cutterSpeed = 3000;
    QTimer* creatorTimer;
    QTimer* beltTimer;
    QTimer* cutterTimer;
    QTimer* centerTimer;
    QTimer* mixerTimer;

    // 商店部件
    QWidget* shopWidget;
    QVBoxLayout *shopLayout;
    // 魔法棒组件
    QWidget* magicWidget;
    QHBoxLayout *magicLayout;
    int magicNum = 0;
    int minerNum = 0;

    QPoint centerPos;
    World* world;
    QString mouseToolBuilder;
    int preToolDirection = 0;
    inline int transDirIndex(int temp);
    QToolBar* toolbar;
    MapPoint* modeGrid;
    QVector<MapPoint *> my_map;
    QVector<MapPoint *> my_barrier;
    QVector<Treasure *> ores;
    QVector<BaseTool *> my_creator;
    QVector<BaseTool *> my_cutter;
    QVector<BaseTool *> my_belt;
    QVector<BaseTool *> my_trash;
    QVector<BaseTool *> my_kitchen;
    QVector<BaseTool *> my_mixer;

    void drawMap(QPainter&);
    void drawLowTool(QPainter&);
    void drawHighTool(QPainter&);
    void drawTreasure(QPainter&);
    void drawCenter(QPainter&);
    void drawMoney(QPainter&);
    void drawShop(QPainter&);
    void drawAssign(QPainter&);
    void paintEvent(QPaintEvent *);

    void mousePressEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);
    bool eventFilter(QObject *obj, QEvent *event);

    void buildCreator(MapPoint* grid, int direct);
    void buildCutter(MapPoint* grid, int direct);
    void buildBelt(MapPoint* grid, int direct);
    void buildTrash(MapPoint* grid, int direct);
    void buildKitchen(MapPoint* grid, int direct);
    void buildMixer(MapPoint* grid, int direct);
    void drawCreator(QPainter& painter, MapPoint* grid, QString& direction);
    void drawTrash(QPainter& painter, MapPoint* grid);
    void drawBelt(QPainter& painter, MapPoint* grid, QString& direction);
    void drawCutter(QPainter& painter, MapPoint* grid, QString& direction);
    void drawKitchen(QPainter& painter, MapPoint* grid, QString& direction);
    void drawMixer(QPainter& painter, MapPoint* grid, QString& direction);

    void changeGrid(MapPoint* oldgrid, QString newgrid);
    void removeBarrier(MapPoint* oldgrid);
    QTextStream& writeTool(QTextStream& out);

    QPixmap goldPath; QPixmap fruitcackPath; QPixmap cackPath; QPixmap waterPath;
    QPixmap fruitPath; QPixmap kunPath; QPixmap chickenPath; QPixmap noodlesPath;
    QPixmap creatorU; QPixmap creatorL; QPixmap creatorD; QPixmap creatorR;
    QPixmap cutterU; QPixmap cutterL; QPixmap cutterD; QPixmap cutterR;
    QPixmap kitchenU; QPixmap kitchenL; QPixmap kitchenD; QPixmap kitchenR;
    QPixmap mixerU; QPixmap mixerL; QPixmap mixerD; QPixmap mixerR;
    QPixmap beltUD; QPixmap beltUR; QPixmap beltUL;
    QPixmap beltLU; QPixmap beltLR; QPixmap beltLD;
    QPixmap beltDU; QPixmap beltDL; QPixmap beltDR;
    QPixmap beltRU; QPixmap beltRL; QPixmap beltRD;
    QPixmap trashPath; QPixmap barrierPath;

public:
    GameWindow(int mapArr[20][32], QWidget* parent=nullptr);
    GameWindow(QFile& file, QWidget* parent=nullptr);
    ~GameWindow();
    // Header:

private:
    Ui::GameWindow *ui;
    void initializeUI(Ui::GameWindow* ui);
    void initializeSHOP();
    void initializeTIME();

private slots:
    void updateGame();
    void updateBelt();
    void updateCutter();
    void updateCreator();
    void updateMixer();

    void upgradeBelt();
    void upgradeCutter();
    void upgradeCreator();
    void upgradeCenter();
    void upgradeMiner();
    void upgradeMagic();
    void upgradeRice();
    void upgradeCack();
    void upgradeFruit();
    void upgradeChick();
    void chose_magicRice();
    void chose_magicCack();
    void chose_magicKun();

    void creatorPushButton();
    void cutterPushButton();
    void beltPushButton();
    void trashPushButton();
    void kitchenPushButton();
    void shopPushButton();
    void magicPushButton();
    void minerPushButton();
    void mixerPushButton();
    void savePushButton();
};

#endif // GAMEWINDOW_H
