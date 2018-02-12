#ifndef BLACKHOLEWIDGET_H
#define BLACKHOLEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QVector>
#include <QHBoxLayout>
#include "blackholemodel.h"
#include "loadgamewidget.h"
#include "savegamewidget.h"

class BlackHoleWidget : public QWidget {
    Q_OBJECT

public:
    BlackHoleWidget(QWidget *parent = 0);
    ~BlackHoleWidget();

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void buttonClicked();
    void model_gameWon(int playerNumber);
    void model_fieldChanged(int x, int y);
    void model_newTable(int n);
    void loadGame();
    void saveGame();

private:
    QGridLayout* _tableLayout;

    bool _isStepping;
    int _clickedX;
    int _clickedY;

    BlackHoleModel _model;
    SaveGameWidget* _saveGameWidget;
    LoadGameWidget* _loadGameWidget;
    QVector<QVector<QPushButton*> > _buttons;

};

#endif // BLACKHOLEWIDGET_H
