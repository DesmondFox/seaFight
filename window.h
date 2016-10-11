#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>

//#include <Q
#include "field.h"

class window    : public QWidget
{
    Q_OBJECT

public:
    window(QWidget *parent = 0);
    Field *field1;
    Field *field2;
    QGridLayout *lay;
    QPushButton *btnDebug;

    QLabel *playerName1;
    QLabel *playerName2;
    QTextEdit *teLog;

    QPushButton *done1;
    QPushButton *done2;

public slots:
    void setPlayerNames(const QString &name1, const QString &name2);
    void Log(const QString &logStr);
    void field1_isDone();
    void field2_isDone();

};

#endif // WINDOW_H
