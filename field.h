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

    bool setCellsModeFlag;  // флаг, показывающий, что мы в режиме расстановки кораблей
    bool tmpStatusPressFlag; // Флаг, указывающий, можно ли ставить корабль в том месте

    POSITION currentPosition; // В какмо положении сейчас указатель (вертикальное/горизонтальное)

    QString playerName;
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

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    virtual void drawField();
    virtual bool drawGhostCell(int cellx, int celly, SHIPS ship, POSITION pos = HORIZONTAL, QColor color = QColor(186, 186, 186, 150));
    virtual void drawCellField();
    virtual void drawShip(int cellx, int celly, SHIPS ship, POSITION pos);
    virtual void drawOneCell(int cellx, int celly, CELLS cellType = CL_CELL);  //Нарисовать одну клетку


    bool checkNeightbourhood(int cellx, int celly, SHIPS ship, POSITION pos);  // метод для проверки корабля на "ближайших соседей"
    /// Функции для дебага
    QString debugGetField();   // вывод значений поля

signals:
    void sendMouseCoord(int x, int y, int indI, int indJ);
    void sendCountCells(int countCells);    // сигнал, передающий колличество расставленных клеток на поле
    void done(); // сигнализируем о том, что у нас клетки уже расставлены

public slots:
    void DEBUGgetField();
    void clean(QColor color = QColor(Qt::white));

};

#endif // FIELD_H
