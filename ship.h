#ifndef SHIP_H
#define SHIP_H
#include <QVector>

enum statusOfShip {st_alive = 1, st_injured};
enum position {horizontal = 0, vertical};

struct IndexesAndStatus
{
    int i;
    int j;
    statusOfShip status;
};

class Ship
{
public:
    Ship();
    Ship(int i, int j, int decks, position pos);    // Сразу зададим конструктор с параметром (на всякий случай)
    QVector<IndexesAndStatus> shipCell; // Это вектор, хранящий координаты каждой клетки корабля и состояние каждой из них
    int numberOfDecks;  // Количество палуб у корабля (менее 4, но более 1)
    position positionOfShip;    // Вертикально или горизонтально корабль стоит
};

#endif // SHIP_H
