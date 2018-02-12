#include "gamemanager.h"

GameManager::GameManager(){
    //fields = QVector<QVector<int>>;
    fields.resize(9);
    for (int i = 0; i < 9; ++i){
        fields[i].resize(9);
        for (int j = 0; j < 9; ++j){
            fields[i].append(0);
        }
    }
    savedFields = fields;
    timer = new QTimer();
    timer->setInterval(1000);

    connect(timer, SIGNAL(timeout()), this, SLOT(timerTimeOut()));

    timeSpent = 0;
    timeLeft = 5;
}

GameManager::~GameManager(){
    timer->stop();
    delete timer;
}

void GameManager::newGame(){
    timeSpent = 0;
    timeLeft = 5;
    isPaused = false;
    isHurried = false;

    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j){
            fields[i][j] = 0;
            emit fieldChanged(i,j);
        }
    }

    int rnd = qrand() % 50;
    for (int i = 0; i < rnd; ++i){
        int rnd2 = qrand() % 9;
        int rnd3 = qrand() % 9;
        int rnd4 = qrand() % 8;
        for (int j = 0; j < rnd4; ++j){
            stepGame(rnd2, rnd3);
        }
        emit fieldChanged(rnd2, rnd3);
    }


    timer->start();
}

void GameManager::pauseGame(){
    isPaused = !isPaused;
}

void GameManager::saveGame(){
    savedFields = fields;
}

void GameManager::loadGame(){
    fields = savedFields;
    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j){
            emit fieldChanged(i,j);
        }
    }
}

void GameManager::stepGame(int i, int j){
    if (isPaused) return;
    int newValue = (fields[i][j]+1) % 10;
    if (newValue == 0) {
        fields[i][j] = newValue;
        emit fieldChanged(i,j);
        return;
    }

    bool l = true;

    do {
        if (newValue == 0)
            break;
        l = true;
        int c = 0;
        for (int k = 0; k < 9; k++){
            if (newValue == fields[k][j])
                c++;
        }
        if (c>0){
            newValue = (newValue + 1) % 10;
            l = false;
            continue;
        }
        c = 0;
        for (int k = 0; k < 9; k++){
            if (newValue == fields[i][k])
                c++;
        }
        if (c>0){
            newValue = (newValue + 1) % 10;
            l = false;
            continue;
        }
        c = 0;
        for (int k = (int)(i / 3) * 3; k < (int)(i / 3) * 3 + 3; k++){
            for (int m = (int)(j / 3) * 3; m < (int)(j / 3) * 3 + 3; m++){
                if (newValue == fields[k][m])
                    c++;
            }
        }
        if (c>0){
            newValue = (newValue + 1) % 10;
            l = false;
            continue;
        }
    } while (!l);

    fields[i][j] = newValue;

    emit fieldChanged(i,j);


    bool n = true;
    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j){
            n = n && fields[i][j] != 0;
        }
    }
    if (n){
        emit gameOver(true);
        isPaused = true;
    }
    if (isHurried){
        emit updateTime();
        timeLeft = 5;
    }
}

void GameManager::timerTimeOut(){
    if (isPaused) return;
    if (isHurried){
        timeLeft--;
    }
    if (isHurried && timeLeft <= 0){
        emit gameOver(false);
    }
    timeSpent++;
    emit updateTime();
}
