#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include <QMediaPlayer>
#include <QSoundEffect>

class SoundPlayer
{
    QSoundEffect* buildToolSound;
    QSoundEffect* spinToolSound;
    QSoundEffect* removeToolSound;
    QSoundEffect* upgradeCenterSound;
    QSoundEffect* upgradeToolSound;
    QSoundEffect* upgradeOreSound;
    QSoundEffect* magicGridSound;
    QSoundEffect* buttonPushSound;
    QSoundEffect* startWindowSound;
public:
    SoundPlayer();

    void buildTool();
    void spinTool();
    void removeTool();
    void upgradeTool();
    void upgradeOre();
    void upgradeCenter();
    void magicGrid();
    void buttonPush();
    void startGame();
};

#endif // SOUNDPLAYER_H
