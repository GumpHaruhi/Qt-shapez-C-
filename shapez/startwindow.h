#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include "soundplayer.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class StartWindow;
}
QT_END_NAMESPACE

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    StartWindow(QWidget *parent = 0);
    ~StartWindow();

private:
    Ui::StartWindow *ui;
    SoundPlayer* musicPlayer;
private slots:
    void loadGameButton();
    void loadFile(const QString& filePath);
};
#endif // STARTWINDOW_H
