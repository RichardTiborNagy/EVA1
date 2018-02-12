/*
#include <QtTest/QtTest>
#include "blackholemodel.h"

class BlackHoleModelTest : public QObject
{
    Q_OBJECT
private:
    BlackHoleModel* _model;
private slots:
    void initTestCase();
    void cleanupTestCase();
    void newGameTest();
    void stepGameTest();
    void checkGameTest();
};

void BlackHoleModelTest::initTestCase()
{
    _model = new BlackHoleModel();
}

void BlackHoleModelTest::cleanupTestCase()
{
    delete _model;
}

void BlackHoleModelTest::newGameTest()
{
    _model->newGame(7);

    QCOMPARE(_model->getField(0,0), 1);
    QCOMPARE(_model->getField(4,2), 2);
    QCOMPARE(_model->getField(3,3), 3);
    QCOMPARE(_model->getField(6,6), 2);
    QCOMPARE(_model->getField(2,4), 1);
}

void BlackHoleModelTest::stepGameTest()
{
    _model->newGame(7);
    _model->stepGame(2,2,3,2);
    QCOMPARE(_model->getField(2,2), 0);
    QCOMPARE(_model->getField(3,2), 1);

    _model->stepGame(4,4,4,5);
    QCOMPARE(_model->getField(4,4), 0);
    QCOMPARE(_model->getField(4,5), 0);
    QCOMPARE(_model->getField(4,6), 2);

    _model->stepGame(3,2,3,3);
    QCOMPARE(_model->getField(3,2), 0);
}

void BlackHoleModelTest::checkGameTest(){
    QCOMPARE(_model->getPlayerOneScore()<3 && _model->getPlayerTwoScore()<3, true);
}

QTEST_APPLESS_MAIN(BlackHoleModelTest)
#include "blackholemodeltest.moc"
*/
