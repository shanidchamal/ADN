#include "dialog_transitive_view.h"
#include "ui_dialog_transitive_view.h"

#include "dialog_fd_input.h"
#include "dialog_path_matrix.h"

int transitve_flag=0;

Dialog_transitive_view::Dialog_transitive_view(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_transitive_view)
{
    ui->setupUi(this);
    //Display initial det_PATH
        int i,j;
        QStringList det_k_titles;

        for(i=0;i<fd_count;i++)
            det_k_titles << det_k[i];

        ui->tableDetPath->setColumnCount(fd_count);
        ui->tableDetPath->setRowCount(fd_count);
        ui->tableDetPath->setHorizontalHeaderLabels(det_k_titles);
        ui->tableDetPath->setVerticalHeaderLabels(det_k_titles);
        ui->tableDetPath->setEditTriggers(QAbstractItemView::NoEditTriggers);

        for(i=0;i<fd_count;i++) {
            for(j=0;j<fd_count;j++) {
                ui->tableDetPath->setItem(i,j,new QTableWidgetItem("0"));
                ui->tableDetPath->item(i,j)->setTextAlignment(Qt::AlignCenter);
            }
        }

        ui->tableDetPath->resizeColumnsToContents();
        ui->tableDetPath->resizeRowsToContents();
}

Dialog_transitive_view::~Dialog_transitive_view()
{
    delete ui;
}

void Dialog_transitive_view::on_detPathButton_clicked()
{
    //generate det_PATH(determinant key transitive dependencies
    char det_PATH[20][20],sub_fd[30],tok[]=",";
    char * poi_sub_fd=(char *)sub_fd;
    int i,j,k,no_path_flag,det_index=-1,dep_index=-1;

    for(i=0;i<fd_count;i++) {
        for(j=0;j<fd_count;j++) {
            no_path_flag=0;
            //node is same
            if(i==j)
                det_PATH[i][j]=1;
            //decompose jth determinant key to sub keys
            else {
                char * tmp=(char *)det_k[j];
                do {
                    int l=strcspn(tmp,tok);
                    sprintf(poi_sub_fd,"%.*s",l,tmp);
                    if(strcmp(det_k[i],sub_fd)!=0) {
                        //retrieve indices for det_k and sub_fd in PATH
                        for(k=0;k<total_k_count;k++) {
                            if(strcmp(total_k[k],det_k[i])==0)
                                det_index=k;
                            if(strcmp(total_k[k],sub_fd)==0)
                                dep_index=k;
                            if(det_index!=-1 && dep_index!=-1)
                                break;
                        }
                        //check if PATH exists
                        if(PATH[det_index][dep_index]!=1)
                            no_path_flag=1;
                        det_index=-1;
                        dep_index=-1;
                        if(no_path_flag)
                            break;
                    }
                    tmp+=l+1;
                } while(tmp[-1]);
                if(!no_path_flag)
                    det_PATH[i][j]=1;
                else
                    det_PATH[i][j]=-1;
            }
        }
    }
    //print PATH to tableDetPath
    for(i=0;i<fd_count;i++) {
        for(j=0;j<fd_count;j++) {
            ui->tableDetPath->setItem(i,j,new QTableWidgetItem(QString::number(det_PATH[i][j])));
            ui->tableDetPath->item(i,j)->setTextAlignment(Qt::AlignCenter);
        }
    }
    transitve_flag=1;
}

void Dialog_transitive_view::on_nextButton_clicked()
{
    if(transitve_flag==1) {
        hide();
        dialog_closure_view=new Dialog_closure_view(this);
        dialog_closure_view->show();
    }
}
