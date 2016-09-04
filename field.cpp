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
    setMouseTracking(true);
    if (event->button() == Qt::LeftButton)
    {
//        if (editingMode == true)
            drawCell(event->x(), event->y(), CL_CELL);
//        else
//            QMessageBox::information(this, "", "Поле закрыто");
    }
    if (event->button() == Qt::RightButton)
//        if (editingMode == true)
            drawCell(event->x(), event->y(), CL_EMPTY);
    emit sendMouseCoord(event->x(), event->y());
}

void Field::drawCell(int x, int y/*, CELLS cellType = CL_CELL*/, CELLS cellType)
{
    // индексы для массива клеток
    // ВНИМАНИЕ, их надо в индексах будет поменять местами
    int c_x, c_y;
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

void Field::clean()
{
    pm->fill();
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

