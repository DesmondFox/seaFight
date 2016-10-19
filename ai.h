#ifndef AI_H
#define AI_H

#include <QTime>
#include "indexesandstatus.h"

class AI
{
public:
    AI();
    indexes ai_randHit();
    void clearMap();


private:
    bool mapDots[10][10];
};

#endif // AI_H
