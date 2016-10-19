#include "about.h"

about::about(QWidget *parent)  : QDialog(parent)
{
    QLabel *author = new QLabel("Автор: ");
    QLabel *version = new QLabel("Версия: ");
    QLabel *rules = new QLabel("Правила: ");
    QLabel *lauthor = new QLabel("Alexey Rott (c) 2016");
    QLabel *lversion = new QLabel(VERSION);
    QTextEdit *trules = new QTextEdit("Игровое поле — обычно квадрат 10×10 каждого игрока, на котором размещается флот кораблей. <br>Горизонтали обычно нумеруются сверху вниз, а вертикали помечаются буквами слева направо. <br>При этом используются буквы русского алфавита от «а» до «к» (буквы «ё» и «й» обычно пропускаются) либо от 'а' до 'и' (с использованием буквы 'ё'), <br>либо буквы латинского алфавита от «a» до «j». <br>Сначало первый игрок расставляет корабли по своему полю, далее второй игрок делает тоже самое только на своём поле.<br> После того, как корабли будут расставлены, игра начнется. Задачей игры является нахождение и потопление всех кораблей противника.");

    QGridLayout *lay = new QGridLayout();
    lay->addWidget(author, 0, 0, Qt::AlignRight);
    lay->addWidget(version, 1, 0, Qt::AlignRight);
    lay->addWidget(rules, 2, 0, Qt::AlignRight | Qt::AlignTop);
    lay->addWidget(lauthor, 0, 1, Qt::AlignLeft);
    lay->addWidget(lversion, 1, 1, Qt::AlignLeft);
    lay->addWidget(trules, 2, 1, Qt::AlignLeft);


    this->setLayout(lay);
    this->setWindowTitle("Морской бой");
}
