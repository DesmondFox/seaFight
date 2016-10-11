#include "fieldclass.h"

FieldClass::FieldClass(QWidget *parent)   : QGraphicsView(parent)
{
    scene = new QGraphicsScene(this);
    groupField = new QGraphicsItemGroup();

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    resize(220, 220);
//    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    this->setScene(scene);
    scene->addItem(groupField);

    timer = new QTimer();



    /// tmp
    cellSize = 20;
    zero_x = zero_y = 20;

//    connect(timer, SIGNAL(timeout()), this, SLOT(drawField()));
//    timer->start(1000);

//    drawField();


}

void FieldClass::drawField()
{
    this->deleteItems(groupField);
    int width = this->width();
    int height = this->height();

    qDebug() << "Scene size: " << width << height;

    scene->setSceneRect(0, 0, width, height);

    QPen penField(Qt::lightGray);

    for (int i = zero_x; i < width; i+=cellSize)
        groupField->addToGroup(scene->addLine(i, 20, i, width, penField));
    for (int i = zero_y; i < height; i+=cellSize)
        groupField->addToGroup(scene->addLine(20, i, height, i, penField));

    QChar chars[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    for (int i = 0; i < 10; i++)
    {
        QGraphicsSimpleTextItem *txt = new QGraphicsSimpleTextItem(chars[i]);
        txt->setPos(zero_x + i*cellSize + 10, 5);
        scene->addItem(txt);
    }
    for (int i = 1; i < 11; i++)
    {
        QGraphicsSimpleTextItem *txt = new QGraphicsSimpleTextItem(QString::number(i));
        txt->setPos(5, i*cellSize+3);
        scene->addItem(txt);
    }
}

void FieldClass::deleteItems(QGraphicsItemGroup *gr)
{
    foreach( QGraphicsItem *item, scene->items(gr->boundingRect())) {
        if(item->group() == gr ) {
            delete item;
        }
    }
}

void FieldClass::mousePressEvent(QMouseEvent *event)
{
    qDebug() << event->x() << event->y();
}


