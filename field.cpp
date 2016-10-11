#include "field.h"

Field::Field(QWidget *parent)   : FieldClass(parent)
{
    groupPermission = new QGraphicsItemGroup;
    groupShips = new QGraphicsItemGroup;
    groupForbidden = new QGraphicsItemGroup;
    groupKicks = new QGraphicsItemGroup;
    groupOneCell = new QGraphicsItemGroup;
    groupMiss = new QGraphicsItemGroup;


    setMouseTracking(true);

    scene->addItem(groupPermission);
    scene->addItem(groupShips);
    scene->addItem(groupForbidden);
    scene->addItem(groupKicks);
    scene->addItem(groupOneCell);
    scene->addItem(groupMiss);

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

    battleMode = false;

    // tmp
}

void Field::drawOneCell(int i, int j)
{
    QPen penCell(QColor(10, 10, 10, 50));
    QBrush cellBrush(QColor(10, 10, 10, 20));

    groupOneCell->addToGroup(scene->addRect(QRectF(j*cellSize+1, i*cellSize+1, cellSize-2, cellSize-2), penCell, cellBrush));
}

void Field::drawSimpleKick(const Kicks &kick)
{
    QPen penKick(QColor(0, 0, 0));
    QPen penInjured(QColor(255, 0, 0));

    QBrush fillBrush(Qt::gray, Qt::SolidPattern);
    QBrush injBrush(Qt::red, Qt::Dense3Pattern);

    if (!kick.injured)
        groupKicks->addToGroup(scene->addRect(QRectF(kick.J*cellSize+1, kick.I*cellSize+1, cellSize-2, cellSize-2), penKick, fillBrush));
    else
        groupKicks->addToGroup(scene->addRect(QRectF(kick.J*cellSize+1, kick.I*cellSize+1, cellSize-2, cellSize-2), penInjured, injBrush));

}

void Field::drawSimpleShip(const Ship &sh)
{
    QPen penShip(QColor(0, 0, 0));
    QPen penInjured(QColor(255, 0, 0));
    QBrush fillBrush(Qt::black, Qt::SolidPattern);
    QBrush injBrush(Qt::red, Qt::SolidPattern);


    for (int i = 0; i < sh.numberOfDecks; i++)
        if (sh.shipCell[i].stt == st_alive)
            groupShips->addToGroup(scene->addRect(QRectF(sh.shipCell[i].j*cellSize+1, sh.shipCell[i].i*cellSize+1, cellSize-2, cellSize-2), penShip, fillBrush));
        else
            groupShips->addToGroup(scene->addRect(QRectF(sh.shipCell[i].j*cellSize+1, sh.shipCell[i].i*cellSize+1, cellSize-2, cellSize-2), penInjured, injBrush));


}

void Field::drawFullField()
{
    QPen penShip(QColor(0, 0, 0));
    QPen penForb(Qt::lightGray);

    clearField();

    for (int i = 0; i < ships.length(); i++)
    {
        drawSimpleShip(ships[i]);
    }

    for (int i = 0; i < kicks.length(); i++)
    {
        drawSimpleKick(kicks[i]);
    }


}

void Field::drawAllKicks()
{
    for (int i = 0; i < kicks.length(); i++)
    {
        drawSimpleKick(kicks[i]);
    }
}

void Field::drawMissCell(int i, int j)
{
    QPen penMiss(QColor(226, 226, 245));
    QBrush brushMiss(QColor(QColor(226, 226, 245)));

    groupMiss->addToGroup(scene->addRect(i*cellSize+1, j*cellSize+1, cellSize-2, cellSize-2));

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

void Field::clearField()
{
    deleteItems(groupShips);
    deleteItems(groupForbidden);


}

void Field::mousePressEvent(QMouseEvent *event)
{
    if (!(event->x() < zero_x || event->y() < zero_x))
    {
        if (event->button() == Qt::RightButton)
        {
            currentPosition = currentPosition == horizontal ? vertical : horizontal;
//            drawFullField();
        }


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

                if (permissionToPaste && setShipFlag)
                {
                    tmpShip.setData(j, i, tmp, currentPosition);
                    ships.push_back(tmpShip);
                    drawShip(tmpShip, QColor(Qt::black));
                    age++;
                    if (age == 10)
                    {
                        setShipFlag = false;
                        emit done();
                    }
                    // окончание расстановки кораблей

                }

            }
            if (battleMode)
            {
                if (FIELD[j-1][i-1] == 1)
                {
                    FIELD[j-1][i-1] = 3;
                    for (int m = 0; m < ships.length(); m++)
                    {
                        for (int n = 0; n < ships[m].shipCell.length(); n++)
                        {
                            if (ships[m].shipCell[n].i == j && ships[m].shipCell[n].j == i)
                            {

                                ships[m].shipCell[n].stt = st_injured;
                                bool tmp = false;

                                for (int t = 0; t < ships[m].shipCell.length(); t++)
                                    if (ships[m].shipCell[t].stt == st_alive)
                                        break;
                                    else
                                        if (t+1 == ships[m].shipCell.length())
                                            tmp = true;
                                qDebug() << "INGURED" << j << i << tmp;
                                emit injured(i, j, tmp);

                            }
                        }
                    }
                }

                if ((FIELD[j-1][i-1] == 5) || (FIELD[j-1][i-1] == 0))
                {
                    emit miss(i, j);
                    drawMissCell(i, j);
//                    FIELD[j-1][i-1] = 2;
                }
                bool tmp = false;
                for (int m = 0; m < ships.length(); m++)
                {
                    for (int n = 0; n < ships[m].shipCell.length(); n++)
                    {
                        if (ships[m].shipCell[n].stt == st_alive)
                        {
                            goto check;
                        }
                    }
                    if (m+1 == ships.length())
                        tmp = true;
                }

                check:
                    if (tmp)
                        emit endGame();

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
                this->deleteItems(groupOneCell);
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

                if (battleMode)
                {
                    drawOneCell(j, i);
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

void Field::setPermission(bool stt)
{
    setShipFlag = stt;
}

void Field::setBattleMode(bool bmode)
{
    battleMode = bmode;
}
