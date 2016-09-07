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
    setCellsMode = true;
    FIELD[5][5] = 1;
    FIELD[5][6] = 1;
    FIELD[0][0] = 1;
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

    emit sendMouseCoord(event->x(), event->y());
}

void Field::mouseMoveEvent(QMouseEvent *event)
{

    int c_x, c_y;


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
            clean();
            drawField();
            drawCellField();
            qDebug() << drawGhostCell(c_x, c_y, SL_4, VERTICAL);
        }
    }
    else
    {
        c_x = -1;
        c_y = -1;
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

    // Тут даже однопалубный корабль бывает горизонтальным и вертикальным
    // Это странно, но работает. Иначе бы пришлось это всё выносить. Мб позже и вынесу отдельно, если надо будет.
    if (pos == HORIZONTAL)
    {
        if (ship == SL_1)
        {
            p.drawRect(QRect(cellx*cell+1, celly*cell+1, cell-2, cell-2));
            // И да, мы закидываем в метод drawGhostCell индексы клеток. т. е нумерация идет от 1 до 10.
            // А вот для массива, как известно, идет нумерация с 0 до 9 и по этому надо
            // минусовать единицу с проверки массива, ибо будет сдвиг (долго с этим возился)
            if ((FIELD[celly-1][cellx-1] != 0))
                return false;
        }
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
        if (ship == SL_1)
        {
            p.drawRect(QRect(cellx*cell+1, celly*cell+1, cell-2, cell-2));
            if ((FIELD[celly-1][cellx-1] != 0))
                return false;
        }
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

    /// TODO: Дописать условия для остальных типок клеток
    update();
}

void Field::drawCellField()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (FIELD[j][i] == 1)
                drawOneCell(i+1, j+1);
        }
    }

}

// Скорее всего этот метод я удалю. Не нужен он. Рисовкой будет заниматься отдельный метод,
// который будет ставить корабли целиком, а не по одному.

/// TODO: Удалить метод. Создать метод для рисовки целого корабля, а не поклеточно
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

