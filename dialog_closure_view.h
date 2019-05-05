#ifndef DIALOG_CLOSURE_VIEW_H
#define DIALOG_CLOSURE_VIEW_H

#include <QDialog>
#include "dialog2nf.h"

extern int NF_array[15],NF_count,bl_count,dm_row,can_flag;
extern char pk[30],ck[30],new_pk[30];
extern Dialog2NF *dialog_2nf;
int checkMaskValidity(int,int);
int checkCanIndex(int,int[]);
int checkCK(int,int[]);
int lossy(int,int);

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
    void candidate_key(char[][30],int);
    int findKeyRank(char[][30],int[],int,int);
    int primary_key(char[][30],int[],int,int[],int);
    int findPartial(int,int *,int);
    int checkLHSonly(int);
    int checkSim_k_blacklist(int);
    int findSim_k_Index(char[]);
    void maskAttr();
    int getDetKIndex(char[]);
    int checkRHS(int);
    void append2DM();

private slots:
    void on_backButton_clicked();

    void on_nextButton_clicked();

private:
    Ui::Dialog_closure_view *ui;
};

#endif // DIALOG_CLOSURE_VIEW_H
