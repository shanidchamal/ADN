#include "dialog3nf.h"
#include "ui_dialog3nf.h"

Dialog3nf::Dialog3nf(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog3nf)
{
    ui->setupUi(this);
}

Dialog3nf::~Dialog3nf()
{
    delete ui;
}
