#include "field.h"

Field::Field(QWidget *parent)   : FieldClass(parent)
{
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            FIELD[i][j] = 0;

    groupPermission = new QGraphicsItemGroup;
    groupShips = new QGraphicsItemGroup;
    groupForbidden = new QGraphicsItemGroup;
    groupKicks = new QGraphicsItemGroup;
    groupOneCell = new QGraphicsItemGroup;
    groupMiss = new QGraphicsItemGroup;
    groupInj = new QGraphicsItemGroup;

    setMouseTracking(true);

    scene->addItem(groupPermission);
    scene->addItem(groupShips);
    scene->addItem(groupForbidden);
    scene->addItem(groupKicks);
    scene->addItem(groupOneCell);
    scene->addItem(groupMiss);
    scene->addItem(groupInj);

    currentPosition = horizontal;
    permissionToPaste = false;
    i = j = -1;
    tmpi = tmpj = -1;

    setShipFlag = true;
    age = 0;

    tmpShip.setData(1, 1, 4, currentPosition);

    battleMode = false;
    tipsMode = true;
}

void Field::drawOneCell(indexes ind)
{
    //
    //  Метод для рисовки одной серой клетки при наведении курсора на клетки
    //

    QPen penCell(QColor(10, 10, 10, 50));
    QBrush cellBrush(QColor(10, 10, 10, 20));

    groupOneCell->addToGroup(scene->addRect(QRectF(ind.j*cellSize+1, ind.i*cellSize+1, cellSize-2, cellSize-2), penCell, cellBrush));
}

void Field::drawTip(const Ship &sh)
{
    //
    //  Метод для обводки убитых кораблей
    //

    QPen penTip(QColor(226, 226, 245));
    QBrush brushTip(QColor(226, 226, 245));

    //
    // Далее код почти целиком копируется из метода drawShip();
    //

    // Получаем индексы противоположных концов корабля
    int tmpi_min = sh.shipCell[0].i-1;
    int tmpj_min = sh.shipCell[0].j-1;
    int tmpi_max = sh.shipCell[sh.shipCell.length()-1].i - 1;
    int tmpj_max = sh.shipCell[sh.shipCell.length()-1].j - 1;

    // Заполнение соседних клеток пятерками по вертикали
    for (int i = tmpi_min - 1; i <= tmpi_max+1; i++)
    {
        if (i < 10 && i >= 0 && tmpj_min > 0)
        {
            FIELD[i][tmpj_min-1] = 5;
            groupMiss->addToGroup(scene->addRect(QRectF(tmpj_min*cellSize+1, (i+1)*cellSize+1, cellSize-2, cellSize-2), penTip, brushTip));
        }

        if (i >= 0 && i < 10 && tmpj_max < 9)
        {
            FIELD[i][tmpj_max+1] = 5;
            groupMiss->addToGroup(scene->addRect(QRectF((tmpj_max+2)*cellSize+1, (i+1)*cellSize+1, cellSize-2, cellSize-2), penTip, brushTip));
        }
    }

    // Заполнение соседних клеток по горизонтали
    for (int i = tmpj_min - 1; i <= tmpj_max + 1; i++)
    {
        if (tmpj_min >= 0 && i >= 0 && i < 10 && tmpi_min > 0)
        {
            FIELD[tmpi_min-1][i] = 5;
            groupMiss->addToGroup(scene->addRect(QRectF((i+1)*cellSize+1, tmpi_min*cellSize+1, cellSize-2, cellSize-2), penTip, brushTip));
        }

        if (tmpi_max < 9 && i >= 0 && i < 10)
        {
            FIELD[tmpi_max+1][i] = 5;
            groupMiss->addToGroup(scene->addRect(QRectF((i+1)*cellSize+1, (tmpi_max+2)*cellSize+1, cellSize-2, cellSize-2), penTip, brushTip));
        }
    }

}



void Field::drawMissCell(indexes ind)
{
    //
    //  Метод для рисовки удара "мимо" по полю
    //

    QPen penMiss(QColor(226, 226, 245));
    QBrush brushMiss(QColor(226, 226, 245));

    groupMiss->addToGroup(scene->addRect(ind.i*cellSize+1, ind.j*cellSize+1, cellSize-2, cellSize-2, penMiss, brushMiss));
}

void Field::drawInjCell(indexes ind, QColor color)
{
    //
    // метод для рисовки удара "попал" или "убил" по полю
    //

    QPen penInj(color);
    color.setAlpha(150);
    QBrush brushInj(color);

    groupInj->addToGroup(scene->addRect(ind.i*cellSize+1, ind.j*cellSize+1, cellSize-2, cellSize-2, penInj, brushInj));
}

void Field::drawShip(const Ship &sh, QColor color)
{
    //
    //  метод для рисовки и занесения в массив корабля на поле
    //
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

bool Field::drawGhostShip(const Ship &sh, QColor color, bool show)
{
    //
    //  Метод для рисовки корабля для получения разрешения на установку его на поле
    //

    if (show)
    {
        QPen penForbidden(color);

        for (int i = 0; i < sh.numberOfDecks; i++)
            groupPermission->addToGroup(scene->addRect(QRectF(sh.shipCell[i].j*cellSize+1, sh.shipCell[i].i*cellSize+1, cellSize-2, cellSize-2), penForbidden));

    }

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

void Field::DEBUGGetField()
{
    //  Метод для дебага
    //  Метод для вывода значения массива
    //

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

bool Field::hit(indexes ind)
{
    // Метод для нанесения удара по кораблям
    //
    // [15/10/2016 11:36] Есть редкий баг с вылетом за грань вектора. Вылетает редко, поэтому отловить его нереально
    // [15/10/2016 12:02] возможно, уже пофикшено

    int i = ind.i;
    int j = ind.j;
    bool result;

    if (FIELD[j-1][i-1] == 1)
    {
        result = true;
        FIELD[j-1][i-1] = 3;
        for (int m = 0; m < ships.length(); m++)
        {
            for (int n = 0; n < ships[m].shipCell.length(); n++)
            {
                if (ships[m].shipCell[n].i == j && ships[m].shipCell[n].j == i)
                {
                    ships[m].shipCell[n].stt = st_injured;
                    bool full = false;  // запишем, убиваем ли мы корабль, или только раним

                    for (int t = 0; t < ships[m].shipCell.length(); t++)
                        if (ships[m].shipCell[t].stt == st_alive)
                            break;
                        else
                            if (t+1 == ships[m].shipCell.length())
                                full = true;

                    if (full && tipsMode)
                        drawTip(ships[m]);



                    qDebug() << "INGURED" << j << i << (!full ? "injured" : "killed");
                    emit injured(i, j, full);

                    indexes ind;
                    ind.i = i;
                    ind.j = j;
                    drawInjCell(ind);

                    if (full)
                    {
                        ships.remove(m);
                        break;
                    }
                }
            }
        }
    }

    if ((FIELD[j-1][i-1] == 5) || (FIELD[j-1][i-1] == 0))
    {
        emit miss(i, j);
        indexes indMiss;
        indMiss.i = i;
        indMiss.j = j;
        drawMissCell(indMiss);
        result = false;
    }

    // Обязательная поверка поля, убили ли мы всех кораблей.
    // В таком случае даем сигнал о завершении игры
    if (ships.isEmpty())
        emit endGame();

    return result;


}

void Field::clearField()
{
    //
    // Метод для очистки поля для последующей игры
    // удаляет корабли из поля и обводку возле него

    deleteItems(groupShips);
    deleteItems(groupForbidden);
}

void Field::randShips()
{
    //
    //  Метод для расстановки кораблей в случайном порядке
    //

    QTime seed(0, 0, 0);
    qsrand(seed.secsTo(QTime::currentTime()));

    indexes tmpInd;
    position tmpPosition;

    while (true)
    {
        tmpInd.i = qrand() % 10+1;
        tmpInd.j = qrand() % 10+1;
        int tmpPos = qrand() % 2;
        tmpPosition = tmpPos == 1 ? horizontal : vertical;

        int decks;

        if (age == 0)               decks = 4;
        if (age >= 1 && age <= 2)   decks = 3;
        if (age >= 3 && age <= 5)   decks = 2;
        if (age >= 6 && age <= 9)   decks = 1;

        tmpShip.setData(tmpInd.j, tmpInd.i, decks, tmpPosition);
        permissionToPaste = drawGhostShip(tmpShip, permissionToPaste ? QColor(0, 255, 0) : QColor(255, 0, 0), false);


        if (permissionToPaste)
        {
            ships.push_back(tmpShip);
            drawShip(tmpShip, QColor(Qt::black));
            age++;
            if (age == 10)
            {
                setShipFlag = false;
                emit done();
                break;
            }
        }
    }




}

void Field::mousePressEvent(QMouseEvent *event)
{
    //
    // Обработка нажатия клавиш мыши по полю
    //

    if (!(event->x() < zero_x || event->y() < zero_x))
    {
        if (event->button() == Qt::RightButton)
        {
            currentPosition = currentPosition == horizontal ? vertical : horizontal;
        }

        qDebug() << event->x() << event->y();

        if (event->button() == Qt::LeftButton)
        {
            if (!(setShipFlag || battleMode))
                emit notBattleMode();

            if (setShipFlag)
                checkShips();
            if (battleMode)
            {
                indexes ind;
                ind.i = i;
                ind.j = j;
                qDebug() << hit(ind);
            }
        }
    }
}

void Field::checkShips()
{
//    if (age <= 9)
//    {
        int decks;

        if (age == 0)               decks = 4;
        if (age >= 1 && age <= 2)   decks = 3;
        if (age >= 3 && age <= 5)   decks = 2;
        if (age >= 6 && age <= 9)   decks = 1;

        if (permissionToPaste && setShipFlag)
        {
            tmpShip.setData(j, i, decks, currentPosition);
            ships.push_back(tmpShip);
            drawShip(tmpShip, QColor(Qt::black));
            age++;
            if (age == 10)
            {
                setShipFlag = false;
                emit done();
            }
        }
//    }
}

void Field::clearAll()
{
    deleteItems(groupForbidden);
    deleteItems(groupInj);
    deleteItems(groupKicks);
    deleteItems(groupMiss);
    deleteItems(groupOneCell);
    deleteItems(groupShips);
    deleteItems(groupPermission);

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            FIELD[i][j] = 0;

    currentPosition = horizontal;
    permissionToPaste = false;
    age = 0;
    i = j = -1;
    tmpi = tmpj = -1;

    tmpShip.setData(1, 1, 4, currentPosition);
    battleMode = false;
}

void Field::mouseMoveEvent(QMouseEvent *event)
{
    //
    //  Обработка наведения мыши по полю
    //

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
                    int decks;
                    if (age == 0)   decks = 4;
                    if (age >= 1 && age <= 2)   decks = 3;
                    if (age >= 3 && age <= 5)   decks = 2;
                    if (age >= 6 && age <= 9)   decks = 1;

                    tmpShip.setData(j, i, decks, currentPosition);
                    permissionToPaste = drawGhostShip(tmpShip, permissionToPaste ? QColor(0, 255, 0) : QColor(255, 0, 0));

                    qDebug() << permissionToPaste;
                }
            }
            if (battleMode)
            {
                indexes ind;
                ind.i = j;
                ind.j = i;
                drawOneCell(ind);
            }
        }
    }
    else
    {
        i = j = -1;
    }

}

void Field::setPermission(bool stt)
{
    //
    //  Метод для установки режима установки кораблей
    //

    setShipFlag = stt;
}

void Field::setBattleMode(bool bmode)
{
    //
    //  Метод для установки режима, когда мы можем бить по полю
    //

    battleMode = bmode;
}

void Field::setTips(bool tmode)
{
    //
    //  Метод для установки режима, когда мы рисуем обводку возле убитого корабля
    //

    tipsMode = tmode;
}
