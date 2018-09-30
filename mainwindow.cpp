#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_homeButton_clicked()
{
    hide();
    dialog_fd_input = new Dialog_fd_input(this);
    dialog_fd_input->show();
}
