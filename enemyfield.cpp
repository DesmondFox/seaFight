#include "enemyfield.h"

EnemyField::EnemyField(int hX, int hY)
{
    pm = new QPixmap(hX, hY);
    pm->fill();
    x = hX;
    y = hY;
    zero_x = hX / 11;
    zero_y = hY / 11;
    clean();
    drawField();
    setCellsModeFlag = false;
}
