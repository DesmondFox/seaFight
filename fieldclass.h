#ifndef FIELDCLASS_H
#define FIELDCLASS_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsItemGroup>
#include <QDebug>
#include <QTimer>
#include <QMouseEvent>


class FieldClass : public QGraphicsView
{
    Q_OBJECT

public:
    FieldClass(QWidget *parent  = 0);

protected:
    QTimer *timer;
    int cellSize;
    int zero_x;
    int zero_y;

    QGraphicsScene *scene;
    QGraphicsItemGroup *groupField;

    void deleteItems(QGraphicsItemGroup *gr);

    virtual void mousePressEvent(QMouseEvent *event);



public slots:
    void drawField();
};

#endif // FIELDCLASS_H
