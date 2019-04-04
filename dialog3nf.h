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

private:
    Ui::Dialog3nf *ui;
};

#endif // DIALOG3NF_H
