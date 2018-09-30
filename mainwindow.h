#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <dialog_fd_input.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_homeButton_clicked();

private:
    Ui::MainWindow *ui;
    Dialog_fd_input *dialog_fd_input;
};

#endif // MAINWINDOW_H
