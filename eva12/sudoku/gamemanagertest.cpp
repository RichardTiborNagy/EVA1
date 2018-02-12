/*
#include <QtTest/QtTest>
#include "gamemanager.h"

class GameManagerTest : public QObject
{
    Q_OBJECT
private:
    GameManager* _model;
private slots:
    void initTestCase();
    void cleanupTestCase();
    void testNewGame();
    void testGameStep();
};

void GameManagerTest::initTestCase()
{
    _model = new GameManager();
}

void GameManagerTest::cleanupTestCase()
{
    delete _model;
}

void GameManagerTest::testNewGame()
{
    _model->newGame();

    QCOMPARE(_model->isPaused, false);
    QCOMPARE(_model->isHurried, false);

}

void GameManagerTest::testGameStep()
{
    _model->newGame();
    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j){
            _model->fields[i][j] = 0;
        }
    }
    for (int i = 0; i < 8; ++i){
        _model->fields[i][0] = i+1;
    }
    _model->stepGame(8,0);
    QCOMPARE(_model->fields[8][0], 9);

    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j){
            _model->fields[i][j] = 0;
        }
    }
    for (int i = 0; i < 8; ++i){
        _model->fields[0][i] = i+1;
    }
    _model->stepGame(0,8);
    QCOMPARE(_model->fields[0][8], 9);

    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j){
            _model->fields[i][j] = 0;
        }
    }

    _model->fields[0][0] = 1;
    _model->fields[0][1] = 2;
    _model->fields[0][2] = 3;
    _model->fields[1][0] = 4;
    _model->fields[1][1] = 5;
    _model->fields[1][2] = 6;
    _model->fields[2][0] = 7;
    _model->fields[2][1] = 8;

    _model->stepGame(2,2);
    QCOMPARE(_model->fields[2][2], 9);
}

QTEST_APPLESS_MAIN(GameManagerTest)
#include "gamemanagertest.moc"
*/
