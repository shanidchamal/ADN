#ifndef DIALOG_TRANSITIVE_VIEW_H
#define DIALOG_TRANSITIVE_VIEW_H

#include <QDialog>
#include "dialog_closure_view.h"

extern char det_PATH[20][20];
extern Dialog_closure_view *dialog_closure_view;

namespace Ui {
class Dialog_transitive_view;
}

class Dialog_transitive_view : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_transitive_view(QWidget *parent = nullptr);
    ~Dialog_transitive_view();

private slots:
    void on_detPathButton_clicked();
    void on_nextButton_clicked();

private:
    Ui::Dialog_transitive_view *ui;
};

#endif // DIALOG_TRANSITIVE_VIEW_H
