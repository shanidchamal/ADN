#include "dialog_path_matrix.h"
#include "ui_dialog_path_matrix.h"

#include "dialog_fd_input.h"

int PATH[20][20],total_k_count,path_flag=0;

Dialog_path_matrix::Dialog_path_matrix(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_path_matrix)
{
    ui->setupUi(this);
    //generate total_k[][] (total key set or nodes in graph)
    char total_k[20][20],ADJ[20][20];
    int i,j;
    total_k_count=sim_k_count;

    generate_total_k(total_k);
    generate_ADJ(ADJ,total_k);
    //Display final ADJ
        QStringList total_k_titles;

        for(i=0;i<total_k_count;i++)
            total_k_titles << total_k[i];

        ui->tableADJ->setColumnCount(total_k_count);
        ui->tableADJ->setRowCount(total_k_count);
        ui->tableADJ->setHorizontalHeaderLabels(total_k_titles);
        ui->tableADJ->setVerticalHeaderLabels(total_k_titles);
        ui->tableADJ->setEditTriggers(QAbstractItemView::NoEditTriggers);

        for(i=0;i<total_k_count;i++) {
            for(j=0;j<total_k_count;j++) {
                ui->tableADJ->setItem(i,j,new QTableWidgetItem(QString::number(ADJ[i][j])));
                ui->tableADJ->item(i,j)->setTextAlignment(Qt::AlignCenter);
            }
        }

        ui->tableADJ->resizeColumnsToContents();
        ui->tableADJ->resizeRowsToContents();

        //Display initial PATH
        for(i=0;i<total_k_count;i++)
            for(j=0;j<total_k_count;j++)
                PATH[i][j]=ADJ[i][j];

        ui->tablePATH->setColumnCount(total_k_count);
        ui->tablePATH->setRowCount(total_k_count);
        ui->tablePATH->setHorizontalHeaderLabels(total_k_titles);
        ui->tablePATH->setVerticalHeaderLabels(total_k_titles);
        ui->tablePATH->setEditTriggers(QAbstractItemView::NoEditTriggers);

        for(i=0;i<total_k_count;i++) {
            for(j=0;j<total_k_count;j++) {
                ui->tablePATH->setItem(i,j,new QTableWidgetItem(QString::number(PATH[i][j])));
                ui->tablePATH->item(i,j)->setTextAlignment(Qt::AlignCenter);
                }
            }

        ui->tablePATH->resizeColumnsToContents();
        ui->tablePATH->resizeRowsToContents();
}

Dialog_path_matrix::~Dialog_path_matrix()
{
    delete ui;
}

void Dialog_path_matrix::generate_total_k(char total_k[][20]) {
    int i,j,flag;

    for(i=0;i<sim_k_count;i++)
        strcpy(total_k[i],sim_k[i]);

    //eliminate duplicates in det_k
    for(i=0;i<fd_count;i++) {
        flag=0;
        for(j=0;j<sim_k_count;j++) {
            if(strcmp(total_k[j],det_k[i])==0) {
                flag=1;
                break;
            }
        }
        if(flag==0)
            strcpy(total_k[total_k_count++],det_k[i]);
    }
}

void Dialog_path_matrix::generate_ADJ(char ADJ[][20],char total_k[][20]) {
    int i,j,det_index=-1,dep_index=-1;

    //initialize ADJ to 0
    for(i=0;i<total_k_count;i++) {
        for(j=0;j<total_k_count;j++) {
            ADJ[i][j]=0;
        }
    }
    //Generate ADJ Actual edges
    for(i=0;i<edge_count;i++) {
        for(j=0;j<total_k_count;j++) {
            if(strcmp(det_edge[i],total_k[j])==0)
                det_index=j;
            if(strcmp(dep_edge[i],total_k[j])==0)
                dep_index=j;
            if(det_index!=-1 && dep_index!=-1)
                break;
        }
        ADJ[det_index][dep_index]=1;
        det_index=-1;
        dep_index=-1;
    }
    //Generate ADJ Reflex edges
    for(i=0;i<reflex_edge_count;i++) {
        for(j=0;j<total_k_count;j++) {
            if(strcmp(reflex_det_edge[i],total_k[j])==0)
                det_index=j;
            if(strcmp(reflex_dep_edge[i],total_k[j])==0)
                dep_index=j;
            if(det_index!=-1 && dep_index!=-1)
                break;
        }
        ADJ[det_index][dep_index]=1;
        det_index=-1;
        dep_index=-1;
    }
}

void Dialog_path_matrix::on_pathButton_clicked()
{
    int i,j,k;
    //Warshall's algorithm to find path matrix
    for(k=0;k<total_k_count;k++) {
        for(i=0;i<total_k_count;i++)
            for(j=0;j<total_k_count;j++)
                PATH[i][j]=(PATH[i][j] || (PATH[i][k] && PATH[k][j]));
    }
    //print PATH to tablePATH
    for(i=0;i<total_k_count;i++) {
        for(j=0;j<total_k_count;j++) {
            ui->tablePATH->setItem(i,j,new QTableWidgetItem(QString::number(PATH[i][j])));
            ui->tablePATH->item(i,j)->setTextAlignment(Qt::AlignCenter);
        }
    }
    path_flag=1;
}

void Dialog_path_matrix::on_nextButton_clicked()
{
    if(path_flag==1) {
        hide();
        dialog_transitive_view=new Dialog_transitive_view(this);
        dialog_transitive_view->show();
    }
}
