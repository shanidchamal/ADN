#ifndef DIALOG_PATH_MATRIX_H
#define DIALOG_PATH_MATRIX_H

#include <QDialog>
#include <dialog_transitive_view.h>

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
    Dialog_transitive_view *dialog_transitive_view;

public slots:
    void generate_total_k(char [][20]);
    void generate_ADJ(char [][20], char[][20]);
private slots:
    void on_pathButton_clicked();
    void on_nextButton_clicked();
};

#endif // DIALOG_PATH_MATRIX_H
