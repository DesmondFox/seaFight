#include "window.h"

window::window(QWidget *parent)     : QWidget(parent)
{
    field1 = new Field(this);
    field2 = new Field(this);
    field1->drawField();
    field2->drawField();
//    field2->
    field1->setStyleSheet("position: fixed");

    playerName1 = new QLabel("<font color=blue>Player 1</font>", this);
    playerName2 = new QLabel("<font color=purple>Player 2</font>", this);

    done1 = new QPushButton("Готово", this);
    done2 = new QPushButton("Готово", this);
    done1->setEnabled(false);
    done2->setEnabled(false);

    teLog = new QTextEdit(this);
    btnDebug = new QPushButton("View", this);
    lay = new QGridLayout(this);
    lay->addWidget(playerName1, 0, 0, Qt::AlignLeft | Qt::AlignBottom);
    lay->addWidget(playerName2, 0, 1, Qt::AlignLeft | Qt::AlignBottom);
    lay->addWidget(field1, 1, 0, Qt::AlignLeft  | Qt::AlignTop);
    lay->addWidget(field2, 1, 1, Qt::AlignLeft  | Qt::AlignTop);
    lay->addWidget(done1, 2, 0, Qt::AlignCenter | Qt::AlignBottom);
    lay->addWidget(done2, 2, 1, Qt::AlignCenter | Qt::AlignBottom);
    lay->addWidget(btnDebug, 3, 0, Qt::AlignCenter | Qt::AlignBottom);
    lay->addWidget(teLog, 4, 0, Qt::AlignLeft  | Qt::AlignTop);

    this->resize(485, 500);



    field2->setPermission(false);

//    setLayout(lay);
    setWindowTitle("Морской бой 0.1-rc1");

    connect(btnDebug, SIGNAL(clicked(bool)), field2, SLOT(DEBUGGetField()));
    connect(field1, SIGNAL(done()), this, SLOT(field1_isDone()));
    connect(field2, SIGNAL(done()), this, SLOT(field2_isDone()));

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
