#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVector>
#include <QHBoxLayout>
#include "gamemanager.h"

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = 0);
    ~GameWindow();

private slots:
    void buttonClicked();
    void newGameButtonClicked();
    void saveGameButtonClicked();
    void loadGameButtonClicked();
    void lockButtons();
    void enableButtons();
    void hurryButtonClicked();
    void pauseButtonClicked();
    void gameManager_gameOver(bool outcome);
    void gameManager_fieldChanged(int i, int j);
    void gameManager_updateTime();


private:
    GameManager* gameManager;

    QPushButton* newGameButton;
    QPushButton* saveGameButton;
    QPushButton* loadGameButton;
    QPushButton* hurryButton;
    QPushButton* pauseButton;

    QLabel* timeLabel;

    QHBoxLayout* mainLayout;
    QVBoxLayout* topLayout;
    QGridLayout* tableLayout;
    QVector<QVector<QPushButton*>> buttons;
};

#endif // GAMEWINDOW_H
