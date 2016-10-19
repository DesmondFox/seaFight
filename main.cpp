#include <QApplication>

//#include "window.h"
#include "startdialog.h"
#include "processofgame.h"
#include <QTextStream>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Process *pr = new Process(0);
    pr->show();

    return a.exec();
}
