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
    // Не спрашивайте, почему я вместо лейблов поставил кнопки
    QPushButton *lblMyCount;     // эти надписи будут показывать
    QPushButton *lblEnemyCount;  // сколько клеток расставлено по полям
    QPushButton *debMy;
    QPushButton *debEn;
signals:
    void sendName(const QString &name); // сигнал для отправки имени игрока
    void startEditing();    // разрешить редактирование
    void startGame();   // начать игру

public slots:
private slots:
    void getMouseCoord(int x, int y);
    void setMyCountOfCells(int myCountCells);
    void setEnemyCountOfCells(int enemyCountCells);
};

#endif // WINDOW_H
