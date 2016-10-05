#include "window.h"

window::window(QWidget *parent)     : QWidget(parent)
{
    field1 = new Field(this);
    field2 = new Field(this);

    playerName1 = new QLabel("<font color=blue>Player 1</font>", this);
    playerName2 = new QLabel("<font color=purple>Player 2</font>", this);


    lay = new QGridLayout(this);
    lay->addWidget(playerName1, 0, 0, Qt::AlignCenter | Qt::AlignBottom);
    lay->addWidget(playerName2, 0, 1, Qt::AlignCenter | Qt::AlignBottom);
    lay->addWidget(field1, 1, 0, Qt::AlignLeft  | Qt::AlignTop);
    lay->addWidget(field2, 1, 1, Qt::AlignRight | Qt::AlignTop);

    this->resize(475, 300);

    btnDebug = new QPushButton("View", this);
    lay->addWidget(btnDebug, 2, 0);

    setLayout(lay);
    setWindowTitle("Морской бой 0.1-rc1");

    connect(btnDebug, SIGNAL(clicked(bool)), field1, SLOT(DEBUGGetField()));
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
        playerName2->setText("<font color=blue>"+name2+"</font>");
    }
    else
        playerName2->setText("<font color=blue>Player 2</font>");
}
