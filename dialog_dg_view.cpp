#include "dialog_dg_view.h"
#include "ui_dialog_dg_view.h"

#include "dialog_fd_input.h"
#include "dialog_dm_view.h"

Dialog_DG_view::Dialog_DG_view(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_DG_view)
{
    ui->setupUi(this);
    //Display initial DG
        int i,j;
        QStringList det_k_titles;

        for(i=0;i<fd_count;i++)
            det_k_titles << det_k[i];

        ui->tableDG->setColumnCount(fd_count);
        ui->tableDG->setRowCount(fd_count);
        ui->tableDG->setHorizontalHeaderLabels(det_k_titles);
        ui->tableDG->setVerticalHeaderLabels(det_k_titles);
        ui->tableDG->setEditTriggers(QAbstractItemView::NoEditTriggers);

        for(i=0;i<fd_count;i++) {
            for(j=0;j<fd_count;j++) {
                ui->tableDG->setItem(i,j,new QTableWidgetItem("0"));
                ui->tableDG->item(i,j)->setTextAlignment(Qt::AlignCenter);
            }
        }

        ui->tableDG->resizeColumnsToContents();
        ui->tableDG->resizeRowsToContents();
}

Dialog_DG_view::~Dialog_DG_view()
{
    delete ui;
}

void Dialog_DG_view::on_dgButton_clicked()
{
    int DG[20][20],flag,i,j,k;
        char sub_dg[30],tok[]=",";
        char * poi_sub_dg=(char *)sub_dg;

        for(i=0;i<fd_count;i++) {
            for(j=0;j<sim_k_count;j++) {
                flag=0;
                //check det_k and sim_k are same
                if(strcmp(det_k[i],sim_k[j])==0)
                    flag=1;
                else if(strlen(det_k[i])>strlen(sim_k[j])) {
                    char * poi_dg_str=(char *)det_k[i];
                    do {
                        int l=strcspn(poi_dg_str,tok);
                        sprintf(poi_sub_dg,"%.*s",l,poi_dg_str);
                        if(strcmp(sub_dg,sim_k[j])==0)
                            flag=1;
                        poi_dg_str+=l+1;
                    } while(poi_dg_str[-1]);
                }
                else
                    continue;
                if(flag==1) {
                    for(k=0;k<fd_count;k++) {
                        if(strcmp(DM[k][j],"0")!=0 && DG[k][i]!=-1)
                            DG[k][i]=1;
                        else
                            DG[k][i]=-1;
                    }
                }
            }
        }
        //print to tableDG
        for(i=0;i<fd_count;i++) {
            for(j=0;j<fd_count;j++) {
                ui->tableDG->setItem(i,j,new QTableWidgetItem(QString::number(DG[i][j])));
                ui->tableDG->item(i,j)->setTextAlignment(Qt::AlignCenter);
            }
        }
}
