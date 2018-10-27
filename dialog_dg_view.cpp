#include "dialog_dg_view.h"
#include "ui_dialog_dg_view.h"

Dialog_DG_view::Dialog_DG_view(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_DG_view)
{
    ui->setupUi(this);
}

Dialog_DG_view::~Dialog_DG_view()
{
    delete ui;
}
