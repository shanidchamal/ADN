#ifndef DIALOG_BCNF_H
#define DIALOG_BCNF_H

#include <QDialog>

namespace Ui {
class Dialog_BCNF;
}

class Dialog_BCNF : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_BCNF(QWidget *parent = nullptr);
    ~Dialog_BCNF();
    void findBCNF();

public slots:
    void printBCNF(int,QStringList,QWidget *);
    void printClosureBCNF(QWidget *);
    int checkBCNF_blacklist(int);

private:
    Ui::Dialog_BCNF *ui;
};

#endif // DIALOG_BCNF_H
