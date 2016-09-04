#include "window.h"

Window::Window(QWidget *parent) : QWidget(parent)
{
    My = new MyField(220, 220);
    Enemy = new EnemyField(220, 220);

    lblMyCount = new QPushButton("Колличество клеток: 0/20", this);
    lblEnemyCount = new QPushButton("Колличество клеток: 0/20", this);
    lblEnemyCount->setEnabled(false);
    lblMyCount->setEnabled(false);

    debEn = new QPushButton("Enemy", this);
    debMy = new QPushButton("My", this);


    QVBoxLayout *leftField = new QVBoxLayout();
    leftField->addWidget(My);
    leftField->addWidget(lblMyCount);
    leftField->addWidget(debMy);
    QVBoxLayout *rightField = new QVBoxLayout();
    rightField->addWidget(Enemy);
    rightField->addWidget(lblEnemyCount);
    rightField->addWidget(debEn);

    QGridLayout *lay = new QGridLayout(this);
    lay->addLayout(leftField, 0, 0);
    lay->addLayout(rightField, 0, 1);

    this->setLayout(lay);
    this->resize(QSize(510, 320));
    this->setMinimumSize(QSize(510, 300));

    // TODO: Сделать, чтобы в выводе писало с какого поля был клик
    connect(My, SIGNAL(sendMouseCoord(int,int)), this, SLOT(getMouseCoord(int,int)));
    connect(Enemy, SIGNAL(sendMouseCoord(int,int)), this, SLOT(getMouseCoord(int,int)));
    connect(My, SIGNAL(sendCountCells(int)), this, SLOT(setMyCountOfCells(int)));
    connect(Enemy, SIGNAL(sendCountCells(int)), this, SLOT(setEnemyCountOfCells(int)));
    // отключение редактирования

    connect(debEn, SIGNAL(clicked(bool)), Enemy, SLOT(getField()));
    connect(debMy, SIGNAL(clicked(bool)), My, SLOT(getField()));
}

void Window::getMouseCoord(int x, int y)
{
    qDebug() << QString("X: %1; Y: %2").arg(QString::number(x)).arg(QString::number(y));
}

void Window::setMyCountOfCells(int myCountCells)
{
    lblMyCount->setText(QString("Колличество клеток: %1/20").arg(QString::number(myCountCells)));
    if (myCountCells == 20)
        lblMyCount->setEnabled(true);
    else
        lblMyCount->setEnabled(false);
}

void Window::setEnemyCountOfCells(int enemyCountCells)
{
    lblEnemyCount->setText(QString("Колличество клеток: %1/20").arg(QString::number(enemyCountCells)));
    if (enemyCountCells == 20)
        lblEnemyCount->setEnabled(true);
    else
        lblEnemyCount->setEnabled(false);
}
