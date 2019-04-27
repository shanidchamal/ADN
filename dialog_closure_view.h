#ifndef DIALOG_CLOSURE_VIEW_H
#define DIALOG_CLOSURE_VIEW_H

#include <QDialog>
#include "dialog2nf.h"

extern int NF_array[15],NF_count,bl_count;
extern char pk[30];

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
    void dependency_closure2(char[][30],int,int);
    void circular_dependency();
    int FindOne(int,int,int);
    int candidate_keys(char[][30],int[]);
    int findKeyRank(char[][30],int[],int);
    int primary_key(char[][30],int[],int,int[],int);
    int findPartial(int,int *);
    int findSim_k_Index(char[]);
    void maskAttr();
    int checkCanIndex(int,int[]);

private slots:
    void on_backButton_clicked();

    void on_nextButton_clicked();

private:
    Ui::Dialog_closure_view *ui;
    Dialog2NF *dialog_2nf;
};

#endif // DIALOG_CLOSURE_VIEW_H
