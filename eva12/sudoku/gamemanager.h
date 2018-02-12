#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <QVector>
#include <QTimer>

class GameManager : public QObject
{
    Q_OBJECT
public:
    GameManager();
    ~GameManager();
    bool isPaused;
    bool isHurried;
    int timeSpent;
    int timeLeft;
    QVector<QVector<int>> fields;

public slots:
    void newGame();
    void pauseGame();
    void saveGame();
    void loadGame();
    void stepGame(int i, int j);

signals:
    void gameOver(bool outcome);
    void fieldChanged(int i, int j);
    void updateTime();

private slots:
    void timerTimeOut();

private:
    QVector<QVector<int>> savedFields;
    QTimer* timer;


};

#endif // GAMEMANAGER_H
