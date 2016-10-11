#ifndef PROCESS_H
#define PROCESS_H

#include "window.h"
#include "startdialog.h"
#include "ai.h"

class Process : public window, public AI
{
    Q_OBJECT
public:
    Process(QWidget *parent = 0);
    Process();
    int stt;    // режим игры: 1 - с ПК, 2 - два игрока
    QString name1;
    QString name2;
    int current;


public slots:
    void getPlayerNamesAndStatus(const QString &playerName_1, const QString &playerName_2, int status);
    void player1_isDone();
    void player2_isDone();

    void AI_checkShips();
//    void AI_isDone();
    void player1_hit(int i, int j, bool full);
    void player1_miss(int i, int j);
    void player1_isWinner();
};

#endif // PROCESS_H
