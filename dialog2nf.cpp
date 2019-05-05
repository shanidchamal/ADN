#include "dialog2nf.h"
#include "ui_dialog2nf.h"

#include "dialog_fd_input.h"
#include <QDebug>
#include <QTableWidget>
#include <QObject>
#include <QDebug>

int pk_index,NF2_index,NF_blacklist[30],bl_count2,bl2_index;
Dialog3nf *dialog3nf;

Dialog2NF::Dialog2NF(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog2NF)
{
    ui->setupUi(this);
    //printf("t-count:%d\n",NF_count);
    NF2_index=NF_count;
    bl_count2=0;
    bl2_index=0;

    int i;
    QStringList det_k_titles,sim_k_titles,tIDs;

    tIDs << "table2NF1" << "table2NF2" << "table2NF3";

    for(i=0;i<NF_count;i++)
        printNF2(i,tIDs,parent);

    printClosure2NF(parent);

    ui->label_3->setText(pk);
}

Dialog2NF::~Dialog2NF()
{
    delete ui;
}

void Dialog2NF::on_nextButton_clicked()
{
    hide();
    if(dialog3nf!=nullptr)
        dialog3nf->show();
    else {
        if(can_flag && strcmp(ck,pk)==0)
            dm_row-=1;
        dialog3nf = new Dialog3nf(this);
        dialog3nf->show();
    }
}

int checkRowScope(int index) {
    int i,scope=1;

    for(i=0;i<NF_count;i++)
        if(NF_array[i]==index) {
            scope=0;
            break;
        }
    return scope;
}

int checkColScope(int index,int limit) {
    int i,scope=1;

    for(i=0;i<limit;i++)
        if(NF_blacklist[i]==index) {
            scope=0;
            break;
        }
    return scope;
}


void Dialog2NF::printNF2(int index, QStringList uIDs, QWidget *parent) {
    QStringList det_k_titles,sim_k_titles;
    int i,j,k,cols=0,bl_index=0,lossy_flag=0,lossy_list[5],lossy_count=0;

    bl_index=bl_count2;
    det_k_titles << det_k[NF_array[index]];

    qDebug() << "printNf2:" << NF_array[index];

    for(j=0;j<sim_k_count;j++) {
            if(checkColScope(j,bl_count2)) {
                if(strcmp(DM[NF_array[index]][j],"1")==0) {
                    sim_k_titles << sim_k[j];
                    NF_blacklist[bl_count2++]=j;
                    cols++;
                    if(lossy(NF_array[index],j)) {
                        lossy_flag=1;
                        lossy_list[lossy_count++]=j;
                    }
                }
                else if(strcmp(DM[NF_array[index]][j],"2")==0)
                    if(!checkMaskValidity(NF_array[index],j)) {
                        qDebug() << "pk_index:" << pk_index;
                        NF_blacklist[bl_count2++]=j;
                        sim_k_titles << sim_k[j];
                        cols++;
                    }
            }
    }

    qDebug() << "before";
    for(i=0;i<bl_count2;i++)
        qDebug() << NF_blacklist[i];

    QTableWidget *obj;
    obj=parent->findChild<QTableWidget*>(uIDs[index]);

    obj->setColumnCount(cols);
    obj->setRowCount(1);
    obj->setHorizontalHeaderLabels(sim_k_titles);
    obj->setVerticalHeaderLabels(det_k_titles);
    obj->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for(j=bl_index,k=0;j<bl_count2;j++,k++) {
        obj->setItem(0,k,new QTableWidgetItem(DM[NF_array[index]][NF_blacklist[j]]));
        obj->item(0,k)->setTextAlignment(Qt::AlignCenter);
    }

    if(lossy_flag)
        for(i=0;i<lossy_count;i++)
            for(j=0;j<bl_count2;j++)
                if(NF_blacklist[j]==lossy_list[i]) {
                    qDebug() << "at:" << NF_array[index];
                    for(k=j;k<bl_count2-1;k++)
                        NF_blacklist[k]=NF_blacklist[k+1];
                    bl_count2-=1;
                }
    qDebug() << "after";
    for(i=0;i<bl_count2;i++)
        qDebug() << NF_blacklist[i];


    obj->resizeColumnsToContents();
    obj->resizeRowsToContents();
}

void Dialog2NF::printClosure2NF(QWidget *parent) {

    int i,j,rows=0,cols=0,a=0,b=0,flag=0;
    QStringList det_k_titles,sim_k_titles;

    for(i=0;i<fd_count;i++) {
        if(checkRowScope(i)) {
            rows++;
            det_k_titles << det_k[i];
            if(strcmp(det_k[i],pk)==0)
                pk_index=rows-1;
        }
    }

    if(can_flag) {
        det_k_titles.append(ck);
        rows++;
    }

    for(j=0;j<sim_k_count;j++) {
            if(checkColScope(j,bl_count2)) {
                cols++;
                sim_k_titles << sim_k[j];
            }
    }

    QTableWidget *obj;
    obj=parent->findChild<QTableWidget*>("tableClosure2NF");

    obj->setColumnCount(cols);
    obj->setRowCount(rows);
    obj->setHorizontalHeaderLabels(sim_k_titles);
    obj->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    obj->setVerticalHeaderLabels(det_k_titles);
    obj->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    obj->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for(i=0;i<dm_row;i++) {
        flag=0;
        if(checkRowScope(i)) {
            flag=1;
            for(j=0;j<sim_k_count;j++) {
                    if(checkColScope(j,bl_count2)) {
                        obj->setItem(a,b,new QTableWidgetItem(DM[i][j]));
                        obj->item(a,b)->setTextAlignment(Qt::AlignCenter);
                        b++;
                    }
            }
        }
        if(flag)
            a++;
        b=0;
    }
    //obj->selectRow(pk_index);
    obj->setSelectionMode(QAbstractItemView::NoSelection);
}

void Dialog2NF::on_backButton_clicked()
{
    hide();
    dialog_closure_view->show();
}
