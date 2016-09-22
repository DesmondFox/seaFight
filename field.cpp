#include "field.h"

Field::Field(QWidget *parent) : QWidget(parent)
{
    pm = new QPixmap();
    pm->fill();

    currentx = 0;
    currenty = 0;
    // очищаем массив клеток на всякий случай
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            FIELD[i][j] = 0;

    // теперь отслеживается перемещение мыши по полю
    this->setMouseTracking(true);

    currentx = currenty = -1;

    /// TEMP
    setCellsModeFlag = true;

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
    cellSize = x / 11;
    for (int i = 2; i < 11; i++)
    {
        pntr.drawLine(QPoint(i*cellSize, zero_y), QPoint(i*cellSize, y));
        pntr.drawLine(QPoint(zero_x, i*cellSize), QPoint(x, i*cellSize));
    }
    QChar temp[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    for (int i = 0; i < 10; i++)
    {
        pntr.drawText(QRect(cellSize+i*cellSize+cellSize/2-2, 4, cellSize*2 + i*cellSize, cellSize-4), QString(temp[i]));
    }
    for (int i = 1; i < 11; i++)
    {
        pntr.drawText(QRect(4, cellSize*i+cellSize/2-7, cellSize-4, cellSize), QString::number(i));
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
            if ((event->x() > cellSize+zero_x) && (event->y() > cellSize+zero_y))
            {
                currenty = (event->x() - cellSize - zero_x) / cellSize + 1;
                currentx = (event->y() - cellSize - zero_y) / cellSize + 1;
            }
            else
            {
                currenty = -1;
                currentx = -1;
            }
        }
    }

    emit sendMouseCoord(event->x(), event->y(), currentx, currenty);
}

void Field::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->x() > cellSize+zero_x) && (event->y() > cellSize+zero_y))
    {

    }

    update();
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
        p.drawRect(QRect(cellx*cellSize+1, celly*cellSize+1, cellSize-2, cellSize-2));
        // И да, мы закидываем в метод drawGhostCell индексы клеток. т. е нумерация идет от 1 до 10.
        // А вот для массива, как известно, идет нумерация с 0 до 9 и по этому надо
        // минусовать единицу с проверки массива, ибо будет сдвиг (долго с этим возился)
//        if (checkNeightbourhood(cellx, celly, SL_1, HORIZONTAL))
//            if ((FIELD[celly-1][cellx-1] != 0))
//                return false;
//            else
//                return true;
//        else
//            return false;
    }

    if (pos == HORIZONTAL)
    {

        if (ship == SL_2)
        {
            p.drawRect(QRect(cellx*cellSize+1, celly*cellSize+1, cellSize-2, cellSize-2));
            p.drawRect(QRect(cellx*cellSize+cellSize+1, celly*cellSize+1, cellSize-2, cellSize-2));
            if ((FIELD[celly-1][cellx-1] != 0) || ((cellx + 1) > 10))
                return false;
            if ((FIELD[celly-1][cellx-1+1] != 0))
                return false;

            return true;
        }
        if (ship == SL_3)
        {
            p.drawRect(QRect(cellx*cellSize+1, celly*cellSize+1, cellSize-2, cellSize-2));
            p.drawRect(QRect(cellx*cellSize+cellSize+1, celly*cellSize+1, cellSize-2, cellSize-2));
            p.drawRect(QRect(cellx*cellSize+cellSize+cellSize+1, celly*cellSize+1, cellSize-2, cellSize-2));

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
            p.drawRect(QRect(cellx*cellSize+1, celly*cellSize+1, cellSize-2, cellSize-2));
            p.drawRect(QRect(cellx*cellSize+cellSize+1, celly*cellSize+1, cellSize-2, cellSize-2));
            p.drawRect(QRect(cellx*cellSize+cellSize+cellSize+1, celly*cellSize+1, cellSize-2, cellSize-2));
            p.drawRect(QRect(cellx*cellSize+cellSize+cellSize+cellSize+1, celly*cellSize+1, cellSize-2, cellSize-2));
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
            p.drawRect(QRect(cellx*cellSize+1, celly*cellSize+1, cellSize-2, cellSize-2));
            p.drawRect(QRect(cellx*cellSize+1, celly*cellSize+cellSize+1, cellSize-2, cellSize-2));
            if ((FIELD[celly-1][cellx-1] != 0) || ((celly + 1) > 10))
                return false;
            if (FIELD[celly-1+1][cellx-1] != 0)
                return false;
            return true;

        }
        if (ship == SL_3)
        {
            p.drawRect(QRect(cellx*cellSize+1, celly*cellSize+1, cellSize-2, cellSize-2));
            p.drawRect(QRect(cellx*cellSize+1, celly*cellSize+cellSize+1, cellSize-2, cellSize-2));
            p.drawRect(QRect(cellx*cellSize+1, celly*cellSize+cellSize+cellSize+1, cellSize-2, cellSize-2));
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
            p.drawRect(QRect(cellx*cellSize+1, celly*cellSize+1, cellSize-2, cellSize-2));
            p.drawRect(QRect(cellx*cellSize+1, celly*cellSize+cellSize+1, cellSize-2, cellSize-2));
            p.drawRect(QRect(cellx*cellSize+1, celly*cellSize+cellSize+cellSize+1, cellSize-2, cellSize-2));
            p.drawRect(QRect(cellx*cellSize+1, celly*cellSize+cellSize+cellSize+cellSize+1, cellSize-2, cellSize-2));
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
        pn.drawRect(QRect(cellx*cellSize+1, celly*cellSize+1, cellSize-2, cellSize-2));
    }
    if (cellType == CL_DOT)
    {
        pn.setBrush(QBrush(Qt::black));
        pn.setPen(QPen(Qt::black));
        // Немного костыльное решение
        pn.drawArc(QRect(cellx*cellSize+cellSize-12, celly*cellSize+cellSize-12, 5, 5), 0, 36000);
    }
    if (cellType == CL_INJURED)
    {
        pn.setBrush(QBrush(QColor(255, 0, 0, 140)));  // м.б. позже убрать альфу
        pn.setPen(QPen(QColor(255, 0, 0, 140)));
        pn.drawRect(QRect(cellx*cellSize+1, celly*cellSize+1, cellSize-2, cellSize-2));
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
        p.drawRect(QRect(cellx*cellSize+1, celly*cellSize+1, cellSize-2, cellSize-2));
        FIELD[celly-1][cellx-1] = 1;
    }

    if (pos == HORIZONTAL)
    {

        if (ship == SL_2)
        {
            p.drawRect(QRect(cellx*cellSize+1, celly*cellSize+1, cellSize-2, cellSize-2));
            p.drawRect(QRect(cellx*cellSize+cellSize+1, celly*cellSize+1, cellSize-2, cellSize-2));
            FIELD[celly-1][cellx-1] = 1;
            FIELD[celly-1][cellx] = 1;
        }
        if (ship == SL_3)
        {
            p.drawRect(QRect(cellx*cellSize+1, celly*cellSize+1, cellSize-2, cellSize-2));
            p.drawRect(QRect(cellx*cellSize+cellSize+1, celly*cellSize+1, cellSize-2, cellSize-2));
            p.drawRect(QRect(cellx*cellSize+cellSize+cellSize+1, celly*cellSize+1, cellSize-2, cellSize-2));
            FIELD[celly-1][cellx-1] = 1;
            FIELD[celly-1][cellx] = 1;
            FIELD[celly-1][cellx+1] = 1;
        }
        if (ship == SL_4)
        {
            p.drawRect(QRect(cellx*cellSize+1, celly*cellSize+1, cellSize-2, cellSize-2));
            p.drawRect(QRect(cellx*cellSize+cellSize+1, celly*cellSize+1, cellSize-2, cellSize-2));
            p.drawRect(QRect(cellx*cellSize+cellSize+cellSize+1, celly*cellSize+1, cellSize-2, cellSize-2));
            p.drawRect(QRect(cellx*cellSize+cellSize+cellSize+cellSize+1, celly*cellSize+1, cellSize-2, cellSize-2));
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
            p.drawRect(QRect(cellx*cellSize+1, celly*cellSize+1, cellSize-2, cellSize-2));
            p.drawRect(QRect(cellx*cellSize+1, celly*cellSize+cellSize+1, cellSize-2, cellSize-2));
            FIELD[celly-1][cellx-1] = 1;
            FIELD[celly][cellx-1] = 1;
        }
        if (ship == SL_3)
        {
            p.drawRect(QRect(cellx*cellSize+1, celly*cellSize+1, cellSize-2, cellSize-2));
            p.drawRect(QRect(cellx*cellSize+1, celly*cellSize+cellSize+1, cellSize-2, cellSize-2));
            p.drawRect(QRect(cellx*cellSize+1, celly*cellSize+cellSize+cellSize+1, cellSize-2, cellSize-2));
            FIELD[celly-1][cellx-1] = 1;
            FIELD[celly][cellx-1] = 1;
            FIELD[celly+1][cellx-1] = 1;
        }
        if (ship == SL_4)
        {
            p.drawRect(QRect(cellx*cellSize+1, celly*cellSize+1, cellSize-2, cellSize-2));
            p.drawRect(QRect(cellx*cellSize+1, celly*cellSize+cellSize+1, cellSize-2, cellSize-2));
            p.drawRect(QRect(cellx*cellSize+1, celly*cellSize+cellSize+cellSize+1, cellSize-2, cellSize-2));
            p.drawRect(QRect(cellx*cellSize+1, celly*cellSize+cellSize+cellSize+cellSize+1, cellSize-2, cellSize-2));
            FIELD[celly-1][cellx-1] = 1;
            FIELD[celly][cellx-1] = 1;
            FIELD[celly+1][cellx-1] = 1;
            FIELD[celly+2][cellx-1] = 1;
        }
    }
    update();
}

void Field::clean(QColor color)
{
    pm->fill(color);
}

void Field::DEBUGgetField()
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

