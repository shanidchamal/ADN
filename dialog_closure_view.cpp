#include "dialog_closure_view.h"
#include "ui_dialog_closure_view.h"

Dialog_closure_view::Dialog_closure_view(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_closure_view)
{
    ui->setupUi(this);
}

Dialog_closure_view::~Dialog_closure_view()
{
    delete ui;
}
