#ifndef FIELD_H
#define FIELD_H

#include <QWidget>
#include <QPainter>
#include <QPaintDevice>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>

enum CELLS {CL_EMPTY = 0, CL_CELL, CL_DOT, CL_INJURED};
enum SHIPS {SL_1 = 1, SL_2, SL_3, SL_4};
enum POSITION {HORIZONTAL = 0, VERTICAL};


class Field : public QWidget
{
    Q_OBJECT
public:
    explicit Field(QWidget *parent = 0);
protected:
    virtual void paintEvent(QPaintEvent *event);
    QPixmap *pm;

    bool setCellsMode;  // флаг, показывающий, что мы в режиме расстановки кораблей

    QString playerName;
    int x;  // ширина поля
    int y;  // высота поля
    int zero_x; //  НУЛЕВЫЕ ТОЧКИ,
    int zero_y; //  с которых идет рисование поля
    int cell;   //  размер(сторона) одной клетки
    int FIELD[10][10]; // собственно, поле

    int currentx;
    int currenty;

    int count;  // колличество расставленных клеток на поле
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

//    void enterEvent(QEvent *event);
    virtual void drawField();
    virtual void drawCell(int x, int y, CELLS cellType = CL_CELL);
    virtual bool drawGhostCell(int cellx, int celly, SHIPS ship, POSITION pos = HORIZONTAL, QColor color = QColor(186, 186, 186, 150));
    void clean();
    virtual void drawCellField();

    virtual void drawOneCell(int cellx, int celly, CELLS cellType = CL_CELL);  //Нарисовать одну клетку

    /// Функции для дебага
    QString debugGetField();   // вывод значений поля

signals:
    void sendMouseCoord(int x, int y);
    void sendCountCells(int countCells);    // сигнал, передающий колличество расставленных клеток на поле
    void startEditingForEnemy();    // после того, как мы расставили свои ячейки, разрешим сделать это сопернику

public slots:
    void setName(const QString &name);  // слот для задания имени игрока
    void getField();
};

#endif // FIELD_H
