#ifndef DIALOG_DG_VIEW_H
#define DIALOG_DG_VIEW_H

#include <QDialog>
#include <dialog_path_matrix.h>

namespace Ui {
class Dialog_DG_view;
}

class Dialog_DG_view : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_DG_view(QWidget *parent = nullptr);
    ~Dialog_DG_view();

private slots:
    void on_dgButton_clicked();
    void on_nextButton_clicked();

private:
    Ui::Dialog_DG_view *ui;
    Dialog_path_matrix *dialog_path_matrix;
};

#endif // DIALOG_DG_VIEW_H
