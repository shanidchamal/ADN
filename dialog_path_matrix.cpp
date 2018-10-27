#include "dialog_path_matrix.h"
#include "ui_dialog_path_matrix.h"

Dialog_path_matrix::Dialog_path_matrix(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_path_matrix)
{
    ui->setupUi(this);
}

Dialog_path_matrix::~Dialog_path_matrix()
{
    delete ui;
}
