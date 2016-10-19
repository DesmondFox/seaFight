#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QMainWindow>
//#include
#include <QMenuBar>
#include "field.h"
#include "stat.h"
#include "about.h"
#include "startdialog.h"

class window    : public QMainWindow
{
    Q_OBJECT

public:
    window(QWidget *parent = 0);
    Field *field1;
    Field *field2;
    QGridLayout *lay;
    QPushButton *btnDebug;
    QAction *newGame;
    QLabel *playerName1;
    QLabel *playerName2;
    QTextEdit *teLog;

    QPushButton *done1;
    QPushButton *done2;
    Statistics *sts;

public slots:
    void setPlayerNames(const QString &name1, const QString &name2);
    void Log(const QString &logStr);
    void field1_isDone();
    void field2_isDone();
    void clearLog();
    void openStat();

signals:
    void startNewGame();

};

#endif // WINDOW_H
