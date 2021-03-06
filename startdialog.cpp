#include "startdialog.h"

StartDialog::StartDialog(QWidget *parent)   : QDialog(parent)
{
    lay = new QGridLayout();
    lblWelcome = new QLabel("<h3>Добро пожаловать!</h3>", this);

    checks = new QVBoxLayout(this);

    checkSinglePlayer = new QRadioButton("Один игрок");
    checkSinglePlayer->setToolTip("Игра с компьютером");
    checkMultiPlayer = new QRadioButton("Два игрока");
    checkMultiPlayer->setToolTip("Игра с другим человеком за одним копьютером");
    groupSingleOrMulti = new QGroupBox("Режим игры");
    checks->addWidget(checkSinglePlayer);
    checks->addWidget(checkMultiPlayer);
    groupSingleOrMulti->setLayout(checks);
    checkSinglePlayer->setChecked(true);

    lblPlayerName_1 = new QLabel("Игрок 1:");
    lblPlayerName_2 = new QLabel("Игрок 2:");
    edName1 = new QLineEdit("Игрок 1");
    edName2 = new QLineEdit("Игрок 2");
    edName2->setEnabled(false);
    lblPlayerName_2->setEnabled(false);

    cbTipsMode = new QCheckBox("С подсказками");
    cbTipsMode->setToolTip("Обводить убитый корабль");

    btnStart = new QPushButton("Начать игру!");
    btnExit = new QPushButton("Выход");
    btnAbout = new QPushButton("О игре/Правила");
    btnStart->setDefault(true);

    lay->addWidget(lblWelcome, 0, 1, Qt::AlignCenter);
    lay->addWidget(groupSingleOrMulti, 1, 1, Qt::AlignCenter);
    lay->addWidget(lblPlayerName_1, 2, 0, Qt::AlignRight);
    lay->addWidget(lblPlayerName_2, 3, 0, Qt::AlignRight);
    lay->addWidget(edName1, 2, 1, Qt::AlignCenter);
    lay->addWidget(edName2, 3, 1, Qt::AlignCenter);
    lay->addWidget(cbTipsMode, 4, 0, Qt::AlignLeft);
    lay->addWidget(btnExit, 5, 0, Qt::AlignCenter);
    lay->addWidget(btnStart, 5, 1);
    lay->addWidget(btnAbout, 5, 2, Qt::AlignCenter);


    this->setLayout(lay);
    this->setWindowTitle("Морской бой");
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    mode = 1;


    connect(btnExit, SIGNAL(clicked(bool)), this, SLOT(slotExit()));
    connect(checkSinglePlayer, SIGNAL(clicked(bool)), this, SLOT(slotSingle()));
    connect(checkMultiPlayer, SIGNAL(clicked(bool)), this, SLOT(slotMulti()));
    connect(btnExit, SIGNAL(clicked(bool)), SLOT(slotExit()));
    connect(btnStart, SIGNAL(clicked(bool)), this, SLOT(slotStart()));
    connect(btnAbout, SIGNAL(clicked(bool)), this, SLOT(slotAbout()));

}

void StartDialog::slotExit()
{
    // TODO: Реализовать выход из приложения по другому, ибо не канон
    std::exit(0);
//    QApplication::exit(0);
}

void StartDialog::closeEvent(QCloseEvent *event)
{
    slotExit();
    event->accept();
}

void StartDialog::slotSingle()
{
    lblPlayerName_2->setEnabled(false);
    edName2->setEnabled(false);
    mode = 1;
    lblPlayerName_1->setEnabled(true);
    edName1->setEnabled(true);
}

void StartDialog::slotMulti()
{
    mode = 2;
    lblPlayerName_2->setEnabled(true);
    edName2->setEnabled(true);
}

void StartDialog::slotStart()
{
    QString name1 = edName1->text();
    QString name2 = edName2->text();
    emit signalSendPlayerNamesAndStart(name1, name2, mode, cbTipsMode->isChecked());
    this->accept();
}

void StartDialog::slotAbout()
{
    about *aboutDialog = new about(this);
    aboutDialog->exec();

}
