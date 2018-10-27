#ifndef DIALOG_DM_VIEW_H
#define DIALOG_DM_VIEW_H

#include <QDialog>

namespace Ui {
class Dialog_DM_view;
}

class Dialog_DM_view : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_DM_view(QWidget *parent = nullptr);
    ~Dialog_DM_view();

private:
    Ui::Dialog_DM_view *ui;
};

#endif // DIALOG_DM_VIEW_H
