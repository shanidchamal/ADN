#include "dialog_dm_view.h"
#include "ui_dialog_dm_view.h"

#include "dialog_fd_input.h"

#include <QDebug>

char DM[20][20][30];
int dm_flag=0;

Dialog_DM_view::Dialog_DM_view(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_DM_view)
{
    ui->setupUi(this);
    //sort simple keys in lexicographic order
    sort();
    //Display initial DM
        int i,j;
        QStringList det_k_titles,sim_k_titles;
        for(i=0;i<sim_k_count;i++)
            sim_k_titles << sim_k[i];

        for(i=0;i<fd_count;i++) {
            qDebug() << "det_K" << det_k[i];
            det_k_titles << det_k[i];
        }

        ui->tableDM->setColumnCount(sim_k_count);
        ui->tableDM->setRowCount(fd_count);
        ui->tableDM->setHorizontalHeaderLabels(sim_k_titles);
        ui->tableDM->setVerticalHeaderLabels(det_k_titles);
        ui->tableDM->setEditTriggers(QAbstractItemView::NoEditTriggers);

        for(i=0;i<fd_count;i++) {
            for(j=0;j<sim_k_count;j++) {
                ui->tableDM->setItem(i,j,new QTableWidgetItem("0"));
                ui->tableDM->item(i,j)->setTextAlignment(Qt::AlignCenter);
            }
        }

        ui->tableDM->resizeColumnsToContents();
        ui->tableDM->resizeRowsToContents();
}

Dialog_DM_view::~Dialog_DM_view()
{
    delete ui;
}

void Dialog_DM_view::sort()
{
    char temp[30];
    int i,j;

    for(i=0;i<sim_k_count-1;i++) {
        for(j=i+1;j<sim_k_count;j++) {
            if(strcmp(sim_k[i],sim_k[j])>0) {
                strcpy(temp,sim_k[i]);
                strcpy(sim_k[i],sim_k[j]);
                strcpy(sim_k[j],temp);
            }
        }
    }
}

void Dialog_DM_view::on_dmButton_clicked()
{
    char sub_det_str[30],tok[]=",";
        char *poi_sub_det_str=(char *)sub_det_str;
        int i,j,k;

        for(i=0;i<fd_count;i++) {
            for(j=0;j<sim_k_count;j++) {
                for(k=0;k<edge_count;k++) {
                    //check for direct dependencies b/w det_k and sim_k
                    if(strcmp(sim_k[j],dep_edge[k])==0 && strcmp(det_edge[k],det_k[i])==0) {
                        strcpy(DM[i][j],"1");
                        break;
                    }
                }
                //check if sim_k and det_k are same(reflexivity)
                if(strcmp(DM[i][j],"1")!=0) {
                    if(strcmp(det_k[i],sim_k[j])==0)
                        strcpy(DM[i][j],"2");

                    //check if sim_k is subset of det_k
                    else if(strlen(det_k[i])>strlen(sim_k[j])) {
                        char *poi_det_str=(char *)det_k[i];
                        do {
                            int l=strcspn(poi_det_str,tok);
                            sprintf(poi_sub_det_str,"%.*s", l, poi_det_str);
                            if(strcmp(sub_det_str,sim_k[j])==0) {
                                strcpy(DM[i][j],"2");
                                break;
                            }
                            else
                                strcpy(DM[i][j],"0");
                            poi_det_str+=l+1;
                        } while(poi_det_str[-1]);
                    }
                    //Neither direct nor reflexive dependency
                    else
                        strcpy(DM[i][j],"0");
                }
            }
        }
        //print to tableDM
        for(i=0;i<fd_count;i++) {
            for(j=0;j<sim_k_count;j++) {
                ui->tableDM->setItem(i,j,new QTableWidgetItem(DM[i][j]));
                ui->tableDM->item(i,j)->setTextAlignment(Qt::AlignCenter);
            }
        }
        dm_flag=1;
}

void Dialog_DM_view::on_nextButton_clicked()
{
    if(dm_flag==1) {
        hide();
        dialog_dg_view=new Dialog_DG_view(this);
        dialog_dg_view->show();
    }
}
