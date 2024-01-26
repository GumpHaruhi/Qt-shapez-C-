#include "startwindow.h"
#include "ui_startwindow.h"
#include "gamewindow.h"

#include <QDebug>
#include <QPainter>
#include <QLabel>
#include <QFileDialog>
#include <QPushButton>
#include <QMessageBox>
#include <QDir>

// 这是开始界面
StartWindow::StartWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartWindow)
{
    ui->setupUi(this);

    setWindowTitle("少年，请开始你的表演");

    setFixedSize(1000, 600);

    QLabel* logoLabel = ui->logo;
    QPixmap logoimage(":/image/logo.png");
    logoimage = logoimage.scaled(700, 180, Qt::KeepAspectRatio);
    logoLabel->setPixmap(logoimage);
    logoLabel->setScaledContents(true);

    musicPlayer = new SoundPlayer;
    QDir().mkpath(QCoreApplication::applicationDirPath() + "/save_game/");

    QPushButton* newGameButton = ui->newGame;
    QPushButton* loadGameButton = ui->loadGame;
    newGameButton->setStyleSheet("background-color: white; color: black;");
    loadGameButton->setStyleSheet("background-color: white; color: black;");

    // condition : [0]goal [1]gold [2]fruitcack [3]cack [4]fruit

    connect(ui->newGame, &QPushButton::clicked, [&](){
        musicPlayer->buttonPush();
        int mapArr[20][32] = {
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,0,0,0,0},
                                {0,0,0,0,1,0,1,0,0,0,0,0,3,3,0,0,0,0,3,3,0,0,0,0,0,1,1,5,5,5,0,0},
                                {0,0,0,0,1,1,0,0,0,0,0,0,0,0,3,0,0,3,0,0,0,0,0,0,0,0,0,2,0,5,0,0},
                                {0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,3,3,0,0,0,0,3,0,0,0,0,0,0,0,5,0,0},
                                {0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,6,6,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,6,6,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,4,0,0,0,0,0,0,3,0,0,0,0,0,0,3,0,0,0,0,0,0,2,0,0,0,0,0},
                                {0,0,0,0,0,4,0,0,0,0,0,0,0,3,0,0,0,0,3,0,0,0,0,0,2,2,2,0,0,0,0,0},
                                {0,0,0,0,0,4,4,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0},
                                {0,0,0,0,4,4,0,0,0,0,0,0,0,0,0,3,3,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                };

        GameWindow * gamewindow = new GameWindow(mapArr);
        gamewindow->show();
    });

    connect(ui->loadGame, &QPushButton::clicked, this, &StartWindow::loadGameButton);

    musicPlayer->startGame();
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::loadGameButton(){
    musicPlayer->buttonPush();
    // 指定目录
    QString directoryPath = QCoreApplication::applicationDirPath() + "/save_game/";

    QStringList fileList = QFileDialog::getOpenFileNames(
        this,
        tr("Load Game"),
        directoryPath,
        tr("Text Files (*.txt);;All Files (*)"));

    // 检查是否有选择文件
    if (!fileList.isEmpty()) {
        // 创建一个弹窗
        QDialog dialog(this);
        QVBoxLayout layout(&dialog);
        dialog.setFixedSize(300, 200);
        dialog.setStyleSheet("background-color: lightgreen;");

        for (const QString& filePath : fileList) {
            QPushButton* okbutton = new QPushButton("确定", &dialog);
            QPushButton* nobutton = new QPushButton("取消", &dialog);

            // 连接按钮的点击信号到槽函数，传递文件路径
            connect(okbutton, &QPushButton::clicked, this, [&]() {
                this->loadFile(filePath);
                dialog.close(); // 关闭弹窗
            });
            connect(nobutton, &QPushButton::clicked, this, [&]() {
                dialog.close();
            });

            layout.addWidget(okbutton);
            layout.addWidget(nobutton);
        }

        // 显示弹窗
        dialog.exec();
    } else {
        // 提示用户目录下没有文件
        QMessageBox::information(this, tr("Information"), tr("You don't chose any file."));
    }
}

void StartWindow::loadFile(const QString& filePath){
    qDebug() << filePath << Qt::endl;

    QFile file(filePath);
    GameWindow * gamewindow = new GameWindow(file);
    gamewindow->show();
}
