#include "field.h"

Field::Field(QWidget *parent)   : FieldClass(parent)
{
    groupPermission = new QGraphicsItemGroup;
    groupShips = new QGraphicsItemGroup;
    groupForbidden = new QGraphicsItemGroup;
    setMouseTracking(true);

    scene->addItem(groupPermission);
    scene->addItem(groupShips);
    scene->addItem(groupForbidden);

    currentPosition = horizontal;
    permissionToPaste = false;
    i = j = -1;
    tmpi = tmpj = -1;

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            FIELD[i][j] = 0;

    setShipFlag = true;
    age = 0;
    tmpShip.setData(1, 1, 4, currentPosition);
}

void Field::drawShip(const Ship &sh, QColor color)
{
    QPen penShip(QBrush(color), 1);
    QPen penForb(Qt::lightGray);
    QBrush fillBrush(Qt::black, Qt::SolidPattern);

    for (int i = 0; i < sh.numberOfDecks; i++)
        groupShips->addToGroup(scene->addRect(QRectF(sh.shipCell[i].j*cellSize+1, sh.shipCell[i].i*cellSize+1, cellSize-2, cellSize-2), penShip, fillBrush));

    for (int i = 0; i < sh.numberOfDecks; i++)
        FIELD[sh.shipCell[i].i-1][sh.shipCell[i].j-1] = 1;

    // Получаем индексы противоположных концов корабля
    int tmpi_min = sh.shipCell[0].i-1;
    int tmpj_min = sh.shipCell[0].j-1;
    int tmpi_max = sh.shipCell[sh.shipCell.length()-1].i - 1;
    int tmpj_max = sh.shipCell[sh.shipCell.length()-1].j - 1;

    qDebug() << tmpi_min << tmpj_min << tmpi_max << tmpj_max;

    // Заполнение соседних клеток пятерками по вертикали
    for (int i = tmpi_min - 1; i <= tmpi_max+1; i++)
    {
        if (i < 10 && i >= 0 && tmpj_min > 0)
        {
            FIELD[i][tmpj_min-1] = 5;
            groupForbidden->addToGroup(scene->addRect(QRectF(tmpj_min*cellSize+1, (i+1)*cellSize+1, cellSize-2, cellSize-2), penForb));
        }

        if (i >= 0 && i < 10 && tmpj_max < 9)
        {
            FIELD[i][tmpj_max+1] = 5;
            groupForbidden->addToGroup(scene->addRect(QRectF((tmpj_max+2)*cellSize+1, (i+1)*cellSize+1, cellSize-2, cellSize-2), penForb));
        }
    }

    // Заполнение соседних клеток по горизонтали
    for (int i = tmpj_min - 1; i <= tmpj_max + 1; i++)
    {
        if (tmpj_min >= 0 && i >= 0 && i < 10 && tmpi_min > 0)
        {
            FIELD[tmpi_min-1][i] = 5;
            groupForbidden->addToGroup(scene->addRect(QRectF((i+1)*cellSize+1, tmpi_min*cellSize+1, cellSize-2, cellSize-2), penForb));
        }

        if (tmpi_max < 9 && i >= 0 && i < 10)
        {
            FIELD[tmpi_max+1][i] = 5;
            groupForbidden->addToGroup(scene->addRect(QRectF((i+1)*cellSize+1, (tmpi_max+2)*cellSize+1, cellSize-2, cellSize-2), penForb));
        }
    }

}

bool Field::drawGhostShip(const Ship &sh, QColor color)
{

    QPen penForbidden(color);


    for (int i = 0; i < sh.numberOfDecks; i++)
        groupPermission->addToGroup(scene->addRect(QRectF(sh.shipCell[i].j*cellSize+1, sh.shipCell[i].i*cellSize+1, cellSize-2, cellSize-2), penForbidden));


    for (int i = 0; i < sh.numberOfDecks; i++)
    {
        try
        {
            if (sh.shipCell[i].i > 10 || sh.shipCell[i].j > 10)
                return false;
        if (FIELD[sh.shipCell[i].i-1][sh.shipCell[i].j-1] != 0)
        {

            return false;
        }

        }
        catch(...)
        {
            return false;
        }
    }
    return true;
}

void Field::mousePressEvent(QMouseEvent *event)
{
    if (!(event->x() < zero_x || event->y() < zero_x))
    {
        if (event->button() == Qt::RightButton)
            currentPosition = currentPosition == horizontal ? vertical : horizontal;

        qDebug() << event->x() << event->y();

        if (event->button() == Qt::LeftButton)
        {
            if (age <= 9)
            {
                int tmp;

                if (age == 0)   tmp = 4;
                if (age >= 1 && age <= 2)   tmp = 3;
                if (age >= 3 && age <= 5)   tmp = 2;
                if (age >= 6 && age <= 9)   tmp = 1;

                Ship s(j, i, 3, currentPosition);
                if (permissionToPaste)
                {
                    tmpShip.setData(j, i, tmp, currentPosition);
                    ships.push_back(tmpShip);
                    drawShip(tmpShip, QColor(Qt::black));
                    age++;
                    if (age == 10)
                        setShipFlag = false;
                    // окончание расстановки кораблей

                }
            }


        }


    }

}

void Field::mouseMoveEvent(QMouseEvent *event)
{


    if (!(event->x() < zero_x || event->y() < zero_x))
    {
        i = (event->x() - cellSize - zero_x) / cellSize + 2;
        j = (event->y() - cellSize - zero_y) / cellSize + 2;
        if (event->x() <= 40)
            i = 1;
        if (event->y() <= 40)
            j = 1;

        if (i == tmpi && j == tmpj)
        {

        }
        else
        {

                this->deleteItems(groupPermission);
                tmpi = i;
                tmpj = j;
                qDebug() << i << j;
                if (setShipFlag)
                {
                    if (age <= 9)
                    {
                        int tmp;

                        if (age == 0)   tmp = 4;
                        if (age >= 1 && age <= 2)   tmp = 3;
                        if (age >= 3 && age <= 5)   tmp = 2;
                        if (age >= 6 && age <= 9)   tmp = 1;

                        tmpShip.setData(j, i, tmp, currentPosition);
                        permissionToPaste = drawGhostShip(tmpShip, permissionToPaste ? QColor(0, 255, 0) : QColor(255, 0, 0));

                        qDebug() << permissionToPaste;
                    }
                }





        }



    }
    else
    {
        i = j = -1;
    }

}

void Field::DEBUGGetField()
{
    QString temp;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            temp.append(QString::number(FIELD[i][j]));
        }
        temp.append("\n");
    }
    QMessageBox::information(this, "debug", temp);
}
