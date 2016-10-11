#include <QApplication>

//#include "window.h"
#include "startdialog.h"
#include "process.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    StartDialog *start = new StartDialog(0);
//    start->exec();

    Process *pr = new Process(0);
    pr->show();

    return a.exec();
}
