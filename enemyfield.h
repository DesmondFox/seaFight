#ifndef ENEMYFIELD_H
#define ENEMYFIELD_H

#include "field.h"

class EnemyField : public Field
{
    Q_OBJECT
public:
    EnemyField(int hX, int hY);
    int FIELD[10][10]; // собственно, поле
private slots:

};

#endif // ENEMYFIELD_H
