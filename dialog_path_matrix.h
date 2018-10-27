#ifndef DIALOG_PATH_MATRIX_H
#define DIALOG_PATH_MATRIX_H

#include <QDialog>

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
    void generate_total_k(char [][20]);
    void generate_ADJ(char [][20], char[][20]);
private slots:
    void on_pathButton_clicked();
};

#endif // DIALOG_PATH_MATRIX_H
