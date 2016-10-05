#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
//#include <Q
#include "field.h"

class window    : public QWidget
{
public:
    window(QWidget *parent = 0);
    Field *field1;
    Field *field2;
    QGridLayout *lay;
    QPushButton *btnDebug;

    QLabel *playerName1;
    QLabel *playerName2;

public slots:
    void setPlayerNames(const QString &name1, const QString &name2);
};

#endif // WINDOW_H
