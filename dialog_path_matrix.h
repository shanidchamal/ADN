#ifndef DIALOG_PATH_MATRIX_H
#define DIALOG_PATH_MATRIX_H

#include <QDialog>
#include "dialog_transitive_view.h"

extern char total_k[20][50];
extern int PATH[20][20],total_k_count;
extern Dialog_transitive_view *dialog_transitive_view;

namespace Ui {
class Dialog_path_matrix;
}

class Dialog_path_matrix : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_path_matrix(QWidget *parent = nullptr);
    ~Dialog_path_matrix();

private:
    Ui::Dialog_path_matrix *ui;

public slots:
    void generate_total_k();
    void generate_ADJ(char [][20]);
private slots:
    void on_pathButton_clicked();
    void on_nextButton_clicked();
};

#endif // DIALOG_PATH_MATRIX_H
