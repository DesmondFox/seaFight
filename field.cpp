#include "field.h"

Field::Field(QWidget *parent) : QWidget(parent)
{
    pm = new QPixmap();
    pm->fill();

    // очищаем массив клеток на всякий случай
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            FIELD[i][j] = 0;

    // теперь отслеживается перемещение мыши по полю
    this->setMouseTracking(true);

    currentx = currenty = -1;
    setCellsModeFlag = true;

    /// temp
    age = 0;
    FIELD[5][4] = 1;
    drawFieldCells();
    tmpStatusToPress = false;
    currentPosition = horizontal;
}

void Field::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(zero_x, zero_y, width, height, *pm);
}

void Field::drawField()
{
    QPainter pntr(pm);
    // нарисуем рамку
    pntr.setPen(QPen(Qt::black, 1, Qt::SolidLine));
    pntr.drawRect(QRect(QPoint(zero_x, zero_y), QPoint(width-2, height-2)));

    // Теперь нарисуем собственно деления/cells
    pntr.setPen(QPen(Qt::gray, 1, Qt::SolidLine));
    cellSize = width / 11;
    for (int i = 2; i < 11; i++)
    {
        pntr.drawLine(QPoint(i*cellSize, zero_y), QPoint(i*cellSize, height));
        pntr.drawLine(QPoint(zero_x, i*cellSize), QPoint(width, i*cellSize));
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

                Ship s(currentx, currenty, 2, currentPosition);
                if (tmpStatusToPress)
                {
                    drawShip(s);
                    ships.append(s);
                }


                update();
            }
            else
            {
                currenty = -1;
                currentx = -1;
            }
        }
        if (event->button() == Qt::RightButton)
            currentPosition = currentPosition == horizontal ? vertical : horizontal;
    }

    emit sendMouseCoord(event->x(), event->y(), currentx, currenty);
}

void Field::mouseMoveEvent(QMouseEvent *event)
{
    // TODO: Уменьшить нагрузку. Сделать, чтобы проверка была на каждой клетке, а не пикселе
    if ((event->x() > cellSize+zero_x) && (event->y() > cellSize+zero_y))
    {
        if (setCellsModeFlag)
        {
            c_x = (event->x() - cellSize - zero_x) / cellSize + 1;
            c_y = (event->y() - cellSize - zero_y) / cellSize + 1;

            clean();
            drawField();

            Ship s(c_y, c_x, 2, currentPosition);
            tmpStatusToPress = drawGhostCell(s, tmpStatusToPress ? QColor(0, 150, 0, 100) : QColor(150, 0, 0, 100));
            qDebug() << "Status: " << tmpStatusToPress << " " << c_x << " - " << c_y;

        }
    }
    drawFieldCells();
    update();

}

void Field::drawShip(const Ship &sh, QColor color)
{
    // Б Ы Д Л О К О Д
    // Ы Ы
    // Д   Д
    // Л     Л
    // О       О
    // К         К
    // О           О
    // Д             Д

    QPainter p(pm);
    p.setPen(QPen(color));
    p.setBrush(QBrush(color));
    for (int i = 0; i < sh.numberOfDecks; i++)
        p.drawRect(QRect(sh.shipCell[i].j*cellSize+1, sh.shipCell[i].i*cellSize+1, cellSize-2, cellSize-2));
    for (int i = 0; i < sh.numberOfDecks; i++)
    {
        FIELD[sh.shipCell[i].i-1][sh.shipCell[i].j-1] = 1;
    }

    int tmpi_min = sh.shipCell[0].i-1;
    int tmpj_min = sh.shipCell[0].j-1;
    int tmpi_max = sh.shipCell[sh.shipCell.length()-1].i - 1;
    int tmpj_max = sh.shipCell[sh.shipCell.length()-1].j - 1;

    qDebug() << tmpi_min << tmpi_max << tmpj_min << tmpj_max;
    for (int i = tmpi_min - 1; i <= tmpi_max+1; i++)
    {
        if (tmpj_min - 1 >= 0 && i >= 0)
            FIELD[i][tmpj_min-1] = 5;
        if (tmpj_max < 9 && i >= 0 && i < 10)
            FIELD[i][tmpj_max+1] = 5;

    }



    if (sh.positionOfShip == horizontal)
    {

    }



}

bool Field::drawGhostCell(const Ship &sh, QColor color)
{
    QPainter p(pm);

    p.setBrush(QBrush(color));
    p.setPen(QPen(color));

    for (int i = 0; i < sh.numberOfDecks; i++)
        p.drawRect(QRect(sh.shipCell[i].j*cellSize+1, sh.shipCell[i].i*cellSize+1, cellSize-2, cellSize-2));
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

void Field::drawFieldCells()
{
    QPainter pn(pm);

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
        {
            if (FIELD[i][j] == 1)
            {
                pn.setPen(QPen(Qt::blue));
                pn.drawRect(QRect((j+1)*cellSize+1, (i+1)*cellSize+1, cellSize-2, cellSize-2));
            }
            if (FIELD[i][j] == 5)
            {
                pn.setPen(QPen(Qt::lightGray));
                pn.drawRect(QRect((j+1)*cellSize+1, (i+1)*cellSize+1, cellSize-2, cellSize-2));
            }
        }

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

