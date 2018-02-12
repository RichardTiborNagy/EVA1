#ifndef BLACKHOLEPERSISTENCE_H
#define BLACKHOLEPERSISTENCE_H

#include <QString>
#include <QVector>

class BlackHolePersistence
{
public:
    explicit BlackHolePersistence() {}

    QVector<QString> saveGameList() const;

    bool loadGame(int gameIndex, QVector<int> &saveGameData);
    bool saveGame(int gameIndex, const QVector<int> &saveGameData);
};

#endif // BLACKHOLEPERSISTENCE_H
