#include "blackholewidget.h"
#include <QMessageBox>
#include <QApplication>
#include <QKeyEvent>

BlackHoleWidget::BlackHoleWidget(QWidget *parent) : QWidget(parent) {
    //set the window size and title
    setMinimumSize(400, 400);
    setWindowTitle("Black Hole");

    //initialize the field variables
    _loadGameWidget = NULL;
    _saveGameWidget = NULL;
    _isStepping = false;

    //connect the signals of the model to the slots of the view
    connect(&_model, SIGNAL(gameWon(int)), this, SLOT(model_gameWon(int)));
    connect(&_model, SIGNAL(newTable(int)), this, SLOT(model_newTable(int)));
    connect(&_model, SIGNAL(fieldChanged(int, int)), this, SLOT(model_fieldChanged(int, int)));

    //create the main layout of the window
    _tableLayout = new QGridLayout();
    //set it to be the main layout
    setLayout(_tableLayout);

    //start a new game with the default (smallest) size
    _model.newGame(5);
}

BlackHoleWidget::~BlackHoleWidget() {
    if (_loadGameWidget != NULL) delete _loadGameWidget;
    if (_saveGameWidget != NULL) delete _saveGameWidget;
}

void BlackHoleWidget::keyPressEvent(QKeyEvent *event){

    //new game events, CTRL+1,2,3
    if (event->key() == Qt::Key_1 && QApplication::keyboardModifiers() == Qt::ControlModifier) {
        _model.newGame(5);
    }
    if (event->key() == Qt::Key_2 && QApplication::keyboardModifiers() == Qt::ControlModifier) {
        _model.newGame(7);
    }
    if (event->key() == Qt::Key_3 && QApplication::keyboardModifiers() == Qt::ControlModifier) {
        _model.newGame(9);
    }

    //saving, CTRL+S
    if (event->key() == Qt::Key_L && QApplication::keyboardModifiers() == Qt::ControlModifier) {
        if (_loadGameWidget == NULL) {
            _loadGameWidget = new LoadGameWidget();
            connect(_loadGameWidget, SIGNAL(accepted()), this, SLOT(loadGame()));
        }
        _loadGameWidget->setGameList(_model.saveGameList());
        _loadGameWidget->open();
    }

    //loading, CTRL+L
    if (event->key() == Qt::Key_S && QApplication::keyboardModifiers() == Qt::ControlModifier) {
        if (_saveGameWidget == NULL) {
            _saveGameWidget = new SaveGameWidget();
            connect(_saveGameWidget, SIGNAL(accepted()), this, SLOT(saveGame()));
        }

        _saveGameWidget->setGameList(_model.saveGameList());
        _saveGameWidget->open();
    }
}

void BlackHoleWidget::model_fieldChanged(int x, int y){
    //get the date from the model
    int a = _model.getField(x,y);

    //set the icon of the button accordingly
    switch ( a ) {
        case 0 : //empty
            _buttons[x][y]->setIcon(QIcon());
            break;
        case 1 : //red ship
            _buttons[x][y]->setIcon(QIcon(":/images/red.png"));
            break;
        case 2 : //blue ship
            _buttons[x][y]->setIcon(QIcon(":/images/blue.png"));
            break;
        case 3 : //black hole
            _buttons[x][y]->setIcon(QIcon(":/images/black.png"));
            break;
    }
}

void BlackHoleWidget::model_gameWon(int playerNumber){
    //notify the players about the end of the game
    QMessageBox::information(this, "Game Over", ("Player " + QString::number(playerNumber) + " won!"));

    //start a new game with the same size as the ended one
    _model.newGame(_model.getTableSize());
}

void BlackHoleWidget::model_newTable(int n){
    //clean up the buttons
    for (int i = 0; i < _buttons.size(); i++){
        for (int j = 0; j < _buttons.size(); j++){
            _tableLayout->removeWidget(_buttons[i][j]);
            delete _buttons[i][j];
        }
    }

    //resize the window according to the table size
    switch (n) {
    case 5:
        setFixedSize(400,400);
        break;
    case 7:
        setFixedSize(550,550);
        break;
    case 9:
        setFixedSize(700,700);
        break;
    }

    //create the buttons
    _buttons.resize(n);

    for (int i = 0; i < n; i++){
        _buttons[i].resize(n);
        for (int j = 0; j < n; j++){
            _buttons[i][j] = new QPushButton();
            _buttons[i][j]->setFixedSize(75, 75);
            _buttons[i][j]->setIconSize(QSize(70, 70));
            connect(_buttons[i][j], SIGNAL(clicked()), this, SLOT(buttonClicked()));
            _tableLayout->addWidget(_buttons[i][j], i, j);
        }
    }

    _isStepping = false;
}

void BlackHoleWidget::loadGame() {

    if (_model.loadGame(_loadGameWidget->selectedGame())) {
        QMessageBox::information(this, "Black Hole", "The game has been loaded, Player " + QString::number(_model.getCurrentPlayer()) + " is next.");
    }
    else {
        QMessageBox::warning(this, "Black Hole", trUtf8("The game was unable to be loaded."));
    }

}

void BlackHoleWidget::saveGame() {

    if (_model.saveGame(_saveGameWidget->selectedGame())) {
        QMessageBox::information(this, "Black Hole", "The game has been saved successfully.");
    }
    else {
        QMessageBox::warning(this, "Black Hole", trUtf8("The game was unable to be saved."));
    }

}

void BlackHoleWidget::buttonClicked(){
    //get the location of the clicked button
    QPushButton* senderButton = dynamic_cast <QPushButton*> (QObject::sender());
    int location = _tableLayout->indexOf(senderButton);
    int n = _model.getTableSize();
    int x = (int)location / n;
    int y = location % n;

    //selecting a ship of the current player
    if (!_isStepping && _model.getField(x, y) == _model.getCurrentPlayer()){
        //save the coordinates of the clicked ship
        _clickedX = x;
        _clickedY = y;
        _isStepping = true;
        //disable all buttons
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                _buttons[i][j]->setEnabled(false);
            }
        }

        //enable the originally clicked button
        _buttons[x][y]->setEnabled(true);

        //enable its neighbours
        if (x > 0) {
            if (_model.getField(x-1, y) == 0 || _model.getField(x-1, y) == 3){
                _buttons[x-1][y]->setEnabled(true);
            }
        }
        if (y > 0) {
            if (_model.getField(x, y-1) == 0 || _model.getField(x, y-1) == 3){
                _buttons[x][y-1]->setEnabled(true);
            }
        }
        if (x < n-1) {
            if (_model.getField(x+1, y) == 0 || _model.getField(x+1, y) == 3){
                _buttons[x+1][y]->setEnabled(true);
            }
        }
        if (y < n-1) {
            if (_model.getField(x, y+1) == 0 || _model.getField(x,y+1) == 3){
                _buttons[x][y+1]->setEnabled(true);
            }
        }
    }

    //moving a previously selected ship
    else if (_isStepping){
        //deselecting the selected ship
        if (_clickedX == x && _clickedY == y){
            _isStepping = false;
        }
        //moving the selected ship
        else {
            _model.stepGame(_clickedX,_clickedY,x,y);
            _isStepping = false;
        }
        //enable all the buttons
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                _buttons[i][j]->setEnabled(true);
            }
        }
    }
}







