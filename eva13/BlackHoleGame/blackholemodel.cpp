#include "blackholemodel.h"

void BlackHoleModel::newGame(int n){
    //reset fields
    _currentPlayer = 1;
    _tableSize = n;
    _playerOneScore = 0;
    _playerTwoScore = 0;

    //clear the game table and create a new one, filled with 0s
    _gameTable.clear();
    _gameTable.resize(n);
    for(int i = 0; i<n; i++){
        _gameTable[i].resize(n);
        for (int j = 0; j < n; j++){
            _gameTable[i].append(0);
        }
    }

    //calculate the middle of the table
    int half = (int)n/2;

    //fill the diagonal elements with ships
    for (int i = 0; i < n; i++){
        if (i<half) _gameTable[i][i] = 1;
        else _gameTable[i][i] = 2;
    }

    int x = n-1;
    int y = 0;
    for (int i = 0; i < n; i++){
        if (x<half) _gameTable[x][y] = 1;
        else _gameTable[x][y] = 2;
        x--;
        y++;
    }

    //set the center to be a black hole
    _gameTable[half][half] = 3;

    //tell the view to update
    emit newTable(n);
    for(int i = 0; i<n; i++){
        for (int j = 0; j < n; j++){
            emit fieldChanged(i,j);
        }
    }
}

void BlackHoleModel::stepGame(int x, int y, int dirX, int dirY){
    //initialize the destination variables
    int destX = x;
    int destY = y;

    //calculate the direction, it will be (1,0),(0,1),(-1,0) or (0,-1)
    dirX = dirX - x;
    dirY = dirY - y;

    //move the destination according to the direction, stop if it hits a ship, a black hole, or the edge of the table
    while (!(destX+dirX < 0) && !(destX+dirX > _tableSize-1) && !(destY+dirY < 0) && !(destY+dirY > _tableSize-1) && _gameTable[destX+dirX][destY+dirY] != 1 && _gameTable[destX+dirX][destY+dirY] != 2){
        destX += dirX;
        destY += dirY;
        if (_gameTable[destX][destY] == 3) break;
    }

    //if the ship hit a black hole, remove it, add a point to the player, and update the table
    if (_gameTable[destX][destY] == 3){
        _gameTable[x][y] = 0;
        emit fieldChanged(x,y);
        if (_currentPlayer == 1) _playerOneScore++;
        else _playerTwoScore++;
    }
    //otherwise, it hit an obstacle, so it moves to the destination
    else {
        _gameTable[destX][destY] = _currentPlayer;
        _gameTable[x][y] = 0;
        emit fieldChanged(x,y);
        emit fieldChanged(destX,destY);
    }

    //change the current player
    if (_currentPlayer == 1) _currentPlayer = 2;
    else _currentPlayer = 1;

    //check if someone won
    checkGame();

}

//if any one of the players has more points than half of the number of ships the began with, they win
void BlackHoleModel::checkGame(){
    if (_playerOneScore == (_tableSize-1)/2) emit gameWon(1);
    else if (_playerTwoScore == (_tableSize-1)/2) emit gameWon(2);
}

QVector<QString> BlackHoleModel::saveGameList() const{
    return _persistence.saveGameList();
}

bool BlackHoleModel::loadGame(int gameIndex)
{
    //create a new vector to load into
    QVector<int> saveGameData;

    //load the vector with the data from the file
    if (!_persistence.loadGame(gameIndex, saveGameData))
        return false;

    //use the vector load the fields
    _tableSize = saveGameData[0];
    newGame(_tableSize);
    _currentPlayer = saveGameData[1];
    _playerOneScore = saveGameData[2];
    _playerTwoScore = saveGameData[3];
    //load the gametable from the vector
    for (int i = 4; i < saveGameData.size(); ++i){
        int x = (int)((i-4) / _tableSize);
        int y = (i-4) % _tableSize;
        _gameTable[x][y] = saveGameData[i];
    }
    //update the view
    for (int i = 0; i < _tableSize; ++i){
        for (int j = 0; j < _tableSize; ++j) {
            emit fieldChanged(i,j);
        }
    }

    return true;
}

bool BlackHoleModel::saveGame(int gameIndex)
{
    QVector<int> saveGameData;

    //save the fields to a vector
    saveGameData.push_back(_tableSize);
    saveGameData.push_back(_currentPlayer);
    saveGameData.push_back(_playerOneScore);
    saveGameData.push_back(_playerTwoScore);
    for (int i = 0; i < _tableSize; ++i){
        for (int j = 0; j < _tableSize; ++j) {
            saveGameData.push_back(_gameTable[i][j]);
        }
    }

    return _persistence.saveGame(gameIndex, saveGameData);
}



























