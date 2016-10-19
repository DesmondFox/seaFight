#ifndef PROCESS_H
#define PROCESS_H

#include <QtMultimedia/QSound>
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
    AI ai;
    StartDialog *start;

public slots:
    void getPlayerNamesAndStatus(const QString &playerName_1, const QString &playerName_2, int status, bool tips);
    void player1_isDone();
    void player2_isDone();

    void AI_checkShips();
//    void AI_isDone();
    void player1_hit(int i, int j, bool full);
    void player1_miss(int i, int j);
    void player1_isWinner();

    void player2_hit(int i, int j, bool full);
    void player2_miss(int i, int j);
    void player2_isWinner();
    void anyPlayer_notBattleMode();
    void startGameAgain();


};

#endif // PROCESS_H
