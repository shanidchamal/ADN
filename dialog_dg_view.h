#ifndef DIALOG_DG_VIEW_H
#define DIALOG_DG_VIEW_H

#include <QDialog>

namespace Ui {
class Dialog_DG_view;
}

class Dialog_DG_view : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_DG_view(QWidget *parent = nullptr);
    ~Dialog_DG_view();

private:
    Ui::Dialog_DG_view *ui;
};

#endif // DIALOG_DG_VIEW_H
