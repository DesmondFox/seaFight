#ifndef FIELD_H
#define FIELD_H

#include <QWidget>
#include <QPainter>
#include <QPaintDevice>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>
#include "ship.h"

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
    explicit Field(int widthOfField, int heightOfField);
protected:
    virtual void paintEvent(QPaintEvent *event);
    QPixmap *pm;

    bool setCellsModeFlag;  // флаг, показывающий, что мы в режиме расстановки кораблей
    bool tmpStatusToPress;


    position currentPosition; // В каком положении сейчас указатель (вертикальное/горизонтальное)

    int width;  // ширина поля
    int height;  // высота поля

    int zero_x; //  НУЛЕВЫЕ ТОЧКИ,
    int zero_y; //  с которых идет рисование поля
    int cellSize;   //  размер(сторона) одной клетки

    int FIELD[10][10]; // собственно, поле
    QVector<Ship> ships;

    int c_x;
    int c_y;
    int currentx;
    int currenty;
    int age;    // состояние постройки кораблей

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    virtual bool drawGhostCell(const Ship &sh, QColor color = QColor(0, 120, 0, 100));
    virtual void drawShip(const Ship &sh, QColor color = QColor(225, 225, 225));
    virtual void drawField();

       /// Функции для дебага
    QString debugGetField();   // вывод значений поля
    void drawFieldCells();

signals:
    void sendMouseCoord(int x, int y, int indI, int indJ);

public slots:
    void DEBUGgetField();
    void clean(QColor color = QColor(Qt::white));

};

#endif // FIELD_H
