#ifndef DIALOG_CLOSURE_VIEW_H
#define DIALOG_CLOSURE_VIEW_H

#include <QDialog>

namespace Ui {
class Dialog_closure_view;
}

class Dialog_closure_view : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_closure_view(QWidget *parent = nullptr);
    ~Dialog_closure_view();

private:
    Ui::Dialog_closure_view *ui;
};

#endif // DIALOG_CLOSURE_VIEW_H
