#ifndef FIELD_H
#define FIELD_H

#include <QMessageBox>
#include <QVector>
#include <QMouseEvent>
#include <QTime>
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
    QGraphicsItemGroup *groupInj;

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

    bool drawGhostShip(const Ship &sh, QColor color, bool show = true);
    void drawShip(const Ship &sh, QColor color = QColor(255, 255, 255));
//    void drawSimpleShip(const Ship &sh);
    void drawOneCell(indexes ind);
    void drawMissCell(indexes ind);
    void drawInjCell(indexes ind, QColor color = QColor(255, 0, 50));
    void drawTip(const Ship &sh);


    bool shoot(indexes ind);

    position currentPosition;
    bool permissionToPaste;
    bool setShipFlag; // режим настройки положения кораблей в начале
    bool battleMode;    // режим, когда мы можем стрелять по кораблям
    bool tipsMode;  // показ "подсказок" вокруг убитого корабля

    int age;    // для правильного расположения кораблей
    Ship tmpShip;
    QVector<Ship> ships;
    QVector<Kicks> kicks;

    int i;
    int j;
    int tmpi;
    int tmpj;

public slots:
    void setPermission(bool stt);
    void clearField();
    void setBattleMode(bool bmode);
    void setTips(bool tmode);
    bool hit(indexes ind);
    void DEBUGGetField();
    void randShips();   // Расставить корабли рандомно
    void clearAll();
    void checkShips();

signals:
    void done();
    void injured(int i, int j, bool full);
    void miss(int i, int j);
    void endGame();
    void notBattleMode();

    void sendCoords(indexes ind);
};

#endif // FIELD_H
