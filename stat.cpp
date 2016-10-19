#include "stat.h"

Statistics::Statistics(QWidget *parent)     : QDialog(parent)
{
    txt = new QTextEdit(this);
    txt->setReadOnly(true);

    resize(300, 100);
    txt->resize(300, 100);
}

void Statistics::read()
{
    txt->clear();
    QFile file("stat.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
//        QMessageBox::critical(this, "Err", "Файл "+file.fileName()+" не найден");
        QFile f("stat.txt");
        f.open(QIODevice::WriteOnly);
        QTextStream out(&f);
        out.setCodec(QTextCodec::codecForName("UTF-8"));
        out << tr("Игрок 1          | Игрок 2          | Итог\n");
        f.close();
    }

    QString tmpName1, tmpName2;

    QStringList list;

    QTextStream in(&file);
    while(!in.atEnd())
    {
        QString tmp = in.readLine();
        QString st = txt->toHtml();

        st.append(tmp);
        txt->setText(st);
        file.flush();
    }
    file.close();
}

void Statistics::toStat(const QString &name1, const QString &name2, int win)
{
    QFile out("stat.txt");

    if (!out.open(QIODevice::WriteOnly | QIODevice::Append))
        QMessageBox::critical(this, "Err", "Непредвиденная ошибка. Скорее всего потерян файл статистики");

    QTextStream stream(&out);
    QString total;
    if (win == 1)
        total = name1+" победитель";
    if (win == 2)
        total = name2+" победитель";
    if (win == 3)
        total = "Ничья";

    stream << name1 << "    " << name2 << "    " << total << "<br>";
    out.close();
}
