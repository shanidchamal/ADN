#ifndef DIALOG_FD_DISPLAY_H
#define DIALOG_FD_DISPLAY_H

#include <QDialog>

namespace Ui {
class Dialog_fd_display;
}

class Dialog_fd_display : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_fd_display(QWidget *parent = nullptr);
    ~Dialog_fd_display();

private:
    Ui::Dialog_fd_display *ui;

private slots:
    char* print_det_fd(int);
    char* print_dep_fd(int);
    int create_dg_edges(char[][30],char[][30],char[][30],char[][30],int *);
    void writeFile(char[][30],char[][30],char[][30],char[][30],int,int);
    void on_graph_Button_clicked();
};

#endif // DIALOG_FD_DISPLAY_H
