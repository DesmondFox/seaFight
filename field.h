#ifndef FIELD_H
#define FIELD_H

#include <QMessageBox>
#include <QVector>
#include <QMouseEvent>
#include "fieldclass.h"
#include "ship.h"

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

    virtual bool drawGhostShip(const Ship &sh, QColor color);
    virtual void drawShip(const Ship &sh, QColor color = QColor(255, 255, 255));
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

    position currentPosition;
    bool permissionToPaste;
    bool setShipFlag; // режим настройки положения кораблей в начале

    int age;    // для правильного расположения кораблей
    Ship tmpShip;
    QVector<Ship> ships;
    int i;
    int j;
    int tmpi;
    int tmpj;

public slots:
    void DEBUGGetField();

};

#endif // FIELD_H
