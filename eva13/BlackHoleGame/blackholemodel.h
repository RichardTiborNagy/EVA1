#ifndef BLACKHOLEMODEL_H
#define BLACKHOLEMODEL_H

#include <QObject>
#include <QVector>
#include <QString>
#include "blackholepersistence.h"

class BlackHoleModel : public QObject
{
    Q_OBJECT
public:

    BlackHoleModel(){}
    virtual ~BlackHoleModel(){}

    QVector<QString> saveGameList() const;
    int getCurrentPlayer() const { return _currentPlayer; }
    int getTableSize() const { return _tableSize; }
    int getField(int x, int y) const { return _gameTable[x][y]; }
    int getPlayerOneScore() const { return _playerOneScore; }
    int getPlayerTwoScore() const { return _playerTwoScore; }

public slots:
    void newGame(int n);
    void stepGame(int x, int y, int dirX, int dirY);
    bool loadGame(int gameIndex);
    bool saveGame(int gameIndex);


signals:
    void gameWon(int playerNumber);
    void fieldChanged(int x, int y);
    void newTable(int n);

private:
    void checkGame();
    int _currentPlayer;
    int _tableSize;
    int _playerOneScore;
    int _playerTwoScore;
    QVector<QVector<int> > _gameTable;

    BlackHolePersistence _persistence;
};

#endif // BLACKHOLEMODEL_H
