#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QDebug>

#include "myfield.h"
#include "enemyfield.h"

class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = 0);
    MyField *My;
    EnemyField *Enemy;
    QPushButton *debMy;
    QPushButton *debEn;

public slots:
private slots:
    void getMouseCoord(int x, int y, int indI, int indJ);
    void doneMy();
};

#endif // WINDOW_H
