#ifndef DIALOG_TRANSITIVE_VIEW_H
#define DIALOG_TRANSITIVE_VIEW_H

#include <QDialog>

namespace Ui {
class Dialog_transitive_view;
}

class Dialog_transitive_view : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_transitive_view(QWidget *parent = nullptr);
    ~Dialog_transitive_view();

private:
    Ui::Dialog_transitive_view *ui;
};

#endif // DIALOG_TRANSITIVE_VIEW_H
