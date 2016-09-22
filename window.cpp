#include "window.h"

Window::Window(QWidget *parent) : QWidget(parent)
{
    My = new MyField(220, 220);
    Enemy = new EnemyField(220, 220);

    debEn = new QPushButton("Enemy", this);
    debMy = new QPushButton("My", this);


    QVBoxLayout *leftField = new QVBoxLayout();
    leftField->addWidget(My);
    leftField->addWidget(debMy);
    QVBoxLayout *rightField = new QVBoxLayout();
    rightField->addWidget(Enemy);
    rightField->addWidget(debEn);

    QGridLayout *lay = new QGridLayout(this);
    lay->addLayout(leftField, 0, 0);
    lay->addLayout(rightField, 0, 1);

    this->setLayout(lay);
    this->resize(QSize(510, 320));
    this->setMinimumSize(QSize(510, 300));
    // тест
    // TODO: Сделать, чтобы в выводе писало с какого поля был клик
    connect(My, SIGNAL(sendMouseCoord(int,int,int,int)), this, SLOT(getMouseCoord(int,int,int,int)));
    connect(Enemy, SIGNAL(sendMouseCoord(int,int,int,int)), this, SLOT(getMouseCoord(int,int,int,int)));

    connect(debEn, SIGNAL(clicked(bool)), Enemy, SLOT(DEBUGgetField()));
    connect(debMy, SIGNAL(clicked(bool)), My, SLOT(DEBUGgetField()));

}

void Window::getMouseCoord(int x, int y, int indI, int indJ)
{
    qDebug() << QString("X: %1; Y: %2 [%3 %4]").arg(QString::number(x)).arg(QString::number(y)).arg(QString::number(indI)).arg(QString::number(indJ));
}

void Window::doneMy()
{
    QMessageBox::information(this, "info", "ssss");
}
