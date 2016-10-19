#include "ai.h"

AI::AI()
{
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            mapDots[i][j] = false;
}

indexes AI::ai_randHit()
{
    QTime seed(0, 0, 0);
    qsrand(seed.secsTo(QTime::currentTime()));
    indexes ind;

    while (true)
    {
        ind.i = qrand() % 10+1;
        ind.j = qrand() % 10+1;

        if (!mapDots[ind.i-1][ind.j-1])
        {
            mapDots[ind.i-1][ind.j-1] = true;
            break;
        }

    }
    return ind;
}

void AI::clearMap()
{
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            mapDots[i][j] = false;
}
