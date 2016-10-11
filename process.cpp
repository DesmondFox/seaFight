#include "process.h"

Process::Process(QWidget *parent)   : window(parent)
{
    StartDialog *start = new StartDialog(this);

    connect(start, SIGNAL(signalSendPlayerNamesAndStart(QString,QString,int)), this, SLOT(getPlayerNamesAndStatus(QString,QString,int)));
    start->exec();

    if (stt == 1)
    {
        done2->hide();
    }

    QMessageBox::information(this, "Начало", playerName1->text()+" расставляет корабли");

    connect(done1, SIGNAL(clicked(bool)), this, SLOT(player1_isDone()));
    connect(done2, SIGNAL(clicked(bool)), this, SLOT(player2_isDone()));
    connect(field2, SIGNAL(injured(int,int,bool)), SLOT(player1_hit(int,int,bool)));
    connect(field2, SIGNAL(endGame()), SLOT(player1_isWinner()));
    connect(field2, SIGNAL(miss(int,int)), SLOT(player1_miss(int,int)));
}

Process::Process()
{

}

void Process::getPlayerNamesAndStatus(const QString &playerName_1, const QString &playerName_2, int status)
{
    setPlayerNames(playerName_1, status == 1 ? "Компьютер" : playerName_2);
    stt = status;
    name1 = playerName1->text();
    name2 = playerName2->text();
}

void Process::player1_isDone()
{
    field1->clearField();
    QMessageBox::information(this, "Начало", name2+" расставляет корабли");

    Log(name1+" корабли расставил");
    if (stt == 1)
    {
        AI_checkShips();
        player2_isDone();
    }
    if (stt == 2)
    {
        field2->setPermission(true);
    }
    done1->hide();

}

void Process::player2_isDone()
{
    field2->setPermission(false);
    field2->clearField();

    done2->hide();
    Log(name2+" корабли расставил");
    QMessageBox::information(this, "Игра началась", "Корабли расставлены. Игра началась <br> "+ name1 +" ходит первым!");
    field2->setBattleMode(true);

}

void Process::player1_hit(int i, int j, bool full)
{
    QChar chars[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    Log(name1+ " > ["+QString::number(j)+chars[i-1]+"] - "+ (full ? "Убил" : "Ранил"));

}

void Process::player1_miss(int i, int j)
{
    QChar chars[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    Log(name1+ " > ["+QString::number(j)+chars[i-1]+"] - <u>Мимо</u>");

    // TODO: Дописать передачу
}

void Process::player1_isWinner()
{
    Log(name1+" Победитель!");
    QMessageBox::information(this, "Конец игры", name1+" выиграл!");
}

void Process::AI_checkShips()
{

}

