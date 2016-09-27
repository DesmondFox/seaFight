#include "ship.h"

Ship::Ship()
{

}

Ship::Ship(int i, int j, int decks, position pos)
{
    shipCell.clear();
    if (pos == horizontal)
        for (int n = 0; n < decks; n++)
            shipCell.append(IndexesAndStatus(i, j+n, st_alive));
    if (pos == vertical)
        for (int n = 0; n < decks; n++)
            shipCell.append(IndexesAndStatus(i+n, j, st_alive));
    numberOfDecks = decks;
    positionOfShip = pos;
}
