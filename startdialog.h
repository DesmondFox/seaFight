#ifndef STARTDIALOG_H
#define STARTDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QGridLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QApplication>

#include "aboutdialog.h"

class StartDialog : public QDialog
{
    Q_OBJECT

public:
    StartDialog(QWidget *parent = 0);

private:
    QGridLayout *lay;
    QLabel *lblWelcome;
    QRadioButton *checkSinglePlayer;
    QRadioButton *checkMultiPlayer;
    QGroupBox *groupSingleOrMulti;
    QVBoxLayout *checks;
    QLabel *lblPlayerName_1;
    QLabel *lblPlayerName_2;
    QLineEdit *edName1;
    QLineEdit *edName2;
    QPushButton *btnStart;
    QPushButton *btnExit;
    QPushButton *btnAbout;
    AboutDialog dlgAbout;

    int mode;   // 1 - Сингплеер, 2 - Два игрока
public slots:
    void slotExit();
    void slotSingle();
    void slotMulti();
    void slotStart();
    void slotAbout();

signals:
    void signalSendPlayerNamesAndStart(const QString &name_1, const QString &name_2, int modeOfGame);
};

#endif // STARTDIALOG_H
