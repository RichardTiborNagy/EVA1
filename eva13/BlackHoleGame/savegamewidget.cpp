#include "savegamewidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

SaveGameWidget::SaveGameWidget(QWidget *parent) :
    QDialog(parent)
{
    setFixedSize(300, 200);
    setWindowTitle("Black Hole game saving");

    _listWidget = new QListWidget();
    _okButton = new QPushButton("Ok");
    _cancelButton = new QPushButton("Cancel");

    QHBoxLayout* hlayout = new QHBoxLayout();
    hlayout->addWidget(_okButton);
    hlayout->addWidget(_cancelButton);

    QVBoxLayout* vlayout = new QVBoxLayout();
    vlayout->addWidget(_listWidget);
    vlayout->addLayout(hlayout);

    setLayout(vlayout);

    connect(_okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(_cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

void SaveGameWidget::setGameList(QVector<QString> saveGameList)
{
    _listWidget->clear();

    for (int i = 0; i < 5; i++)
    {
        if (i < saveGameList.size() && !saveGameList[i].isEmpty())
            _listWidget->addItem(saveGameList[i]);
        else
            _listWidget->addItem("empty");
    }
}
