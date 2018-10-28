#ifndef DIALOG_DM_VIEW_H
#define DIALOG_DM_VIEW_H

#include <QDialog>
#include <dialog_dg_view.h>

extern char DM[20][20][30];

namespace Ui {
class Dialog_DM_view;
}

class Dialog_DM_view : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_DM_view(QWidget *parent = nullptr);
    ~Dialog_DM_view();

private slots:
    void sort();
    void on_dmButton_clicked();
    void on_nextButton_clicked();

private:
    Ui::Dialog_DM_view *ui;
    Dialog_DG_view *dialog_dg_view;
};

#endif // DIALOG_DM_VIEW_H
