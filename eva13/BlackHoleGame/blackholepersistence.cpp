#include "blackholepersistence.h"
#include <QDateTime>
#include <QFileInfo>
#include <QFile>
#include <QTextStream>

QVector<QString> BlackHolePersistence::saveGameList() const
{
    QVector<QString> result(5);

    for (int i = 0; i < 5; i++)
    {
        if (QFile::exists("game" + QString::number(i) + ".sav"))
        {
            QFileInfo info("game"+ QString::number(i) + ".sav");
            result[i] = "[" + QString::number(i + 1) + "] " + info.lastModified().toString("yyyy.MM.dd HH:mm:ss");
        }
    }

    return result;
}

bool BlackHolePersistence::loadGame(int gameIndex, QVector<int> &saveGameData)
{
    QFile file("game" + QString::number(gameIndex) + ".sav");
    if (!file.open(QFile::ReadOnly))
        return false;

    QTextStream stream(&file);

    saveGameData.resize(1);
    saveGameData[0] = stream.readLine().toInt();

    saveGameData.resize(saveGameData[0]*saveGameData[0]+4);

    for (int i = 1; i < saveGameData.size(); i++)
        saveGameData[i] = stream.readLine().toInt();

    file.close();

    return true;
}

bool BlackHolePersistence::saveGame(int gameIndex, const QVector<int> &saveGameData)
{
    QFile file("game" + QString::number(gameIndex) + ".sav");
    if (!file.open(QFile::WriteOnly))
        return false;

    QTextStream stream(&file);

    for (int i = 0; i < saveGameData.size(); i++)
        stream << saveGameData[i] << endl;

    file.close();

    return true;
}
