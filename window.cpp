#include "window.h"

window::window(QWidget *parent)     : QMainWindow(parent)
{
    QMenuBar *bar = new QMenuBar(this);
    QMenu *game = bar->addMenu("Game");
    QMenu *other = bar->addMenu("?");

    newGame = new QAction("Новая игра", this);
    QAction *endGame = new QAction("Выход", this);

    game->addAction(newGame);
    game->addSeparator();
    game->addAction(endGame);

    QAction *statist = new QAction("Статистика");
    statist->setShortcut(QKeySequence("Alt+F1"));
    statist->setIcon(QIcon(":/icon/icon/ocean-transportation.png"));
    QAction *abt = new QAction("Об игре");

    other->addAction(statist);
    other->addSeparator();
    other->addAction(abt);

    sts = new Statistics();
    about *ab = new about();

    field1 = new Field(this);
    field2 = new Field(this);
    field1->drawField();
    field2->drawField();
    field1->setStyleSheet("position: fixed");

    playerName1 = new QLabel("<font color=blue>Player 1</font>", this);
    playerName2 = new QLabel("<font color=purple>Player 2</font>", this);

    done1 = new QPushButton("Готово", this);
    done2 = new QPushButton("Готово", this);
    done1->setEnabled(false);
    done2->setEnabled(false);

    teLog = new QTextEdit(this);

    btnDebug = new QPushButton("View", this);

    btnDebug->hide();
    lay = new QGridLayout();
    lay->addWidget(playerName1, 0, 0, Qt::AlignLeft | Qt::AlignBottom);
    lay->addWidget(playerName2, 0, 1, Qt::AlignLeft | Qt::AlignBottom);
    lay->addWidget(field1, 1, 0, Qt::AlignLeft  | Qt::AlignTop);
    lay->addWidget(field2, 1, 1, Qt::AlignLeft  | Qt::AlignTop);
    lay->addWidget(done1, 2, 0, Qt::AlignCenter | Qt::AlignBottom);
    lay->addWidget(done2, 2, 1, Qt::AlignCenter | Qt::AlignBottom);
    lay->addWidget(btnDebug, 3, 0, Qt::AlignCenter | Qt::AlignBottom);
    lay->addWidget(teLog, 4, 0, Qt::AlignLeft  | Qt::AlignTop);

    this->resize(460, 400);
    QWidget *wgt = new QWidget(this);
    wgt->setLayout(lay);

    this->setCentralWidget(wgt);
    this->setMenuBar(bar);
    this->setWindowIcon(QIcon(":/icon/icon/ocean-transportation.png"));

    field2->setPermission(false);


    setWindowTitle("Морской бой 0.1-rc1");
    setWindowFlags(Qt::WindowContextHelpButtonHint | Qt::WindowCloseButtonHint);
    connect(field1, SIGNAL(done()), this, SLOT(field1_isDone()));
    connect(field2, SIGNAL(done()), this, SLOT(field2_isDone()));
    connect(btnDebug, SIGNAL(clicked(bool)), field2, SLOT(DEBUGGetField()));
    connect(statist, SIGNAL(triggered(bool)), this, SLOT(openStat()));
    connect(abt, SIGNAL(triggered(bool)), ab, SLOT(exec()));
    connect(endGame, SIGNAL(triggered(bool)), SLOT(close()));
    connect(this, SIGNAL(startNewGame()), field1, SLOT(clearAll()));
    connect(this, SIGNAL(startNewGame()), field2, SLOT(clearAll()));

}

void window::openStat()
{
    sts->read();
    sts->exec();
}


void window::setPlayerNames(const QString &name1, const QString &name2)
{
    if (!name1.isEmpty())
    {
        playerName1->setText("<font color=blue>"+name1+"</font>");
    }
    else
        playerName1->setText("<font color=blue>Player 1</font>");

    if (!name2.isEmpty())
    {
        playerName2->setText("<font color=purple>"+name2+"</font>");
    }
    else
        playerName2->setText("<font color=purple>Player 2</font>");

}

void window::Log(const QString &logStr)
{
    QString log = teLog->toHtml();
    log += logStr;
    teLog->clear();
    teLog->setText(log);
    teLog->moveCursor(QTextCursor::End);
}

void window::clearLog()
{
    teLog->clear();
}

void window::field1_isDone()
{
    done1->setEnabled(true);
    qDebug() << "FIELD 1 is done!";
}

void window::field2_isDone()
{
    done2->setEnabled(true);
    qDebug() << "FIELD 2 is done!";
}
