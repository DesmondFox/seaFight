#include "aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent)   : QDialog(parent)
{
    lblVersion = new QLabel("Версия: ");
    lblAuthor = new QLabel("Автор: ");
    Version = new QLabel(SF_VERSION);
    Author = new QLabel("Alexey Rott (Di3go) \n (c) 2016");
    lblRules = new QLabel("Правила: ");
    Rules = new QLabel("/// В РАЗРАБОТКЕ");
    btnClose = new QPushButton("ОК");
    lay = new QGridLayout(this);

    lay->addWidget(lblVersion, 0, 0, Qt::AlignRight | Qt::AlignTop);
    lay->addWidget(lblAuthor, 1, 0, Qt::AlignRight | Qt::AlignTop);
    lay->addWidget(lblRules, 2, 0, Qt::AlignRight | Qt::AlignTop);
    lay->addWidget(Version, 0, 1);
    lay->addWidget(Author, 1, 1);
    lay->addWidget(Rules, 2, 1);
    lay->addWidget(btnClose, 3, 2);
    this->setLayout(lay);
    this->setWindowTitle("About / Правила");
    this->resize(400, 200);

    connect(btnClose, SIGNAL(clicked(bool)), this, SLOT(slotClose()));
}

AboutDialog::~AboutDialog()
{
    delete lblAuthor;
    delete lblRules;
    delete lblVersion;
    delete Author;
    delete Version;
    delete Rules;
    delete lay;
    delete btnClose;
}

void AboutDialog::slotClose()
{
    this->close();
}
