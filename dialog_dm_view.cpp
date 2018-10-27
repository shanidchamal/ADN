#include "dialog_dm_view.h"
#include "ui_dialog_dm_view.h"

Dialog_DM_view::Dialog_DM_view(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_DM_view)
{
    ui->setupUi(this);
}

Dialog_DM_view::~Dialog_DM_view()
{
    delete ui;
}
