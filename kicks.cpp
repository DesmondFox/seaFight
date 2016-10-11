#include "kicks.h"

Kicks::Kicks()
{

}

Kicks::Kicks(int i, int j, bool inj)
{
    I = i;
    J = j;
    injured = inj;
}

void Kicks::setData(int i, int j, bool inj)
{
    I = i;
    J = j;
    injured = inj;
}
