#include "field.h"

Field::Field(QWidget *parent) : QWidget(parent)
{
    pm = new QPixmap();
    pm->fill();
    count = 0;  // первоначально на поле 0 расставленых клеток

    // очищаем массив клеток на всякий случай
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            FIELD[i][j] = 0;

    // теперь отслеживается перемещение мыши по полю
    this->setMouseTracking(true);

    currentx = currenty = -1;

    /// TEMP
    setCellsModeFlag = true;
    currentPosition = HORIZONTAL;
//    FIELD[5][5] = 1;
//    FIELD[5][6] = 1;
//    FIELD[0][0] = 1;
//    FIELD[1][5] = 2;
//    FIELD[1][6] = 2;
//    FIELD[2][5] = 3;
//    FIELD[3][5] = 3;
    countSL_1 = 0;
    countSL_2 = 0;
    countSL_3 = 0;
    countSL_4 = 0;

}

void Field::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(zero_x, zero_y, x, y, *pm);
}

void Field::drawField()
{
    QPainter pntr(pm);
    // нарисуем рамку
    pntr.setPen(QPen(Qt::black, 1, Qt::SolidLine));
    pntr.drawRect(QRect(QPoint(zero_x, zero_y), QPoint(x-2, y-2)));

    // Теперь нарисуем собственно деления/cells
    pntr.setPen(QPen(Qt::gray, 1, Qt::SolidLine));
    cell = x / 11;
    for (int i = 2; i < 11; i++)
    {
        pntr.drawLine(QPoint(i*cell, zero_y), QPoint(i*cell, y));
        pntr.drawLine(QPoint(zero_x, i*cell), QPoint(x, i*cell));
    }
    // pntr.setFont(QFont("Times New Roman", 12, 20));
    QChar temp[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    for (int i = 0; i < 10; i++)
    {
        pntr.drawText(QRect(cell+i*cell+cell/2-2, 4, cell*2 + i*cell, cell-4), QString(temp[i]));
    }
    for (int i = 1; i < 11; i++)
    {
        pntr.drawText(QRect(4, cell*i+cell/2-7, cell-4, cell), QString::number(i));
    }
    update();
    //drawLabels();


}

void Field::mousePressEvent(QMouseEvent *event)
{
    if (setCellsModeFlag)
    {
        if (event->button() == Qt::LeftButton)
        {
            if (tmpStatusPressFlag)
            {
//                if (countSL_4 >= 0 && countSL_4 != 1)
//                {
//                    drawShip(c_x, c_y, SL_4, currentPosition);
//                    countSL_4++;
//                    return;
//                }
//                if (countSL_3 >= 0 && countSL_3 != 2)
//                {
//                    drawShip(c_x, c_y, SL_3, currentPosition);
//                    countSL_3++;
//                    return;
//                }
//                if (countSL_2 >= 0 && countSL_2 != 3)
//                {
//                    drawShip(c_x, c_y, SL_2, currentPosition);
//                    countSL_2++;
//                    return;
//                }
                if (countSL_1 >= 0 && countSL_1 != 4)
                {
                    drawShip(c_x, c_y, SL_1, currentPosition);
                    countSL_1++;
                    return;
                }
//                drawShip(c_x, c_y, SL_4, currentPosition);

            }
            else
                QMessageBox::warning(this, "err", "Здесь нельзя ставить корабль");
        }

        if (event->button() == Qt::RightButton)
            currentPosition = currentPosition == HORIZONTAL ? VERTICAL : HORIZONTAL;
    }


    // Небольшая недоработка: корабль меняет положение, но это будет видно, если переместить курсор
    emit sendMouseCoord(event->x(), event->y());
}

void Field::mouseMoveEvent(QMouseEvent *event)
{
        if ((event->x() > cell+zero_x) && (event->y() > cell+zero_y))
        {

            // находим индексы для массива
            c_x = (event->x() - cell - zero_x) / cell + 1;
            c_y = (event->y() - cell - zero_y) / cell + 1;
            if ((c_x == currentx) && (c_y == currenty))
            {

            }
            else
            {

                if (setCellsModeFlag)
                {
                    clean();
                    drawField();
                    drawCellField();

//                    if (countSL_4 >= 0 && countSL_4 != 1)
//                    {
//                        tmpStatusPressFlag = drawGhostCell(c_x, c_y, SL_4, currentPosition);
//                        qDebug() << tmpStatusPressFlag;
//                        return;
//                    }
//                    if (countSL_3 >= 0 && countSL_3 != 2)
//                    {
//                        tmpStatusPressFlag = drawGhostCell(c_x, c_y, SL_3, currentPosition);
//                        qDebug() << tmpStatusPressFlag;
//                        return;
//                    }
//                    if (countSL_2 >= 0 && countSL_2 != 3)
//                    {
//                        tmpStatusPressFlag = drawGhostCell(c_x, c_y, SL_2, currentPosition);
//                        qDebug() << tmpStatusPressFlag;
//                        return;
//                    }
                    if (countSL_1 >= 0 && countSL_1 != 4)
                    {
                        tmpStatusPressFlag = drawGhostCell(c_x, c_y, SL_1, currentPosition);
                        qDebug() << tmpStatusPressFlag;
                        return;
                    }


                }
            }
        }
        else
        {
            c_x = -1;
            c_y = -1;
        }

    update();
}

bool Field::checkNeightborhood(int cellx, int celly, SHIPS ship, POSITION pos)
{
    int i = celly - 1;
    int j = cellx - 1;

    qDebug() << i << " -- " << j;
    if (ship == SL_1)
    {
        if (i == 0)
            if ((FIELD[i][j+1] == 0) && (FIELD[i+1][j+1] == 0) && (FIELD[i+1][j] == 0) && (FIELD[i+1][j-1] == 0) && (FIELD[i][j-1] == 0))
                return true;
        if (j == 0)
            if ((FIELD[i-1][j] == 0) && (FIELD[i+1][j-1] == 0) && (FIELD[i][j+1] == 0) && (FIELD[i+1][j+1] == 0) && (FIELD[i+1][j] == 0))
                return true;
        if (i == 0 && j == 0)
            if ((FIELD[i][j+1] == 0) && (FIELD[i+1][j+1] == 0) && (FIELD[i+1][j] == 0))
                return true;
        if (i != 0 && j != 0)
            if ()
    }
    if (pos == HORIZONTAL)
    {

    }
    if (pos == VERTICAL)
    {

    }
    return false;
}

bool Field::drawGhostCell(int cellx, int celly, SHIPS ship, POSITION pos, QColor color)
{
    QPainter p(pm);

    p.setBrush(QBrush(color));
    p.setPen(QPen(color));
    // Рисование клеток
    // Очень плохой код, очень. Серьёзно
    // Какой-то индусский код тут
    if (ship == SL_1)
    {
        p.drawRect(QRect(cellx*cell+1, celly*cell+1, cell-2, cell-2));
        // И да, мы закидываем в метод drawGhostCell индексы клеток. т. е нумерация идет от 1 до 10.
        // А вот для массива, как известно, идет нумерация с 0 до 9 и по этому надо
        // минусовать единицу с проверки массива, ибо будет сдвиг (долго с этим возился)
        if (checkNeightborhood(cellx, celly, SL_1, HORIZONTAL))
            if ((FIELD[celly-1][cellx-1] != 0))
                return false;
            else
                return true;
        else
            return false;
    }

    if (pos == HORIZONTAL)
    {

        if (ship == SL_2)
        {
            p.drawRect(QRect(cellx*cell+1, celly*cell+1, cell-2, cell-2));
            p.drawRect(QRect(cellx*cell+cell+1, celly*cell+1, cell-2, cell-2));
            if ((FIELD[celly-1][cellx-1] != 0) || ((cellx + 1) > 10))
                return false;
            if ((FIELD[celly-1][cellx-1+1] != 0))
                return false;

            return true;
        }
        if (ship == SL_3)
        {
            p.drawRect(QRect(cellx*cell+1, celly*cell+1, cell-2, cell-2));
            p.drawRect(QRect(cellx*cell+cell+1, celly*cell+1, cell-2, cell-2));
            p.drawRect(QRect(cellx*cell+cell+cell+1, celly*cell+1, cell-2, cell-2));

            // Сам по себе этот момент некорректен, надо будет позже как-то сделать так,
            // чтобы это всё входило в одно условие. И так в каждом
            if ((FIELD[celly-1][cellx-1] != 0) || ((cellx + 2) > 10))
                return false;
            if (FIELD[celly-1][cellx-1+1] != 0)
                return false;
            if (FIELD[celly-1][cellx-1+2] != 0)
                return false;
            return true;
        }
        if (ship == SL_4)
        {
            p.drawRect(QRect(cellx*cell+1, celly*cell+1, cell-2, cell-2));
            p.drawRect(QRect(cellx*cell+cell+1, celly*cell+1, cell-2, cell-2));
            p.drawRect(QRect(cellx*cell+cell+cell+1, celly*cell+1, cell-2, cell-2));
            p.drawRect(QRect(cellx*cell+cell+cell+cell+1, celly*cell+1, cell-2, cell-2));
            if ((FIELD[celly-1][cellx-1] != 0) || ((cellx + 3) > 10))
                return false;

            if (FIELD[celly-1][cellx-1+1] != 0)
                return false;
            if (FIELD[celly-1][cellx-1+2] != 0)
                return false;
            if (FIELD[celly-1][cellx-1+3] != 0)
                return false;
            return true;
        }
    }
    if (pos == VERTICAL)
    {
        if (ship == SL_2)
        {
            p.drawRect(QRect(cellx*cell+1, celly*cell+1, cell-2, cell-2));
            p.drawRect(QRect(cellx*cell+1, celly*cell+cell+1, cell-2, cell-2));
            if ((FIELD[celly-1][cellx-1] != 0) || ((celly + 1) > 10))
                return false;
            if (FIELD[celly-1+1][cellx-1] != 0)
                return false;
            return true;

        }
        if (ship == SL_3)
        {
            p.drawRect(QRect(cellx*cell+1, celly*cell+1, cell-2, cell-2));
            p.drawRect(QRect(cellx*cell+1, celly*cell+cell+1, cell-2, cell-2));
            p.drawRect(QRect(cellx*cell+1, celly*cell+cell+cell+1, cell-2, cell-2));
            if ((FIELD[celly-1][cellx-1] != 0) || ((celly + 2) > 10))
                return false;
            if (FIELD[celly-1+1][cellx-1] != 0)
                return false;
            if (FIELD[celly-1+2][cellx-1] != 0)
                return false;
            return true;
        }
        if (ship == SL_4)
        {
            p.drawRect(QRect(cellx*cell+1, celly*cell+1, cell-2, cell-2));
            p.drawRect(QRect(cellx*cell+1, celly*cell+cell+1, cell-2, cell-2));
            p.drawRect(QRect(cellx*cell+1, celly*cell+cell+cell+1, cell-2, cell-2));
            p.drawRect(QRect(cellx*cell+1, celly*cell+cell+cell+cell+1, cell-2, cell-2));
            if ((FIELD[celly-1][cellx-1] != 0) || ((celly + 3) > 10))
                return false;
            if (FIELD[celly-1+1][cellx-1] != 0)
                return false;
            if (FIELD[celly-1+2][cellx-1] != 0)
                return false;
            if (FIELD[celly-1+3][cellx-1] != 0)
                return false;
            return true;
        }
    }
    return false;
}

void Field::drawOneCell(int cellx, int celly, CELLS cellType)
{
    // Да, я сделал отдельный метод для рисовки ОДНОЙ клетки.
    // так будет лучше, имхо.
    QPainter pn(pm);
    if (cellType == CL_CELL)
    {
        pn.setBrush(Qt::black);
        pn.setPen(QPen(Qt::black));
        pn.drawRect(QRect(cellx*cell+1, celly*cell+1, cell-2, cell-2));
    }
    if (cellType == CL_DOT)
    {
        pn.setBrush(QBrush(Qt::black));
        pn.setPen(QPen(Qt::black));
        // Немного костыльное решение
        pn.drawArc(QRect(cellx*cell+cell-12, celly*cell+cell-12, 5, 5), 0, 36000);
    }
    if (cellType == CL_INJURED)
    {
        pn.setBrush(QBrush(QColor(255, 0, 0, 140)));  // м.б. позже убрать альфу
        pn.setPen(QPen(QColor(255, 0, 0, 140)));
        pn.drawRect(QRect(cellx*cell+1, celly*cell+1, cell-2, cell-2));
    }
    update();
}

void Field::drawCellField()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (FIELD[j][i] == 1)
                drawOneCell(i+1, j+1, CL_CELL);
            if (FIELD[j][i] == 2)
                drawOneCell(i+1, j+1, CL_DOT);
            if (FIELD[j][i] == 3)
                drawOneCell(i+1, j+1, CL_INJURED);
        }
    }

}

void Field::drawShip(int cellx, int celly, SHIPS ship, POSITION pos)
{
    QPainter p(pm);

    p.setBrush(QBrush(Qt::black));
    p.setPen(QPen(Qt::black));

    if (ship == SL_1)
    {
        p.drawRect(QRect(cellx*cell+1, celly*cell+1, cell-2, cell-2));
        FIELD[celly-1][cellx-1] = 1;
    }

    if (pos == HORIZONTAL)
    {

        if (ship == SL_2)
        {
            p.drawRect(QRect(cellx*cell+1, celly*cell+1, cell-2, cell-2));
            p.drawRect(QRect(cellx*cell+cell+1, celly*cell+1, cell-2, cell-2));
            FIELD[celly-1][cellx-1] = 1;
            FIELD[celly-1][cellx] = 1;
        }
        if (ship == SL_3)
        {
            p.drawRect(QRect(cellx*cell+1, celly*cell+1, cell-2, cell-2));
            p.drawRect(QRect(cellx*cell+cell+1, celly*cell+1, cell-2, cell-2));
            p.drawRect(QRect(cellx*cell+cell+cell+1, celly*cell+1, cell-2, cell-2));
            FIELD[celly-1][cellx-1] = 1;
            FIELD[celly-1][cellx] = 1;
            FIELD[celly-1][cellx+1] = 1;
        }
        if (ship == SL_4)
        {
            p.drawRect(QRect(cellx*cell+1, celly*cell+1, cell-2, cell-2));
            p.drawRect(QRect(cellx*cell+cell+1, celly*cell+1, cell-2, cell-2));
            p.drawRect(QRect(cellx*cell+cell+cell+1, celly*cell+1, cell-2, cell-2));
            p.drawRect(QRect(cellx*cell+cell+cell+cell+1, celly*cell+1, cell-2, cell-2));
            FIELD[celly-1][cellx-1] = 1;
            FIELD[celly-1][cellx] = 1;
            FIELD[celly-1][cellx+1] = 1;
            FIELD[celly-1][cellx+2] = 1;
        }
    }
    if (pos == VERTICAL)
    {
        if (ship == SL_2)
        {
            p.drawRect(QRect(cellx*cell+1, celly*cell+1, cell-2, cell-2));
            p.drawRect(QRect(cellx*cell+1, celly*cell+cell+1, cell-2, cell-2));
            FIELD[celly-1][cellx-1] = 1;
            FIELD[celly][cellx-1] = 1;
        }
        if (ship == SL_3)
        {
            p.drawRect(QRect(cellx*cell+1, celly*cell+1, cell-2, cell-2));
            p.drawRect(QRect(cellx*cell+1, celly*cell+cell+1, cell-2, cell-2));
            p.drawRect(QRect(cellx*cell+1, celly*cell+cell+cell+1, cell-2, cell-2));
            FIELD[celly-1][cellx-1] = 1;
            FIELD[celly][cellx-1] = 1;
            FIELD[celly+1][cellx-1] = 1;
        }
        if (ship == SL_4)
        {
            p.drawRect(QRect(cellx*cell+1, celly*cell+1, cell-2, cell-2));
            p.drawRect(QRect(cellx*cell+1, celly*cell+cell+1, cell-2, cell-2));
            p.drawRect(QRect(cellx*cell+1, celly*cell+cell+cell+1, cell-2, cell-2));
            p.drawRect(QRect(cellx*cell+1, celly*cell+cell+cell+cell+1, cell-2, cell-2));
            FIELD[celly-1][cellx-1] = 1;
            FIELD[celly][cellx-1] = 1;
            FIELD[celly+1][cellx-1] = 1;
            FIELD[celly+2][cellx-1] = 1;
        }
    }
    update();
}


// Скорее всего этот метод я удалю. Не нужен он. Рисовкой будет заниматься отдельный метод,
// который будет ставить корабли целиком, а не по одному.
/// TODO: Удалить метод. Создать метод для рисовки целого корабля, а не поклеточно
void Field::drawCelltmp(int x, int y/*, CELLS cellType = CL_CELL*/, CELLS cellType)
{
    // индексы для массива клеток
    // ВНИМАНИЕ, их надо в индексах будет поменять местами
    QPainter pntr(pm);

    if ((x > cell+zero_x) && (y > cell+zero_y))
    {
        // находим индексы для массива
        c_x = (x - cell - zero_x) / cell + 1;
        c_y = (y - cell - zero_y) / cell + 1;
    }
    else
    {
        c_x = -1;
        c_y = -1;
        return;
    }
    try
    {
        if (cellType == CL_EMPTY)   //  0
        {
            pntr.setBrush(QBrush(Qt::white));
            pntr.setPen(QPen(Qt::white));
            pntr.drawRect(QRect(c_x*cell+1, c_y*cell+1, cell-2, cell-2));
            if (FIELD[c_y-1][c_x-1] == 1)
            {
                FIELD[c_y-1][c_x-1] = 0;    // заполняем наш массив клеток
                count--;
                emit sendCountCells(count);
            }

        }
        if (cellType == CL_CELL)    //  1
        {
            pntr.setBrush(QBrush(Qt::black));
            pntr.setPen(QPen(Qt::black));
            pntr.drawRect(QRect(c_x*cell+1, c_y*cell+1, cell-2, cell-2));
            if (FIELD[c_y-1][c_x-1] == 0)
            {
                FIELD[c_y-1][c_x-1] = 1;
                count++;
                emit sendCountCells(count);
            }
        }
        if (cellType == CL_DOT)     //  2
        {
            pntr.setBrush(QBrush(Qt::black));
            pntr.setPen(QPen(Qt::black));
            // рисование круга небольшим костылем, т.к. я не знал,
            // как его сделать ровно по центру клетки
            pntr.drawArc(QRect(c_x*cell+cell-12, c_y*cell+cell-12, 5, 5), 0, 36000);
            FIELD[c_y-1][c_x-1] = 2;
        }
        if (cellType == CL_INJURED) //  3 - т.е раненая клетка
        {
            pntr.setBrush(QBrush(QColor(255, 0, 0, 140)));  // м.б. позже убрать альфу
            pntr.setPen(QPen(QColor(255, 0, 0, 140)));
            pntr.drawRect(QRect(c_x*cell+1, c_y*cell+1, cell-2, cell-2));
            FIELD[c_y-1][c_x-1] = 3;
        }


    }
    catch (...)
    {

    }
    update();
}

void Field::clean(QColor color)
{
    pm->fill(color);
}

void Field::setName(const QString &name)
{
    if (!name.isEmpty())
        playerName = name;
}

QString Field::debugGetField()
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
    return temp;
}

void Field::getField()
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

