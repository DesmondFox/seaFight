#ifndef FIELD_H
#define FIELD_H

#include <QMessageBox>
#include <QVector>
#include <QMouseEvent>
#include "fieldclass.h"
#include "ship.h"
#include "kicks.h"


class Field : public FieldClass
{
    Q_OBJECT

public:
    Field(QWidget *parent = 0);

protected:
    int FIELD[10][10];  // поле с кораблями и тд и тп
    QGraphicsItemGroup *groupShips;
    QGraphicsItemGroup *groupPermission;
    QGraphicsItemGroup *groupForbidden;
    QGraphicsItemGroup *groupKicks;
    QGraphicsItemGroup *groupOneCell;
    QGraphicsItemGroup *groupMiss;

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

    bool drawGhostShip(const Ship &sh, QColor color);
    void drawShip(const Ship &sh, QColor color = QColor(255, 255, 255));
    void drawFullField();
    void drawSimpleShip(const Ship &sh);
    void drawSimpleKick(const Kicks &kick);
    void drawAllKicks();
    void drawOneCell(int i, int j);
    void drawMissCell(int i, int j);

    position currentPosition;
    bool permissionToPaste;
    bool setShipFlag; // режим настройки положения кораблей в начале
    bool battleMode;

    int age;    // для правильного расположения кораблей
    Ship tmpShip;
    QVector<Ship> ships;
    QVector<Kicks> kicks;

    int i;
    int j;
    int tmpi;
    int tmpj;

public slots:
    void DEBUGGetField();
    void setPermission(bool stt);
    void clearField();
    void setBattleMode(bool bmode);

signals:
    void done();
    void injured(int i, int j, bool full);
    void miss(int i, int j);
    void endGame();
};

#endif // FIELD_H
