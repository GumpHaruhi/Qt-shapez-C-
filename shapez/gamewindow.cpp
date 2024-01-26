#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "gold.h"
#include "fruitcack.h"
#include "fruit.h"
#include "cack.h"
#include "kunkun.h"
#include "chicken.h"
#include "water.h"
#include "noodles.h"
#include "creator.h"
#include "cutter.h"
#include "belt.h"
#include "trash.h"
#include "kitchen.h"
#include "mixer.h"

#include <QTimer>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <QInputDialog>
#include <QFile>
#include <QCoreApplication>
#include <QDir>

// 新游戏
GameWindow::GameWindow(int mapArr[20][32], QWidget* parent)
    :QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    this->initializeUI(ui);

    this->initializeSHOP();

    // 加入事件过滤器
    this->installEventFilter(this);

    money = 0;
    victory = false;
    world = new World();
    mouseToolBuilder = nullptr;
    modeGrid = new MapPoint(world, -50, -50, "grid");

    for(int i=0;i < 20;++i){
        for(int j=0;j < 32;++j){
            if(mapArr[i][j] == 6){
                MapPoint* m_c = new MapPoint(world, i, j, "center");
                m_c->make_center();
                my_map.push_back(m_c);
                world->addPoint(m_c, i, j);
                if(!find_center){
                    centerPos.setX(j * gridSize);
                    centerPos.setY(i * gridSize);
                    find_center = true;
                }
            }
            else if(mapArr[i][j] == 1){
                MapPoint* m_g = new MapPoint(world, i, j, "goldplace");
                my_map.push_back(m_g);
                world->addPoint(m_g, i, j);
            }
            else if(mapArr[i][j] == 2){
                MapPoint* m_s = new MapPoint(world, i, j, "cackplace");
                my_map.push_back(m_s);
                world->addPoint(m_s, i, j);
            }
            else if(mapArr[i][j] == 0){
                MapPoint* m_f = new MapPoint(world, i, j, "field");
                my_map.push_back(m_f);
                world->addPoint(m_f, i, j);
            }
            else if(mapArr[i][j] == 3){
                MapPoint* m_b = new MapPoint(world, i, j, "barrier");
                my_map.push_back(m_b);
                my_barrier.push_back(m_b);
                world->addPoint(m_b, i, j);
            }
            else if(mapArr[i][j] == 4){
                MapPoint* m_k = new MapPoint(world, i, j, "kunplace");
                my_map.push_back(m_k);
                world->addPoint(m_k, i, j);
            }
            else if(mapArr[i][j] == 5){
                MapPoint* m_w = new MapPoint(world, i, j, "waterplace");
                my_map.push_back(m_w);
                world->addPoint(m_w, i, j);
            }
        }
    }

    this->initializeTIME();
}

// 读档
GameWindow::GameWindow(QFile& file, QWidget* parent)
    :QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    this->initializeUI(ui);

    this->initializeSHOP();

    // 加入事件过滤器
    this->installEventFilter(this);

    world = new World();
    mouseToolBuilder = nullptr;
    modeGrid = new MapPoint(world, -50, -50, "grid");

    // 打开文件，以只读方式
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // 创建 QTextStream 对象，并绑定到文件
        QTextStream in(&file);

        char tag;
        while(1){
            in >> tag;
            if(tag == '\n' || tag == '\r'){
                continue;
            }
            else if(tag == 'g'){
                QString type;  int x, y;
                in >> x >> y;  in >> type;
                MapPoint* grid = new MapPoint(world, x, y, type);
                if(type == "center"){
                    grid->make_center();
                    if(!find_center){
                        centerPos.setX(y * gridSize);
                        centerPos.setY(x * gridSize);
                        find_center = true;
                    }
                }
                else if(type == "barrier"){
                    my_barrier.push_back(grid);
                }
                my_map.push_back(grid);
                world->addPoint(grid, x, y);
            }
            else if(tag == 't'){
                int type, x, y, direct;
                in >>type >> x >> y >> direct;
                QPair<int, int> gpos(x, y);
                MapPoint* grid = world->get_Grid(gpos);
                switch(type){
                case(1):
                    buildCreator(grid, direct); break;
                case(2):
                    buildCutter(grid, direct); break;
                case(3):
                    buildBelt(grid, direct); break;
                case(4):
                    buildTrash(grid, direct); break;
                case(5):
                    buildKitchen(grid, direct); break;
                case(6):
                    buildMixer(grid, direct); break;
                default:
                    qDebug() << "error tool type: " << type;
                    break;
                }
            }
            else if(tag == 'o'){
                break;
            }
            else if(tag == 'c'){
                int level; in >> level;
                centerLevel = level;
            }
            else if(tag == 'm'){
                int m; in >> m;
                money = m;
            }
            else {
                qDebug() << "strange tag:" << tag;
                break;
            }
        }

        // 关闭文件
        file.close();

        this->initializeTIME();
    }
    else {
        // 打开文件失败，输出错误信息
        qDebug() << "Failed to open file: " << file.errorString();
    }
}

GameWindow::~GameWindow(){

}

void GameWindow::initializeUI(Ui::GameWindow* ui){
    ui->setupUi(this);
    setWindowTitle("就这？");
    setFixedSize(1440, 900);

    ui->creatorButton->setIcon(QIcon(":/image/miner.png"));
    ui->beltButton->setIcon(QIcon(":/image/belt.png"));
    ui->cutterButton->setIcon(QIcon(":/image/cutter.png"));
    ui->trashButton->setIcon(QIcon(":/image/trash.png"));
    ui->kitchenButton->setIcon(QIcon(":/image/16u.png"));
    ui->minerButton->setIcon(QIcon(":/image/analyzer.png"));
    ui->mixerButton->setIcon(QIcon(":/image/mU.png"));
    ui->shopButton->setIcon(QIcon(":/image/shop.png"));
    ui->magicButton->setIcon(QIcon(":/image/producer.png"));
    ui->saveButton->setIcon(QIcon(":/image/save.png"));
    ui->creatorButton->setIconSize(QSize(50, 50));
    ui->beltButton->setIconSize(QSize(50, 50));
    ui->cutterButton->setIconSize(QSize(50, 50));
    ui->trashButton->setIconSize(QSize(50, 50));
    ui->kitchenButton->setIconSize(QSize(50, 50));
    ui->minerButton->setIconSize(QSize(50, 50));
    ui->mixerButton->setIconSize(QSize(50, 50));
    ui->shopButton->setIconSize(QSize(60, 60));
    ui->magicButton->setIconSize(QSize(50, 50));
    ui->saveButton->setIconSize(QSize(30, 30));

    connect(ui->creatorButton, &QPushButton::clicked, this, &GameWindow::creatorPushButton);
    connect(ui->cutterButton, &QPushButton::clicked, this, &GameWindow::cutterPushButton);
    connect(ui->beltButton, &QPushButton::clicked, this, &GameWindow::beltPushButton);
    connect(ui->trashButton, &QPushButton::clicked, this, &GameWindow::trashPushButton);
    connect(ui->kitchenButton, &QPushButton::clicked, this, &GameWindow::kitchenPushButton);
    connect(ui->shopButton, &QPushButton::clicked, this, &GameWindow::shopPushButton);
    connect(ui->magicButton, &QPushButton::clicked, this, &GameWindow::magicPushButton);
    connect(ui->minerButton, &QPushButton::clicked, this, &GameWindow::minerPushButton);
    connect(ui->mixerButton, &QPushButton::clicked, this, &GameWindow::mixerPushButton);
    connect(ui->saveButton, &QPushButton::clicked, this, &GameWindow::savePushButton);

    // 图片加载
    goldPath.load(":/image/bw.png"); fruitcackPath.load(":/image/cack0.png");
    fruitPath.load(":/image/cack2.png"); cackPath.load(":/image/cack1.png");
    kunPath.load(":/image/ji.png");chickenPath.load(":/image/chicken.png");
    waterPath.load(":/image/water.png"); noodlesPath.load(":/image/noodles.png");
    creatorU.load(":/image/creatorU.png"); creatorL.load(":/image/creatorL.png");
    creatorD.load(":/image/creatorD.png"); creatorR.load(":/image/creatorR.png");
    cutterU.load(":/image/cutU.png"); cutterL.load(":/image/cutL.png");
    cutterD.load(":/image/cutD.png"); cutterR.load(":/image/cutR.png");
    kitchenU.load(":/image/16u.png"); kitchenL.load(":/image/16l.png");
    kitchenD.load(":/image/16d.png"); kitchenR.load(":/image/16r.png");
    mixerU.load(":/image/mU.png"); mixerL.load(":/image/mL.png");
    mixerD.load(":/image/mD.png"); mixerR.load(":/image/mR.png");
    beltUD.load(":/image/UD.png"); beltUR.load(":/image/UR.png"); beltUL.load(":/image/UL.png");
    beltLU.load(":/image/LU.png"); beltLR.load(":/image/LR.png"); beltLD.load(":/image/LD.png");
    beltDU.load(":/image/DU.png"); beltDL.load(":/image/DL.png"); beltDR.load(":/image/DR.png");
    beltRU.load(":/image/RU.png"); beltRL.load(":/image/RL.png"); beltRD.load(":/image/RD.png");
    trashPath.load(":/image/4.png"); barrierPath.load(":/image/block.png");

    // 播放音乐
    musicPlayer = new SoundPlayer;
}

void GameWindow::initializeSHOP(){
    // 商店的组件
    shopWidget = new QWidget(this);
    shopLayout = new QVBoxLayout(shopWidget);
    shopWidget->setFixedSize(200, 800);
    shopLayout->setSpacing(20);
    // 商店内的商品按钮
    QPushButton *shop_creatorButton = new QPushButton(shopWidget);
    shopLayout->addWidget(shop_creatorButton);
    shop_creatorButton->setFixedSize(50, 50);
    shop_creatorButton->setIcon(QIcon(":/image/miner.png"));
    shop_creatorButton->setIconSize(QSize(50, 50));

    QPushButton *shop_beltButton = new QPushButton(shopWidget);
    shopLayout->addWidget(shop_beltButton);
    shop_beltButton->setFixedSize(50, 50);
    shop_beltButton->setIcon(QIcon(":/image/belt.png"));
    shop_beltButton->setIconSize(QSize(50, 50));

    QPushButton *shop_cutterButton = new QPushButton(shopWidget);
    shopLayout->addWidget(shop_cutterButton);
    shop_cutterButton->setFixedSize(50, 50);
    shop_cutterButton->setIcon(QIcon(":/image/cutter.png"));
    shop_cutterButton->setIconSize(QSize(50, 50));

    QPushButton *shop_centerButton = new QPushButton(shopWidget);
    shopLayout->addWidget(shop_centerButton);
    shop_centerButton->setFixedSize(50, 50);
    shop_centerButton->setIcon(QIcon(":/image/center.png"));
    shop_centerButton->setIconSize(QSize(50, 50));

    QPushButton *shop_minerButton = new QPushButton(shopWidget);
    shopLayout->addWidget(shop_minerButton);
    shop_minerButton->setFixedSize(50, 50);
    shop_minerButton->setIcon(QIcon(":/image/analyzer.png"));
    shop_minerButton->setIconSize(QSize(50, 50));

    QPushButton *shop_magicButton = new QPushButton(shopWidget);
    shopLayout->addWidget(shop_magicButton);
    shop_magicButton->move(50, 50);
    shop_magicButton->setFixedSize(50, 50);
    shop_magicButton->setIcon(QIcon(":/image/producer.png"));
    shop_magicButton->setIconSize(QSize(50, 50));

    QPushButton *shop_riceButton = new QPushButton(shopWidget);
    shopLayout->addWidget(shop_riceButton);
    shop_riceButton->move(50, 50);
    shop_riceButton->setFixedSize(50, 50);
    shop_riceButton->setIcon(QIcon(":/image/bw.png"));
    shop_riceButton->setIconSize(QSize(50, 50));

    QPushButton *shop_cackButton = new QPushButton(shopWidget);
    shopLayout->addWidget(shop_cackButton);
    shop_cackButton->move(50, 50);
    shop_cackButton->setFixedSize(50, 50);
    shop_cackButton->setIcon(QIcon(":/image/cack0.png"));
    shop_cackButton->setIconSize(QSize(50, 50));

    QPushButton *shop_fruitButton = new QPushButton(shopWidget);
    shopLayout->addWidget(shop_fruitButton);
    shop_fruitButton->move(50, 50);
    shop_fruitButton->setFixedSize(50, 50);
    shop_fruitButton->setIcon(QIcon(":/image/cack2.png"));
    shop_fruitButton->setIconSize(QSize(50, 50));

    QPushButton *shop_chickButton = new QPushButton(shopWidget);
    shopLayout->addWidget(shop_chickButton);
    shop_chickButton->move(50, 50);
    shop_chickButton->setFixedSize(50, 50);
    shop_chickButton->setIcon(QIcon(":/image/chicken.png"));
    shop_chickButton->setIconSize(QSize(50, 50));

    shopLayout->addStretch();

    connect(shop_creatorButton, &QPushButton::clicked, this, &GameWindow::upgradeCreator);
    connect(shop_beltButton, &QPushButton::clicked, this, &GameWindow::upgradeBelt);
    connect(shop_cutterButton, &QPushButton::clicked, this, &GameWindow::upgradeCutter);
    connect(shop_centerButton,  &QPushButton::clicked, this, &GameWindow::upgradeCenter);
    connect(shop_minerButton,  &QPushButton::clicked, this, &GameWindow::upgradeMiner);
    connect(shop_magicButton,  &QPushButton::clicked, this, &GameWindow::upgradeMagic);
    connect(shop_riceButton,  &QPushButton::clicked, this, &GameWindow::upgradeRice);
    connect(shop_cackButton,  &QPushButton::clicked, this, &GameWindow::upgradeCack);
    connect(shop_fruitButton,  &QPushButton::clicked, this, &GameWindow::upgradeFruit);
    connect(shop_chickButton,  &QPushButton::clicked, this, &GameWindow::upgradeChick);

    // 魔法棒的组件
    magicWidget = new QWidget(this);
    magicLayout = new QHBoxLayout(magicWidget);
    magicWidget->setFixedSize(150, 50);
    magicWidget->setGeometry(720, 700, 150, 50);
    magicLayout->setSpacing(5);

    QPushButton *magic_Rice = new QPushButton(magicWidget);
    magicLayout->addWidget(magic_Rice);
    magic_Rice->setFixedSize(40, 40);
    magic_Rice->setIcon(QIcon(":/image/bw.png"));
    magic_Rice->setIconSize(QSize(40, 40));

    QPushButton *magic_Cack = new QPushButton(magicWidget);
    magicLayout->addWidget(magic_Cack);
    magic_Cack->setFixedSize(40, 40);
    magic_Cack->setIcon(QIcon(":/image/cack0.png"));
    magic_Cack->setIconSize(QSize(40, 40));

    QPushButton *magic_Kun = new QPushButton(magicWidget);
    magicLayout->addWidget(magic_Kun);
    magic_Kun->setFixedSize(40, 40);
    magic_Kun->setIcon(QIcon(":/image/ji.png"));
    magic_Kun->setIconSize(QSize(40, 40));

    magicWidget->setLayout(magicLayout);

    connect(magic_Rice, &QPushButton::clicked, this, &GameWindow::chose_magicRice);
    connect(magic_Cack, &QPushButton::clicked, this, &GameWindow::chose_magicCack);
    connect(magic_Kun, &QPushButton::clicked, this, &GameWindow::chose_magicKun);

}

void GameWindow::initializeTIME(){
    // 交付中心和垃圾桶的刷新时间不应该受任何影响（交付中心的刷新时间应该很快，非常快）
    centerTimer = new QTimer(this);
    connect(centerTimer, &QTimer::timeout, this, &GameWindow::updateGame);
    centerTimer->setInterval(20);
    centerTimer->start();

    // 生产者应该拥有自己的独立时间
    creatorTimer = new QTimer(this);
    connect(creatorTimer, &QTimer::timeout, this, &GameWindow::updateCreator);
    // 每两秒排出一个货物
    creatorTimer->setInterval(3000);
    creatorTimer->start();

    beltTimer = new QTimer(this);
    // 连接QTimer的timeout信号到更新游戏的槽函数
    connect(beltTimer, &QTimer::timeout, this, &GameWindow::updateBelt);
    beltTimer->setInterval(20);
    beltTimer->start();

    cutterTimer = new QTimer(this);
    connect(cutterTimer, &QTimer::timeout, this, &GameWindow::updateCutter);
    cutterTimer->setInterval(3000);
    cutterTimer->start();

    mixerTimer = new QTimer(this);
    connect(mixerTimer, &QTimer::timeout, this, &GameWindow::updateMixer);
    mixerTimer->setInterval(3000);
    mixerTimer->start();

}


/****************** 绘制事件 ********************/

void GameWindow::drawMap(QPainter& painter){
    QPen pen(Qt::gray, 2);
    painter.setPen(pen);
    for(int i=0;i <= 900;){
        painter.drawLine(0, i, 1440, i);
        i += gridSize;
    }
    for(int j=0;j <= 1440;){
        painter.drawLine(j, 0, j, 900);
        j += gridSize;
    }

    for(auto point: my_map){
        if(!point->is_center()){
            QString name = point->getName();
            if(name == "goldplace"){
                painter.drawPixmap(point->getPos().x(), point->getPos().y(), gridSize, gridSize, goldPath);
            }
            else if(name == "cackplace"){
                painter.drawPixmap(point->getPos().x(), point->getPos().y(), gridSize, gridSize, fruitcackPath);
            }
            else if(name == "kunplace"){
                painter.drawPixmap(point->getPos().x(), point->getPos().y(), gridSize, gridSize, kunPath);
            }
            else if(name == "waterplace"){
                painter.drawPixmap(point->getPos().x(), point->getPos().y(), gridSize, gridSize, waterPath);
            }
        }
    }
}

void GameWindow::drawLowTool(QPainter& painter){
    for(BaseTool* tool : my_belt){
        QString direction = tool->getDirection();
        drawBelt(painter, tool->getPos(), direction);
    }
}

void GameWindow::drawHighTool(QPainter& painter){
    for(BaseTool* tool : my_creator){
        QString direction = tool->getDirection();
        drawCreator(painter, tool->getPos(), direction);
    }

    for(BaseTool* tool : my_cutter){
        QString direction = tool->getDirection();
        drawCutter(painter, tool->getPos(), direction);
    }

    for(BaseTool* tool : my_trash){
        drawTrash(painter, tool->getPos());
    }

    for(BaseTool* tool : my_kitchen){
        QString direction = tool->getDirection();
        drawKitchen(painter, tool->getPos(), direction);
    }

    for(BaseTool* tool : my_mixer){
        QString direction = tool->getDirection();
        drawMixer(painter, tool->getPos(), direction);
    }

    // 画屏障的地方放在这里比较美观
    for(MapPoint* stone : my_barrier){
        painter.drawPixmap(stone->getPos().x(), stone->getPos().y(), gridSize, gridSize, barrierPath);
    }
}

void GameWindow::drawTreasure(QPainter& painter){
    for(Treasure* ore: ores){
        QString name = ore->getName();
        QPoint pos = ore->getPixelPos();
        if(name == "gold"){
            painter.drawPixmap(pos.x(), pos.y(), gridSize, gridSize, goldPath);
        }
        else if(name == "fruitcack"){
            painter.drawPixmap(pos.x(), pos.y(), gridSize, gridSize, fruitcackPath);
        }
        else if(name == "fruit"){
            painter.drawPixmap(pos.x(), pos.y(), gridSize, gridSize, fruitPath);
        }
        else if(name == "cack"){
            painter.drawPixmap(pos.x(), pos.y(), gridSize, gridSize, cackPath);
        }
        else if(name == "kunkun"){
            painter.drawPixmap(pos.x(), pos.y(), gridSize, gridSize, kunPath);
        }
        else if(name == "chicken"){
            painter.drawPixmap(pos.x(), pos.y(), gridSize, gridSize, chickenPath);
        }
        else if(name == "water"){
            painter.drawPixmap(pos.x(), pos.y(), gridSize, gridSize, waterPath);
        }
        else if(name == "noodles"){
            painter.drawPixmap(pos.x(), pos.y(), gridSize, gridSize, noodlesPath);
        }
    }
}

void GameWindow::drawCenter(QPainter& painter){
    if(centerLevel == 0){
        painter.drawPixmap(centerPos.x(), centerPos.y(), 2*gridSize, 2*gridSize, QPixmap(":/image/3-1.png"));
    }
    else{
        painter.drawPixmap(centerPos.x(), centerPos.y(), 4*gridSize, 4*gridSize, QPixmap(":/image/3.png"));
    }

    // 这里画出工具栏
    painter.setBrush(Qt::white);
    painter.drawEllipse(455, 750, 76, 76);
    painter.drawEllipse(895, 750, 76, 76);
    painter.drawRect(500, 750, 440, 76);
}

void GameWindow::drawMoney(QPainter& painter){
    // 设置文本颜色、字体等属性
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 12)); // 设置字体和大小

    // 绘制文本，将 money 绘制在左上角（0, 0）的位置
    painter.drawText(700, 410, QString("Money: %1").arg(money));
    painter.drawText(700, 430, QString("rice: %1").arg(goldmoney));
    painter.drawText(700, 450, QString("cack: %1").arg(fruitcackmoney));
    painter.drawText(700, 470, QString("bread: %1").arg(cackmoney));
    painter.drawText(700, 490, QString("fruit: %1").arg(fruitmoney));
    painter.drawText(700, 510, QString("chicken: %1").arg(chickenmoney));
}

void GameWindow::drawShop(QPainter& painter){
    QRect shopRect(0, 0, 200, 800);
    if(shopVisiable){
        painter.fillRect(shopRect, QColor(0, 0, 0, 100));

        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 15)); // 设置字体和大小

        // 绘制文本，将 money 绘制在左上角（0, 0）的位置
        painter.drawText(80, 40, QString("等级: %1 /2").arg(creatorLevel));
        painter.drawText(80, 110, QString("等级: %1 /1").arg(beltLevel));
        painter.drawText(80, 180, QString("等级: %1 /3").arg(cutterLevel));
        painter.drawText(80, 240, QString("价格： 150"));
        painter.drawText(80, 265, QString("等级： %1 /1").arg(centerLevel));
        painter.drawText(80, 310, QString("价格： 10"));
        painter.drawText(80, 335, QString("已有： %1").arg(minerNum));
        painter.drawText(80, 380, QString("价格： 10"));
        painter.drawText(80, 405, QString("已有： %1").arg(magicNum));
            Treasure* rice = new Gold(modeGrid); Treasure* cack = new FruitCack(modeGrid);
            Treasure* fruit = new Fruit(modeGrid); Treasure* chick = new Chicken(modeGrid);
        painter.drawText(80, 450, QString("价格： 50"));
        painter.drawText(80, 475, QString("价值： %1").arg(rice->getValue()));
        painter.drawText(80, 520, QString("价格： 50"));
        painter.drawText(80, 545, QString("价值： %1").arg(cack->getValue()));
        painter.drawText(80, 590, QString("价格： 50"));
        painter.drawText(80, 615, QString("价值： %1").arg(fruit->getValue()));
        painter.drawText(80, 660, QString("价格： 50"));
        painter.drawText(80, 685, QString("价值： %1").arg(chick->getValue()));

        painter.drawText(40, 730, QString("可升级次数: %1").arg(coin));
        painter.drawText(40, 770, QString("金币数: %1").arg(money));
    }

    if(magicVisiable){
        QRect magicRect(720, 700, 150, 50);
        painter.fillRect(magicRect, QColor(0, 0, 0, 100));
    }
}

void GameWindow::drawAssign(QPainter& painter){
    QRect assignRect(1200, 270, 250, 220);
    painter.fillRect(assignRect, QColor(0, 0, 0, 100));

    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 15)); // 设置字体和大小

    painter.drawText(1230, 300, QString("Your Assignment:"));
    painter.drawText(1250, 340, QString("米饭 : %1").arg(assignRice[assignRicePointer]));
    painter.drawText(1250, 380, QString("草莓蛋糕 : %1").arg(assignCack[assignCackPointer]));
    painter.drawText(1250, 420, QString("草莓 : %1").arg(assignFruit[assignFruitPointer]));
    painter.drawText(1250, 460, QString("只因 : %1").arg(assignChicken[assignChickPointer]));
}

void GameWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);

    drawMap(painter);
    drawLowTool(painter);
    drawTreasure(painter);
    drawHighTool(painter);
    drawCenter(painter);
    drawMoney(painter);
    drawShop(painter);
    drawAssign(painter);
}

/*******************   玩家交互   *********************/

void GameWindow::mousePressEvent(QMouseEvent *event){

    // 鼠标左键，建造工具
    if(event->button() == Qt::LeftButton){
        QPoint mousePos = event->pos();
        if(mouseToolBuilder != nullptr){
            MapPoint* grid = world->get_Grid(mousePos);
            if(mouseToolBuilder == "creator"){
                buildCreator(grid, preToolDirection);
            }
            else if(mouseToolBuilder == "cutter"){
                buildCutter(grid, preToolDirection);
            }
            else if(mouseToolBuilder == "belt"){
                buildBelt(grid, preToolDirection);
            }
            else if(mouseToolBuilder == "trash"){
                buildTrash(grid, preToolDirection);
            }
            else if(mouseToolBuilder == "kitchen"){
                buildKitchen(grid, preToolDirection);
            }
            else if(mouseToolBuilder == "magicRice"){
                changeGrid(grid, "rice");
            }
            else if(mouseToolBuilder == "magicCack"){
                changeGrid(grid, "cack");
            }
            else if(mouseToolBuilder == "magicKun"){
                changeGrid(grid, "kun");
            }
            else if(mouseToolBuilder == "miner"){
                removeBarrier(grid);
            }
            else if(mouseToolBuilder == "mixer"){
                buildMixer(grid, preToolDirection);
            }

            update();
        }
    }

    // 鼠标右键，拆除工具
    else if(event->button() == Qt::RightButton){
        QPoint mousePos = event->pos();
        MapPoint* grid = world->get_Grid(mousePos);
        BaseTool* tool = grid->removeTool();
        if(tool != nullptr){
            // 移除工具
            musicPlayer->removeTool();

            QString toolname = tool->getName();
            if(toolname == "creator"){
                my_creator.removeOne(tool);
            }
            else if(toolname == "cutter"){
                my_cutter.removeOne(tool);
            }
            else if(toolname == "belt"){
                my_belt.removeOne(tool);
            }
            else if(toolname == "trash"){
                my_trash.removeOne(tool);
            }
            else if(toolname == "kitchen"){
                my_kitchen.removeOne(tool);
            }
            else if(toolname == "mixer"){
                my_mixer.removeOne(tool);
            }
            tool->deleself();
            delete tool;
            tool = nullptr;

            update();
        }
    }

    QMainWindow::mousePressEvent(event);
}

void GameWindow::keyPressEvent(QKeyEvent *event){

}

bool GameWindow::eventFilter(QObject *obj, QEvent *event){
    if (event->type() == QEvent::KeyRelease) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

        // 键盘事件，Q E 正向反向旋转工具
        if (keyEvent->key() == Qt::Key_E || keyEvent->key() == Qt::Key_Q) {
            // 获取鼠标位置
            QPoint globalPos = QCursor::pos();
            QPoint mousePos = mapFromGlobal(globalPos);

            // 获取窗口的矩形区域
            QRect windowRect = rect();

            // 判断鼠标是否在窗口内
            if (windowRect.contains(mousePos)) {
                MapPoint* grid = world->get_Grid(mousePos);
                if(grid->has_tool()){
                    musicPlayer->spinTool();

                    BaseTool* tool = grid->getTool();
                    if(keyEvent->key() == Qt::Key_Q){
                        tool->changeDirection(1);
                    }
                    else{
                        tool->changeDirection(-1);
                    }
                    preToolDirection = this->transDirIndex(tool->getDirectionIndex());
                }
            } else {
                // 忽略窗口外的操作
                qDebug() << "Mouse position outside window, ignoring...";
            }

            return true; // 表示事件已处理
        }
    }

    return QObject::eventFilter(obj, event);
}

int GameWindow::transDirIndex(int temp){
    if(temp == 1 || temp == 5 || temp == 10){
        return 1;
    }
    else if(temp == 3 || temp == 8 || temp == 11){
        return 3;
    }
    else if(temp == 0 || temp == 6 || temp == 9){
        return 0;
    }
    else {
        return 2;
    }
}

/****************     SLOTS     ****************/

/**********  游戏刷新 ***********/

void GameWindow::updateGame(){
    for(Treasure* ore: ores){

        if(ore == nullptr){
            continue;
        }
        if(ore->on_center()){
            money += ore->getValue();

            QString orename = ore->getName();
            if(orename == "gold"){
                goldmoney += 1;
            }
            else if(orename == "fruitcack"){
                fruitcackmoney += 1;
            }
            else if(orename == "cack"){
                cackmoney += 1;
            }
            else if(orename == "fruit"){
                fruitmoney += 1;
            }
            else if(orename == "chicken"){
                chickenmoney += 1;
            }

            ore->getPos()->removeTreasure();
            ores.removeOne(ore);
            delete ore;
            ore = nullptr;
        }

        else {
            BaseTool* toll = ore->check_tool();
            if(toll == nullptr){ continue; }

            QString toolstr = toll->getName();
            if(toolstr == "trash"){
                ore->getPos()->removeTreasure();
                ores.removeOne(ore);
                delete ore;
                ore = nullptr;
            }

            else if(toolstr == "mixer"){
                ore->getPos()->removeTreasure();
                toll->recieveOre(ore);
                ores.removeOne(ore);
                delete ore;
                ore = nullptr;
            }
        }
    }

    if(assignRicePointer !=2 && goldmoney == assignRice[assignRicePointer]){
        assignRicePointer++;
        coin++;
    }
    if(assignCackPointer !=2 && cackmoney == assignCack[assignCackPointer]){
        assignCackPointer++;
        coin++;
    }
    if(assignFruitPointer !=2 && fruitmoney == assignFruit[assignFruitPointer]){
        assignFruitPointer++;
        coin++;
    }
    if(assignChickPointer !=2 && chickenmoney == assignChicken[assignChickPointer]){
        assignChickPointer++;
        coin++;
    }

    update();
}

void GameWindow::updateCreator(){
    for(BaseTool* tool: my_creator){
        Treasure* ore = tool->operate();
        if(ore){
            ores.push_back(ore);
        }
    }

    update();
}

void GameWindow::updateBelt(){
    for(Treasure* ore: ores){
        if(!ore->on_center()){
            BaseTool* toll = ore->check_tool();
            if(toll == nullptr){ continue; }

            QString toolstr = toll->getName();
            if(toolstr == "belt"){
                if(ore->move(beltSpeed)){
                    ores.removeOne(ore);
                    delete ore;
                    ore = nullptr;
                }
            }

            else if(toolstr == "kitchen"){
                if(ore->getName() == "kunkun"){
                    ores.removeOne(ore);
                    delete ore;
                    ore = nullptr;
                    if(!toll->getCreatPos()->can_addore()){
                        Treasure* chick = new Chicken(toll->getCreatPos());
                        ores.push_back(chick);
                    }
                }
                else{
                    if(ore->move(beltSpeed)){
                        ores.removeOne(ore);
                        delete ore;
                        ore = nullptr;
                    }
                }
            }
        }
    }

    update();
}

void GameWindow::updateCutter(){
    for(Treasure* ore: ores){

        if(!ore->on_center()){
            BaseTool* toll = ore->check_tool();
            if(toll == nullptr){ continue; }

            QString toolstr = toll->getName();

            if(toolstr == "cutter"){
                ores.removeOne(ore);
                bool cut = ore->can_cut();
                ore->getPos()->removeTreasure();
                delete ore;
                ore = nullptr;
                if(cut){
                    MapPoint* firexit = toll->getFirPos();
                    MapPoint* secexit = toll->getSecPos();
                    if(firexit != nullptr && !firexit->can_addore()){
                        Treasure* newcack = new Cack(firexit);
                        ores.push_back(newcack);
                    }
                    if(secexit != nullptr && !secexit->can_addore()){
                        Treasure* newfruit = new Fruit(secexit);
                        ores.push_back(newfruit);
                    }
                }
            }
        }
    }

    update();
}

void GameWindow::updateMixer(){
    for(BaseTool* tool : my_mixer){
        Treasure* ore = tool->mixPush();
        if(ore){
            ores.push_back(ore);
        }
    }

    update();
}

/***********  升级系统  ************/

void GameWindow::upgradeBelt(){
    if(coin > 0 && beltSpeed != 3){
        musicPlayer->upgradeTool();
        coin--;
        beltLevel++;
        beltSpeed = 3;
    }
}

void GameWindow::upgradeCutter(){
    if(coin > 0 && cutterSpeed != 0){
        musicPlayer->upgradeTool();
        coin--;
        cutterLevel++;
        cutterSpeed -= 1000;
        if(cutterSpeed != 0){
            cutterTimer->setInterval(cutterSpeed);
        }
        else{
            cutterTimer->setInterval(100);
        }
    }
}

void GameWindow::upgradeCreator(){
    if(coin > 0 && creatorSpeed != 0){
        musicPlayer->upgradeTool();
        coin--;
        creatorLevel++;
        creatorTimer->setInterval(creatorSpeed);
        creatorSpeed -= 1000;
    }
}

void GameWindow::upgradeCenter(){
    if(money >= 150 && centerLevel == 0){
        musicPlayer->upgradeCenter();

        // 从世界中获得扩展到的地块
        QVector<MapPoint *> grids = world->centerArround();

        for(MapPoint* grid : grids){
            // 先清除地块上的工具
            BaseTool* tool = grid->removeTool();
            if(tool != nullptr){
                QString toolname = tool->getName();

                if(toolname == "creator"){
                    my_creator.removeOne(tool);
                }
                else if(toolname == "cutter"){
                    my_cutter.removeOne(tool);
                }
                else if(toolname == "belt"){
                    my_belt.removeOne(tool);
                }
                else if(toolname == "trash"){
                    my_trash.removeOne(tool);
                }
                else if(toolname == "kitchen"){
                    my_kitchen.removeOne(tool);
                }
                tool->deleself();
                delete tool;
                tool = nullptr;
            }

            // 再清除地块上的货物
            Treasure* ore = grid->removeTreasure();
            if(ore != nullptr){
                ores.removeOne(ore);
                delete ore;
                ore = nullptr;
            }

            // 此地块更改为中心
            grid->changeName("center");
            grid->make_center();
        }

        centerPos.setX(centerPos.x()-gridSize);
        centerPos.setY(centerPos.y()-gridSize);

        centerLevel = 1;
        money -= 150;
    }
}

void GameWindow::upgradeMiner(){
    if(money >= 10){
        musicPlayer->upgradeTool();
        money -= 10;
        minerNum++;
    }
}

void GameWindow::upgradeMagic(){
    if(money >= 10){
        musicPlayer->upgradeTool();
        money -= 10;
        magicNum++;
    }
}

void GameWindow::upgradeRice(){
    if(money >= 50){
        musicPlayer->upgradeOre();
        money -= 50;
        Treasure* ore = new Gold(modeGrid);
        ore->changeValue(1);
        modeGrid->removeTreasure();
        delete ore;
    }
}

void GameWindow::upgradeCack(){
    if(money >= 50){
        musicPlayer->upgradeOre();
        money -= 50;
        Treasure* ore = new FruitCack(modeGrid);
        ore->changeValue(1);
        modeGrid->removeTreasure();
        delete ore;
    }
}

void GameWindow::upgradeFruit(){
    if(money >= 50){
        musicPlayer->upgradeOre();
        money -= 50;
        Treasure* ore = new Fruit(modeGrid);
        ore->changeValue(1);
        modeGrid->removeTreasure();
        delete ore;
    }
}

void GameWindow::upgradeChick(){
    if(money >= 50){
        musicPlayer->upgradeOre();
        money -= 50;
        Treasure* ore = new Chicken(modeGrid);
        ore->changeValue(1);
        modeGrid->removeTreasure();
        delete ore;
    }
}

/**************** 按钮响应 *****************/

void GameWindow::creatorPushButton(){
    musicPlayer->buttonPush();
    mouseToolBuilder = "creator";
    qDebug() << "you chose creator";
}

void GameWindow::cutterPushButton(){
    musicPlayer->buttonPush();
    mouseToolBuilder = "cutter";
    qDebug() << "you chose cutter";
}

void GameWindow::beltPushButton(){
    musicPlayer->buttonPush();
    mouseToolBuilder = "belt";
    qDebug() << "you chose belt";
}

void GameWindow::trashPushButton(){
    musicPlayer->buttonPush();
    mouseToolBuilder = "trash";
    qDebug() << "you chose trash";
}

void GameWindow::kitchenPushButton(){
    musicPlayer->buttonPush();
    mouseToolBuilder = "kitchen";
    qDebug() << "you chose kitchen";
}

void GameWindow::minerPushButton(){
    musicPlayer->buttonPush();
    mouseToolBuilder = "miner";
}

void GameWindow::mixerPushButton(){
    musicPlayer->buttonPush();
    mouseToolBuilder = "mixer";
    qDebug() << "you chose mixer";
}

void GameWindow::shopPushButton(){
    musicPlayer->buttonPush();
    shopVisiable = !shopVisiable;
    if(shopVisiable){
        shopWidget->show();
    }
    else{
        shopWidget->hide();
    }
}

void GameWindow::magicPushButton(){
    musicPlayer->buttonPush();
    magicVisiable = !magicVisiable;
    if(magicVisiable){
        magicWidget->show();
    }
    else{
        magicWidget->hide();
    }
}

void GameWindow::chose_magicRice(){
    musicPlayer->buttonPush();
    mouseToolBuilder = "magicRice";
}

void GameWindow::chose_magicCack(){
    musicPlayer->buttonPush();
    mouseToolBuilder = "magicCack";
}

void GameWindow::chose_magicKun(){
    musicPlayer->buttonPush();
    mouseToolBuilder = "magicKun";
}


/**************   存档   **************/
void GameWindow::savePushButton(){
    musicPlayer->buttonPush();
    QString saveName = QInputDialog::getText(this, tr("Save Game"), tr("存档名称:"));

    QDir().mkpath(QCoreApplication::applicationDirPath() + "/save_game/");

    // 检查用户是否取消了输入
    if (!saveName.isEmpty()) {
        QString fileName = QCoreApplication::applicationDirPath() + "/save_game/" + saveName + ".txt"; // 保存的文件名
        qDebug() << fileName;
        QFile savefile(fileName);
        if (savefile.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream out(&savefile);
            // 将游戏数据写入文件
            // 写地图
            world->save_world(out);
            // 写工具
            this->writeTool(out);
            // 写现场
            out << 'c' << " " << centerLevel << Qt::endl;
            out << 'm' << " " << money << Qt::endl;
            out << 'o' << Qt::endl;

            savefile.close();
        }
        else {
            qDebug() << "fail to build file: " << savefile.errorString();;
        }
    }
}

QTextStream& GameWindow::writeTool(QTextStream& out){
    for(BaseTool* tool : my_creator){
        out << "t " << 1 << " " << tool->arr_x() << " "
            << tool->arr_y() << " " << tool->getDirectionIndex() << Qt::endl;
    }
    for(BaseTool* tool : my_cutter){
        out << "t " << 2 << " " << tool->arr_x() << " "
            << tool->arr_y() << " " << tool->getDirectionIndex() << Qt::endl;
    }
    for(BaseTool* tool : my_belt){
        out << "t " << 3 << " " << tool->arr_x() << " "
            << tool->arr_y() << " " << tool->getDirectionIndex() << Qt::endl;
    }
    for(BaseTool* tool : my_trash){
        out << "t " << 4 << " " << tool->arr_x() << " "
            << tool->arr_y() << " " << tool->getDirectionIndex() << Qt::endl;
    }
    for(BaseTool* tool : my_kitchen){
        out << "t " << 5 << " " << tool->arr_x() << " "
            << tool->arr_y() << " " << tool->getDirectionIndex() << Qt::endl;
    }
    for(BaseTool* tool : my_mixer){
        out << "t " << 6 << " " << tool->arr_x() << " "
            << tool->arr_y() << " " << tool->getDirectionIndex() << Qt::endl;
    }

    return out;
}

/***********   建造工具   ************/

void GameWindow::buildCreator(MapPoint* grid, int direct){
    if(!grid->can_addtool()){
        musicPlayer->buildTool();
        BaseTool* tool = new Creator(grid, direct);
        grid->addTool(tool);
        my_creator.push_back(tool);
    }
}

void GameWindow::buildCutter(MapPoint* grid, int direct){
    MapPoint* with_grid;
    switch(direct){
    case(0):
        with_grid = grid->get_RIGHTpoint();
        break;
    case(1):
        with_grid = grid->get_UPpoint();
        break;
    case(2):
        with_grid = grid->get_LEFTpoint();
        break;
    case(3):
        with_grid = grid->get_DOWNpoint();
        break;
    default:
        with_grid = nullptr;
    }

    if(!grid->can_addtool() && with_grid != nullptr && !with_grid->can_addtool()){
        musicPlayer->buildTool();
        BaseTool* tool = new Cutter(grid, with_grid, direct);
        grid->addTool(tool);
        my_cutter.push_back(tool);
    }
}

void GameWindow::buildBelt(MapPoint* grid, int direct){
    if(!grid->can_addtool()){
        musicPlayer->buildTool();
        BaseTool* tool = new Belt(grid, direct);
        grid->addTool(tool);
        my_belt.push_back(tool);
    }
}

void GameWindow::buildTrash(MapPoint* grid, int direct){
    if(!grid->can_addtool()){
        musicPlayer->buildTool();
        BaseTool* tool = new Trash(grid, direct);
        grid->addTool(tool);
        my_trash.push_back(tool);
    }
}

void GameWindow::buildKitchen(MapPoint* grid, int direct){
    if(!grid->can_addtool()){
        musicPlayer->buildTool();
        BaseTool* tool = new Kitchen(grid, direct);
        grid->addTool(tool);
        my_kitchen.push_back(tool);
    }
}

void GameWindow::buildMixer(MapPoint* grid, int direct){
    if(!grid->can_addtool()){
        musicPlayer->buildTool();
        BaseTool* tool = new Mixer(grid, direct);
        grid->addTool(tool);
        my_mixer.push_back(tool);
    }
}

void GameWindow::changeGrid(MapPoint* oldgrid, QString newgrid){
    if(magicNum > 0 && oldgrid->getName() == "field"){
        if(oldgrid->can_addore() || oldgrid->can_addtool()){
            return;
        }
        musicPlayer->magicGrid();
        if(newgrid == "rice"){
            oldgrid->changeName("goldplace");
        }
        else if(newgrid == "cack"){
            oldgrid->changeName("cackplace");
        }
        else if(newgrid == "kun"){
            oldgrid->changeName("kunplace");
        }
        magicNum--;
    }
}

void GameWindow::removeBarrier(MapPoint* oldgrid){
    if(minerNum > 0 && oldgrid->getName() == "barrier"){
        musicPlayer->removeTool();
        oldgrid->changeName("field");
        oldgrid->free_block();
        my_barrier.removeOne(oldgrid);
        minerNum--;
    }
}

/*******     绘制tool     ********/

void GameWindow::drawCreator(QPainter& painter, MapPoint* grid, QString& direction){
    QPoint pos = grid->getPos();
    QRect imageRect(pos.x(), pos.y(), gridSize, gridSize);
    if(direction == "UP"){
        painter.drawPixmap(imageRect, creatorU);
    }
    else if(direction == "LEFT"){
        painter.drawPixmap(imageRect, creatorL);
    }
    else if(direction == "DOWN"){
        painter.drawPixmap(imageRect, creatorD);
    }
    else if(direction == "RIGHT"){
        painter.drawPixmap(imageRect, creatorR);
    }
}

void GameWindow::drawMixer(QPainter& painter, MapPoint* grid, QString& direction){
    QPoint pos = grid->getPos();
    QRect imageRect(pos.x(), pos.y(), gridSize, gridSize);
    if(direction == "UP"){
        painter.drawPixmap(imageRect, mixerU);
    }
    else if(direction == "LEFT"){
        painter.drawPixmap(imageRect, mixerL);
    }
    else if(direction == "DOWN"){
        painter.drawPixmap(imageRect, mixerD);
    }
    else if(direction == "RIGHT"){
        painter.drawPixmap(imageRect, mixerR);
    }
}

void GameWindow::drawCutter(QPainter& painter, MapPoint* grid, QString& direction){
    QPoint pos = grid->getPos();
    if(direction == "UP"){
        QRect imageRect(pos.x(), pos.y(), 2*gridSize, gridSize);
        painter.drawPixmap(imageRect, cutterU);
    }
    else if(direction == "LEFT"){
        QRect imageRect(pos.x(), pos.y()-gridSize, gridSize, 2*gridSize);
        painter.drawPixmap(imageRect, cutterL);
    }
    else if(direction == "RIGHT"){
        QRect imageRect(pos.x(), pos.y(), gridSize, 2*gridSize);
        painter.drawPixmap(imageRect, cutterR);
    }
    else if(direction == "DOWN"){
        QRect imageRect(pos.x()-gridSize, pos.y(), 2*gridSize, gridSize);
        painter.drawPixmap(imageRect, cutterD);
    }
}

void GameWindow::drawTrash(QPainter& painter, MapPoint* grid){
    QPoint pos = grid->getPos();
    painter.drawPixmap(pos.x(), pos.y(), gridSize, gridSize, trashPath);
}

void GameWindow::drawKitchen(QPainter& painter, MapPoint* grid, QString& direction){
    QPoint pos = grid->getPos();
    QRect imageRect(pos.x(), pos.y(), gridSize, gridSize);
    if(direction == "UP"){
        painter.drawPixmap(imageRect, kitchenU);
    }
    else if(direction == "LEFT"){
        painter.drawPixmap(imageRect, kitchenL);
    }
    else if(direction == "DOWN"){
        painter.drawPixmap(imageRect, kitchenD);
    }
    else if(direction == "RIGHT"){
        painter.drawPixmap(imageRect, kitchenR);
    }
}

void GameWindow::drawBelt(QPainter& painter, MapPoint* grid, QString& direction){
    QPoint pos = grid->getPos();
    QRect imageRect(pos.x(), pos.y(), gridSize, gridSize);
    if(direction == "UD"){
        painter.drawPixmap(imageRect, beltUD);
    }
    else if(direction == "DU"){
        painter.drawPixmap(imageRect, beltDU);
    }
    else if(direction == "UR"){
        painter.drawPixmap(imageRect, beltUR);
    }
    else if(direction == "RU"){
        painter.drawPixmap(imageRect, beltRU);
    }
    else if(direction == "LR"){
        painter.drawPixmap(imageRect, beltLR);
    }
    else if(direction == "RL"){
        painter.drawPixmap(imageRect, beltRL);
    }
    else if(direction == "RD"){
        painter.drawPixmap(imageRect, beltRD);
    }
    else if(direction == "DR"){
        painter.drawPixmap(imageRect, beltDR);
    }
    else if(direction == "DL"){
        painter.drawPixmap(imageRect, beltDL);
    }
    else if(direction == "LD"){
        painter.drawPixmap(imageRect, beltLD);
    }
    else if(direction == "LU"){
        painter.drawPixmap(imageRect, beltLU);
    }
    else if(direction == "UL"){
        painter.drawPixmap(imageRect, beltUL);
    }
}

