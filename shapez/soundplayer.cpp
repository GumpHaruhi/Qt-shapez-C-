#include "soundplayer.h"

#include <QUrl>

SoundPlayer::SoundPlayer() {
    buildToolSound = new QSoundEffect;
    buildToolSound->setSource(QUrl::fromLocalFile(":/sound/spint.wav"));

    spinToolSound = new QSoundEffect;
    spinToolSound->setSource(QUrl::fromLocalFile(":/sound/removet.wav"));

    removeToolSound = new QSoundEffect;
    removeToolSound->setSource(QUrl::fromLocalFile(":/sound/buildt.wav"));

    upgradeCenterSound = new QSoundEffect;
    upgradeCenterSound->setSource(QUrl::fromLocalFile(":/sound/upCenter.wav"));

    upgradeToolSound = new QSoundEffect;
    upgradeToolSound->setSource(QUrl::fromLocalFile(":/sound/levelt.wav"));

    upgradeOreSound = new QSoundEffect;
    upgradeOreSound->setSource(QUrl::fromLocalFile(":/sound/levelo.wav"));

    magicGridSound = new QSoundEffect;
    magicGridSound->setSource(QUrl::fromLocalFile(":/sound/magic.wav"));

    buttonPushSound = new QSoundEffect;
    buttonPushSound->setSource(QUrl::fromLocalFile(":/sound/button.wav"));

    startWindowSound = new QSoundEffect;
    startWindowSound->setSource(QUrl::fromLocalFile(":/sound/start.wav"));
}

void SoundPlayer::buildTool(){
    buildToolSound->play();
}

void SoundPlayer::spinTool(){
    spinToolSound->play();
}

void SoundPlayer::removeTool(){
    removeToolSound->play();
}

void SoundPlayer::upgradeTool(){
    upgradeToolSound->play();
}

void SoundPlayer::upgradeOre(){
    upgradeOreSound->play();
}

void SoundPlayer::upgradeCenter(){
    upgradeCenterSound->play();
}

void SoundPlayer::magicGrid(){
    magicGridSound->play();
}

void SoundPlayer::buttonPush(){
    qDebug() << "play";
    buttonPushSound->play();
}

void SoundPlayer::startGame(){
    startWindowSound->play();
}
