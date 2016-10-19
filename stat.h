#ifndef STAT_H
#define STAT_H

#include <QDialog>
#include <QFile>
#include <QTextEdit>
#include <QMessageBox>
#include <QTextStream>
#include <QStringList>
#include <QTextCodec>
//#include <QIODevice>

class Statistics : public QDialog
{
public:
    Statistics(QWidget *parent = 0);
    QTextEdit *txt;

public slots:
    void toStat(const QString &name1, const QString &name2, int win);
    void read();
};

#endif // STAT_H
