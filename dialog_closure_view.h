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

public slots:
    void dependency_closure();
    void dependency_closure2(char[][30],int);
    void circular_dependency();
    int FindOne(int,int,int,int);
    int candidate_keys(char[][30],int[]);
    int findKeyRank(char[][30],int[],int);
    int primary_key(char[][30],int[],int,int[],int);

private slots:
    void on_backButton_clicked();

private:
    Ui::Dialog_closure_view *ui;
};

#endif // DIALOG_CLOSURE_VIEW_H
