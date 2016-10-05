#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>

#define SF_VERSION QString("0.1-rc1")

class AboutDialog : public QDialog
{
    Q_OBJECT
public:
    AboutDialog(QWidget *parent = 0);
    ~AboutDialog();

private:
    QGridLayout *lay;
    QLabel *lblVersion;
    QLabel *lblAuthor;
    QLabel *Version;
    QLabel *Author;
    QPushButton *btnClose;
    QLabel *lblRules;
    QLabel *Rules;
private  slots:
    void slotClose();
};

#endif // ABOUTDIALOG_H
