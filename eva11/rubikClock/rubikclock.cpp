#include "rubikclock.h"

RubikClock::RubikClock(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(400, 400);
    setBaseSize(400,400);
    setWindowTitle(tr("Rubik Clock"));

    newGameButton = new QPushButton(trUtf8("Új játék"));
    connect(newGameButton, SIGNAL(clicked()), this, SLOT(newGameButtonClicked()));

    mainLayout = new QVBoxLayout();
    //mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addWidget(newGameButton);

    tableLayout = new QGridLayout();
    generateGame();

    mainLayout->addLayout(tableLayout);
    setLayout(mainLayout);
}

void RubikClock::generateGame()
{
    clockValues =  new int[9];
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            if (0 == (i % 2) && 0 == (j % 2))
            {
                clockLabels.push_back(new QLabel(this));
                clockLabels.last()->setFont(QFont("Times New Roman", 28, QFont::Bold));
                clockLabels.last()->setAlignment(Qt::AlignCenter);
                tableLayout->addWidget(clockLabels.last(), i, j);
            }
            if (1 == (i % 2) && 1 == (j % 2))

            {
                buttons.push_back(new QPushButton(this));
                buttons.last()->setFont(QFont("Times New Roman", 10, QFont::Bold));
                buttons.last()->setText("+");
                tableLayout->addWidget(buttons.last(), i, j);
                connect(buttons.last(), SIGNAL(clicked()), this, SLOT(buttonClicked()));
            }
        }
    }

    newGame();
}

void RubikClock::refreshLabels()
{
    for (int i = 0; i < 9; ++i){
        clockLabels[i]->setText(QString::number(clockValues[i]));
    }
}

void RubikClock::buttonClicked()
{
    QPushButton* senderButton = dynamic_cast <QPushButton*> (QObject::sender());
    int buttonIndex = buttons.indexOf(senderButton);
    switch (buttonIndex)
    {
    case 0:
        tickClocks(0,1,3,4);
        break;
    case 1:
        tickClocks(1,2,4,5);
        break;
    case 2:
        tickClocks(3,4,6,7);
        break;
    case 3:
        tickClocks(4,5,7,8);
        break;
    }
}

void RubikClock::tickClocks(int a, int b, int c, int d)
{
    ++stepCount;
    clockValues[a] = clockValues[a] % 12 + 1;
    clockValues[b] = clockValues[b] % 12 + 1;
    clockValues[c] = clockValues[c] % 12 + 1;
    clockValues[d] = clockValues[d] % 12 + 1;
    refreshLabels();
    checkGame();
}

void RubikClock::newGame()
{
    stepCount = 0;
    for (int i = 0; i < 9; ++i)
    {
        clockValues[i] = rand()%(12) + 1;
    }
    refreshLabels();
}

void RubikClock::newGameButtonClicked()
{
    newGame();
}

void RubikClock::checkGame()
{
    bool l = true;
    int i = 0;
    while (l && i < 9)
    {
        l = clockValues[i] == 12;
        ++i;
    }
    if (l)
    {
        QMessageBox::information(this, "Játék vége!", "Lépésszám: " + QString::number(stepCount));
        newGame();
    }
}
