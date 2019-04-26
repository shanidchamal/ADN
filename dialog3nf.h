#ifndef DIALOG3NF_H
#define DIALOG3NF_H

#include <QDialog>

namespace Ui {
class Dialog3nf;
}

class Dialog3nf : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog3nf(QWidget *parent = nullptr);
    ~Dialog3nf();

public slots:
    void printNF3(int,QStringList,QWidget *);
    int checkNF3_blacklist(int);
    void printClosure3NF(QWidget *);

private:
    int checkPkAttr(char[]);
    void findTransitive();

private:
    Ui::Dialog3nf *ui;
};

#endif // DIALOG3NF_H
