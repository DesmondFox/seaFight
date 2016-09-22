#ifndef FIELD_H
#define FIELD_H

#include <QWidget>
#include <QPainter>
#include <QPaintDevice>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>
#include "ship.h"

enum POSITION {HORIZONTAL = 0, VERTICAL};
struct Indexes
{
    int i;
    int j;
};

class Field : public QWidget
{
    Q_OBJECT
public:
    explicit Field(QWidget *parent = 0);
protected:
    virtual void paintEvent(QPaintEvent *event);
    QPixmap *pm;

    bool setCellsModeFlag;  // флаг, показывающий, что мы в режиме расстановки кораблей

    POSITION currentPosition; // В какмо положении сейчас указатель (вертикальное/горизонтальное)
    int x;  // ширина поля
    int y;  // высота поля

    int zero_x; //  НУЛЕВЫЕ ТОЧКИ,
    int zero_y; //  с которых идет рисование поля
    int cellSize;   //  размер(сторона) одной клетки

    int FIELD[10][10]; // собственно, поле

    int c_x;    // клетки
    int c_y;    // т.е. индексы для массива+1

    int currentx;
    int currenty;
    int age;    // состояние постройки кораблей

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);


    virtual void drawField();

       /// Функции для дебага
    QString debugGetField();   // вывод значений поля

signals:
    void sendMouseCoord(int x, int y, int indI, int indJ);

public slots:
    void DEBUGgetField();
    void clean(QColor color = QColor(Qt::white));

};

#endif // FIELD_H
