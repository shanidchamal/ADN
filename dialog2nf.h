#ifndef DIALOG2NF_H
#define DIALOG2NF_H

#include <QDialog>

namespace Ui {
class Dialog2NF;
}

class Dialog2NF : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog2NF(QWidget *parent = nullptr);
    ~Dialog2NF();

private:
    Ui::Dialog2NF *ui;
};

#endif // DIALOG2NF_H
