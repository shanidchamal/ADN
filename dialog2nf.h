#ifndef DIALOG2NF_H
#define DIALOG2NF_H

#include <QDialog>
#include "dialog3nf.h"

extern int NF2_index,bl2_index,bl_count2,NF_blacklist[30];
extern Dialog3nf *dialog3nf;

int checkRowScope(int);
int checkColScope(int,int);
int checkNF3_blacklist(int);

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
    void printNF2(int,QStringList,QWidget *);
    void printClosure2NF(QWidget *);
    void on_backButton_clicked();

private:
    Ui::Dialog2NF *ui;
};

#endif // DIALOG2NF_H
