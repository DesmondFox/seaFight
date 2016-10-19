#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QTextEdit>

#define VERSION QString("0.1-rc1")

class about : public QDialog
{
public:
    about(QWidget *parent = 0);
};

#endif // ABOUT_H
