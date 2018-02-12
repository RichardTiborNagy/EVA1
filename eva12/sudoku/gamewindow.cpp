#include "gamewindow.h"
#include <QMessageBox>
#include <QApplication>

GameWindow::GameWindow(QWidget *parent) : QWidget(parent){
    setFixedSize(600,400);
    setWindowTitle(trUtf8("Sudoku"));

    gameManager = new GameManager();

    connect(gameManager, SIGNAL(gameOver(bool)), this, SLOT(gameManager_gameOver(bool)));
    connect(gameManager, SIGNAL(fieldChanged(int, int)), this, SLOT(gameManager_fieldChanged(int, int)));
    connect(gameManager, SIGNAL(updateTime()), this, SLOT(gameManager_updateTime()));

    newGameButton = new QPushButton(trUtf8("New Game"));
    connect(newGameButton, SIGNAL(clicked()), this, SLOT(newGameButtonClicked()));
    saveGameButton = new QPushButton(trUtf8("Save Game"));
    connect(saveGameButton, SIGNAL(clicked()), this, SLOT(saveGameButtonClicked()));
    loadGameButton = new QPushButton(trUtf8("Load Game"));
    connect(loadGameButton, SIGNAL(clicked()), this, SLOT(loadGameButtonClicked()));
    hurryButton = new QPushButton(trUtf8("Hurry Gamemode"));
    connect(hurryButton, SIGNAL(clicked()), this, SLOT(hurryButtonClicked()));

    pauseButton = new QPushButton(trUtf8("Pause/Continue"));
    connect(pauseButton, SIGNAL(clicked()), gameManager, SLOT(pauseGame()));

    timeLabel = new QLabel("Time spent: " + QString::number(gameManager->timeSpent) + "\n\nTime left: " + QString::number(gameManager->timeLeft));
    mainLayout = new QHBoxLayout();
    tableLayout = new QGridLayout();
    topLayout = new QVBoxLayout();

    topLayout->addWidget(newGameButton);
    topLayout->addWidget(saveGameButton);
    topLayout->addWidget(loadGameButton);
    topLayout->addWidget(hurryButton);
    topLayout->addWidget(pauseButton);
    topLayout->addWidget(timeLabel);

    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(tableLayout);

    //tableLayout->setSpacing(0);
    //tableLayout->setMargin(0);

    buttons.resize(9);
    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j){
            QPushButton * b = new QPushButton(this);
            buttons[i].append(b);
            b->setFixedWidth(40);
            b->setFixedHeight(40);
            connect(b, SIGNAL(clicked()), this, SLOT(buttonClicked()));
            tableLayout->addWidget(b,i,j);
        }
    }

    setLayout(mainLayout);
}

GameWindow::~GameWindow(){
    delete gameManager;
}

void GameWindow::buttonClicked(){
    QPushButton* senderButton = dynamic_cast <QPushButton*> (QObject::sender());
    int location = tableLayout->indexOf(senderButton);

    gameManager->stepGame((int)location / 9, location % 9);
}

void GameWindow::newGameButtonClicked(){
    enableButtons();
    gameManager->newGame();
    lockButtons();
}

void GameWindow::saveGameButtonClicked(){
    gameManager->saveGame();
}

void GameWindow::loadGameButtonClicked(){
    gameManager->loadGame();
    lockButtons();
}

void GameWindow::lockButtons(){
    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j){
            if (gameManager->fields[i][j] != 0)
                buttons[i][j]->setEnabled(false);
        }
    }
}

void GameWindow::enableButtons(){
    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j){
            if (gameManager->fields[i][j] != 0)
                buttons[i][j]->setEnabled(true);
        }
    }
}

void GameWindow::hurryButtonClicked(){
    gameManager->isHurried = !gameManager->isHurried;
}

void GameWindow::pauseButtonClicked(){
    gameManager->isPaused = !gameManager->isPaused;
}

void GameWindow::gameManager_gameOver(bool outcome){
    if (outcome)
    {
        QMessageBox::information(this, "Game Over", ("Time spent: " + QString::number(gameManager->timeSpent) + " seconds."));
        enableButtons();
        gameManager->newGame();
        lockButtons();
    }
    else
    {
        QMessageBox::information(this, "Game Over", "You ran out of time!");
        enableButtons();
        gameManager->newGame();
        lockButtons();
    }
}

void GameWindow::gameManager_fieldChanged(int i, int j){
    if (gameManager->fields[i][j] == 0)
        buttons[i][j]->setText("");
    else
        buttons[i][j]->setText(QString::number(gameManager->fields[i][j]));
}

void GameWindow::gameManager_updateTime(){
    timeLabel->setText("Time spent: " + QString::number(gameManager->timeSpent) + "\n\nTime left: " + QString::number(gameManager->timeLeft));
}








