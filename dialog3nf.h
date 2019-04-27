#ifndef DIALOG3NF_H
#define DIALOG3NF_H

#include "dialog_bcnf.h"

#include <QDialog>

int checkNF3_blacklist(int);

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
    void printClosure3NF(QWidget *);

private slots:
    void on_nextButton_clicked();

private:
    int checkPkAttr(char[]);
    void findTransitive();

private:
    Ui::Dialog3nf *ui;
    Dialog_BCNF *dialog_bcnf;
};

#endif // DIALOG3NF_H
