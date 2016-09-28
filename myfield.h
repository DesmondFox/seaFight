#ifndef MYFIELD_H
#define MYFIELD_H

#include "field.h"

class MyField : public Field
{
    Q_OBJECT
public:
    MyField(int hX, int hY);

};

#endif // MYFIELD_H
