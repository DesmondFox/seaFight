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

