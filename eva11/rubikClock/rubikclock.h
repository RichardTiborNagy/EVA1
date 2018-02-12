#ifndef RUBIKCLOCK_H
#define RUBIKCLOCK_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>

class RubikClock : public QWidget
{
    Q_OBJECT

private slots:
    void buttonClicked();
    void newGameButtonClicked();

public:
    RubikClock(QWidget *parent = 0);

private:
    void newGame();
    void tickClocks(int a, int b, int c, int d);
    void generateGame();
    void checkGame();
    void refreshLabels();

    int stepCount;
    QGridLayout* tableLayout;
    QVBoxLayout* mainLayout;
    QPushButton* newGameButton;
    QVector<QPushButton*> buttons;
    QVector<QLabel*> clockLabels;
    int* clockValues;
};

#endif // RUBIKCLOCK_H
