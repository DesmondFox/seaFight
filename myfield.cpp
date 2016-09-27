#include "myfield.h"

MyField::MyField(int hX, int hY)
{
    pm = new QPixmap(hX, hY);
    width = hX;
    height = hY;
    zero_x = hX / 11;
    zero_y = hY / 11;
    pm->fill();
//    editingMode = true;
    drawField();
    drawFieldCells();
}

//void MyField::startEditing()
//{
//    QMessageBox::information(this, "Расстановка", QString("Сначала %1 расставляет свои корабли").arg(playerName));
//}

