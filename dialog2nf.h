#ifndef DIALOG2NF_H
#define DIALOG2NF_H

#include <QDialog>
#include "dialog3nf.h"

namespace Ui {
class Dialog2NF;
}

class Dialog2NF : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog2NF(QWidget *parent = nullptr);
    ~Dialog2NF();

private slots:
    void on_nextButton_clicked();
    int checkPkAttr(char[]);
    int print2NF(int,int,int[],QStringList,QWidget *);
    int checkRowScope(int);
    int checkColScope(int,int,int[]);

private:
    Ui::Dialog2NF *ui;
    Dialog3nf *dialog3nf;
};

#endif // DIALOG2NF_H
