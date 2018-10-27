#include "dialog_transitive_view.h"
#include "ui_dialog_transitive_view.h"

Dialog_transitive_view::Dialog_transitive_view(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_transitive_view)
{
    ui->setupUi(this);
}

Dialog_transitive_view::~Dialog_transitive_view()
{
    delete ui;
}
