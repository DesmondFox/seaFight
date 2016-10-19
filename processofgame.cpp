#include "processofgame.h"

Process::Process(QWidget *parent)   : window(parent)
{
    start = new StartDialog(this);

    connect(start, SIGNAL(signalSendPlayerNamesAndStart(QString,QString,int,bool)), this, SLOT(getPlayerNamesAndStatus(QString,QString,int,bool)));
    start->exec();

    if (stt == 1)
    {
        done2->hide();
    }

    current = 1;    // 1 - ход первого игрока
                    // 2 - ход второго игрока



    connect(done1, SIGNAL(clicked(bool)), this, SLOT(player1_isDone()));
    connect(done2, SIGNAL(clicked(bool)), this, SLOT(player2_isDone()));

    connect(field2, SIGNAL(injured(int,int,bool)), SLOT(player1_hit(int,int,bool)));
    connect(field2, SIGNAL(endGame()), SLOT(player1_isWinner()));
    connect(field2, SIGNAL(miss(int,int)), SLOT(player1_miss(int,int)));

    connect(field1, SIGNAL(injured(int,int,bool)), SLOT(player2_hit(int,int,bool)));
    connect(field1, SIGNAL(endGame()), SLOT(player2_isWinner()));
    connect(field1, SIGNAL(miss(int,int)), SLOT(player2_miss(int,int)));

    QMessageBox::information(this, "Начало", playerName1->text()+" расставляет корабли");
    connect(field1, SIGNAL(notBattleMode()), SLOT(anyPlayer_notBattleMode()));
    connect(field2, SIGNAL(notBattleMode()), SLOT(anyPlayer_notBattleMode()));
    connect(newGame, SIGNAL(triggered(bool)), SLOT(startGameAgain()));
//    Log(playerName1->text()+" расставляет корабли первым");
}

Process::Process()
{

}

void Process::getPlayerNamesAndStatus(const QString &playerName_1, const QString &playerName_2, int status, bool tips)
{
    setPlayerNames(playerName_1, status == 1 ? "Компьютер" : playerName_2);
    stt = status;
    name1 = playerName1->text();
    name2 = playerName2->text();
    field1->setTips(tips);
    field2->setTips(tips);
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
    Log(name1+ " > ["+QString::number(j)+chars[i-1]+"] - "+ (full ? "<i><b>Убил</b></i>" : "<i>Ранил<i>"));

}

void Process::player1_miss(int i, int j)
{
    QChar chars[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    Log(name1+ " > ["+QString::number(j)+chars[i-1]+"] - <u>Мимо</u>");
    Log(name2+ ", Ваш ход!");
    bool tmp;

    if (stt == 1)
    {
        do
        {
                tmp = field1->hit(ai.ai_randHit());
                qDebug() << tmp;
        }
        while (tmp);
    }
    if (stt == 1)
    {
        field1->setBattleMode(false);
        field2->setBattleMode(true);
    }
    else
    {

        field1->setBattleMode(true);
        field2->setBattleMode(false);
    }


}

void Process::player1_isWinner()
{
    Log(name1+" Победитель!");
    QMessageBox::information(this, "Конец игры", name1+" выиграл!");
    Statistics st;
    st.toStat(name1, name2, 1);
    field1->setBattleMode(false);
    field2->setBattleMode(false);
}

void Process::player2_hit(int i, int j, bool full)
{
    QChar chars[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    Log(name2+ " &lt; ["+QString::number(j)+chars[i-1]+"] - "+ (full ? "<i><b>Убил</b></i>" : "<i>Ранил<i>"));
}

void Process::player2_miss(int i, int j)
{
    QChar chars[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    Log(name2+ " &lt; ["+QString::number(j)+chars[i-1]+"] - <u>Мимо</u>");
    Log(name1+ ", Ваш ход!");

    field1->setBattleMode(false);
    field2->setBattleMode(true);
    current = 1;
}

void Process::player2_isWinner()
{
    Log(name2+" Победитель!");
    QMessageBox::information(this, "Конец игры", name2+" выиграл!");
    Statistics st;
    st.toStat(name1, name2, 2);
    field1->setBattleMode(false);
    field2->setBattleMode(false);
}

void Process::anyPlayer_notBattleMode()
{
    QSound::play(":/sounds/no_battle.wav");
}

void Process::AI_checkShips()
{
    field2->randShips();
}

void Process::startGameAgain()
{
    int warn = QMessageBox::warning(this, "Новая игра", "Внимание! Вы уверенны, что хотите начать игру заново? Текущая игра будет стерта", "Да", "Нет", QString(), 0, 1);
    if (!warn)
    {
        emit startNewGame();
        ai.clearMap();
        field1->setPermission(true);
        field2->setPermission(false);
        done1->show();
        done1->setEnabled(false);
        if (stt == 2)
        {
            done2->show();
            done2->setEnabled(false);
        }
        clearLog();
        start->exec();
    }

}
