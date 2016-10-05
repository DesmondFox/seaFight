#include <QApplication>

#include "window.h"
#include "startdialog.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartDialog str;
    str.exec();
    window wnd;
    wnd.show();

    return a.exec();
}
