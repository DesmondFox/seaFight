#ifndef FIELD_H
#define FIELD_H

#include <QWidget>
#include <QPainter>
#include <QPaintDevice>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>

enum CELLS {CL_EMPTY = 0, CL_CELL, CL_DOT, CL_INJURED};

struct cells
{
    int one;
    int two;
};

class Field : public QWidget
{
    Q_OBJECT
public:
    explicit Field(QWidget *parent = 0);
protected:
    virtual void paintEvent(QPaintEvent *event);
    QPixmap *pm;

    QString playerName;
    bool editingMode;   // режим редактирования клеток

    int x;  // ширина поля
    int y;  // высота поля
    int zero_x; //  НУЛЕВЫЕ ТОЧКИ,
    int zero_y; //  с которых идет рисование поля
    int cell;   //  размер(сторона) одной клетки
    int FIELD[10][10]; // собственно, поле

    int count;  // колличество расставленных клеток на поле
    void mousePressEvent(QMouseEvent *event);
    virtual void drawField();
    virtual void drawCell(int x, int y, CELLS cellType = CL_CELL);
    virtual void drawNonActiveField();   // для нарисовки неактивного поля(понадобится в начале игры)
    void drawCellFromIndexes();
    void clean();


    /// Функции для дебага
    QString debugGetField();   // вывод значений поля
signals:
    void sendMouseCoord(int x, int y);
    void sendCountCells(int countCells);    // сигнал, передающий колличество расставленных клеток на поле
    void startEditingForEnemy();    // после того, как мы расставили свои ячейки, разрешим сделать это сопернику


public slots:
    virtual void endEditing();  // слот для отключения режима редактирования клеток
    void setName(const QString &name);  // слот для задания имени игрока
    virtual void startEditing();    // разрешать редактирование своих ячеек
    void drawPlayField();   // рисует поле с кораблями/попаданиями и прочие мимо
//    void starting();    // первоначальная настройка полей для игры после расстановки
    void getField();
};

#endif // FIELD_H
