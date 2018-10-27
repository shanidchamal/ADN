#ifndef DIALOG_FD_DISPLAY_H
#define DIALOG_FD_DISPLAY_H

#include <QDialog>
#include <math.h>

#include <dialog_dm_view.h>

extern char det_edge[30][30],dep_edge[30][30];
extern int edge_count,reflex_edge_count;

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
    Dialog_DM_view *dialog_dm_view;

private slots:
    char* print_det_fd(int);
    char* print_dep_fd(int);
    int create_dg_edges(char[][30],char[][30],char[][30],char[][30],int *);
    void writeFile(char[][30],char[][30],char[][30],char[][30],int,int);
    void on_graph_Button_clicked();
    void on_nextButton_clicked();
};

#endif // DIALOG_FD_DISPLAY_H
