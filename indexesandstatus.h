#ifndef INDEXESANDSTATUS_H
#define INDEXESANDSTATUS_H

struct indexes
{
    int i;
    int j;
};

enum status {st_alive = 1, st_injured};
enum position {horizontal = 0, vertical};

class IndexesAndStatus
{
public:
    IndexesAndStatus();
    IndexesAndStatus(int indi, int indj, status s);
    int i;
    int j;
    status stt;
};

#endif // INDEXESANDSTATUS_H
