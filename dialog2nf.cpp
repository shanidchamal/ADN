#include "dialog2nf.h"
#include "ui_dialog2nf.h"

#include "dialog_fd_input.h"
Dialog2NF::Dialog2NF(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog2NF)
{
    ui->setupUi(this);
    int i,j,k,scope,sim_k_blacklist[30],bl_count=0,cols,rows,curr_bl_val;
    char uiTableID[3][10];

    strcpy(uiTableID[0],"table2NF1");strcpy(uiTableID[1],"table2NF2");strcpy(uiTableID[2],"table2NF3");
    //printing first 2NF
    QStringList det_k_titles,sim_k_titles;

    if(transformer[0]!=-1) {
        cols=0;
        curr_bl_val=bl_count;
        det_k_titles << det_k[transformer[0]];
        for(j=0;j<sim_k_count;j++) {
        if(strcmp(DM[transformer[0]][j],"1")==0 || strcmp(DM[transformer[0]][j],"2")==0) {
            sim_k_titles << sim_k[j];
            sim_k_blacklist[bl_count++]=j;
            cols++;
            }
        }
        ui->table2NF1->setColumnCount(cols);
        ui->table2NF1->setRowCount(1);
        ui->table2NF1->setHorizontalHeaderLabels(sim_k_titles);
        ui->table2NF1->setVerticalHeaderLabels(det_k_titles);
        ui->table2NF1->setEditTriggers(QAbstractItemView::NoEditTriggers);

        for(j=curr_bl_val;j<bl_count;j++) {
            ui->table2NF1->setItem(0,j,new QTableWidgetItem(DM[transformer[0]][sim_k_blacklist[j]]));
            ui->table2NF1->item(0,j)->setTextAlignment(Qt::AlignCenter);
        }
        ui->table2NF1->resizeColumnsToContents();
        ui->table2NF1->resizeRowsToContents();
    }

    if(transformer[1]!=-1) {
        cols=0;
        printf("\nstarting bl_count:%d",bl_count);
        curr_bl_val=bl_count;
        det_k_titles.clear();
        sim_k_titles.clear();
        det_k_titles << det_k[transformer[1]];
        for(j=0;j<sim_k_count;j++) {
            scope=1;
            for(k=0;k<bl_count;k++)
                if(sim_k_blacklist[k]==j)
                    scope=0;
            if(scope)
                if(strcmp(DM[transformer[1]][j],"1")==0 || strcmp(DM[transformer[1]][j],"2")==0) {
                    sim_k_titles << sim_k[j];
                    printf("\nblacklisted key:%s",sim_k[j]);
                    sim_k_blacklist[bl_count++]=j;
                    cols++;
        }
        }
        printf("\nending bl_count:%d",bl_count);
        ui->table2NF2->setColumnCount(cols);
        ui->table2NF2->setRowCount(1);
        ui->table2NF2->setHorizontalHeaderLabels(sim_k_titles);
        ui->table2NF2->setVerticalHeaderLabels(det_k_titles);
        ui->table2NF2->setEditTriggers(QAbstractItemView::NoEditTriggers);


        for(j=curr_bl_val,k=0;j<bl_count;j++,k++) {
            ui->table2NF2->setItem(0,k,new QTableWidgetItem(DM[transformer[1]][sim_k_blacklist[j]]));
            ui->table2NF2->item(0,k)->setTextAlignment(Qt::AlignCenter);
            }
        ui->table2NF2->resizeColumnsToContents();
        ui->table2NF2->resizeRowsToContents();
    }

    if(transformer[2]!=-1) {
        cols=0;
        printf("\nstarting bl_count:%d",bl_count);
        curr_bl_val=bl_count;
        det_k_titles.clear();
        sim_k_titles.clear();
        det_k_titles << det_k[transformer[2]];
        for(j=0;j<sim_k_count;j++) {
            scope=1;
            for(k=0;k<bl_count;k++)
                if(sim_k_blacklist[k]==j)
                    scope=0;
            if(scope)
                if(strcmp(DM[transformer[2]][j],"1")==0 || strcmp(DM[transformer[2]][j],"2")==0) {
                    sim_k_titles << sim_k[j];
                    printf("\nblacklisted key:%s",sim_k[j]);
                    sim_k_blacklist[bl_count++]=j;
                    cols++;
        }
        }
        printf("\nending bl_count:%d",bl_count);
        ui->table2NF3->setColumnCount(cols);
        ui->table2NF3->setRowCount(1);
        ui->table2NF3->setHorizontalHeaderLabels(sim_k_titles);
        ui->table2NF3->setVerticalHeaderLabels(det_k_titles);
        ui->table2NF3->setEditTriggers(QAbstractItemView::NoEditTriggers);


        for(j=curr_bl_val,k=0;j<bl_count;j++,k++) {
            ui->table2NF3->setItem(0,k,new QTableWidgetItem(DM[transformer[2]][sim_k_blacklist[j]]));
            ui->table2NF3->item(0,k)->setTextAlignment(Qt::AlignCenter);
            }
        ui->table2NF3->resizeColumnsToContents();
        ui->table2NF3->resizeRowsToContents();
    }

    det_k_titles.clear();
    sim_k_titles.clear();
    cols=0;
    rows=0;

    for(i=0;i<bl_count;i++)
        printf("\t%d",sim_k_blacklist[i]);

    for(i=0;i<fd_count;i++) {
        scope=1;
        for(k=0;k<t_count;k++)
            if(transformer[k]==i)
                scope=0;
        if(scope) {
            rows++;
            det_k_titles << det_k[i];
        }
    }
            int l;
            for(j=0;j<sim_k_count;j++) {
                scope=1;
                for(l=0;l<bl_count;l++)
                    if(sim_k_blacklist[l]==j)
                        scope=0;
                if(scope) {
                    cols++;
                    sim_k_titles << sim_k[j];
                }
    }

    printf("\n col count:%d",cols);
    ui->tableClosure->setColumnCount(cols);
    ui->tableClosure->setRowCount(rows);
    ui->tableClosure->setHorizontalHeaderLabels(sim_k_titles);
    ui->tableClosure->setVerticalHeaderLabels(det_k_titles);
    ui->tableClosure->setEditTriggers(QAbstractItemView::NoEditTriggers);


    int a=0,b=0,flag=0;
    for(i=0;i<fd_count;i++) {
        flag=0;
        scope=1;
        for(k=0;k<t_count;k++)
            if(transformer[k]==i)
                scope=0;
        if(scope) {
            flag=1;
            for(j=0;j<sim_k_count;j++) {
                scope=1;
                for(l=0;l<bl_count;l++)
                    if(sim_k_blacklist[l]==j)
                        scope=0;
                if(scope) {
                    printf("\na:%d\tb:%d",a,b);
                    ui->tableClosure->setItem(a,b,new QTableWidgetItem(DM[i][j]));
                    ui->tableClosure->item(a,b)->setTextAlignment(Qt::AlignCenter);
                    b++;
                }
            }
        }
        if(flag)
            a++;
        b=0;
    }

}

Dialog2NF::~Dialog2NF()
{
    delete ui;
}
