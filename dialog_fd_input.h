#ifndef DIALOG_FD_INPUT_H
#define DIALOG_FD_INPUT_H

#include <QDialog>
#include <dialog_fd_display.h>

//include necessary headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Structure to store determinant keys
struct det_fd_node{
    char fd[30];
    struct det_fd_node *next;
};

//Structure to store dependent keys
struct dep_fd_node{
    char fd[30];
    struct dep_fd_node *next;
};

extern struct det_fd_node *det_head[6];
extern struct dep_fd_node *dep_head[6];
extern int fd_count,sim_k_count;
extern char det_k[30][30],sim_k[30][30];

namespace Ui {
class Dialog_fd_input;
}

class Dialog_fd_input : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_fd_input(QWidget *parent = nullptr);
    ~Dialog_fd_input();

private:
    Ui::Dialog_fd_input *ui;
    Dialog_fd_display *dialog_fd_display;

private slots:
    void create_det_FD(int , char*);
    void create_dep_FD(int, char*);
    void on_push_fd_Button_clicked();
    void on_ex1Button_clicked();
    void on_ex2Button_clicked();
    void on_cRentalButton_clicked();
};

#endif // DIALOG_FD_INPUT_H
