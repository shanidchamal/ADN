#include "dialog2nf.h"
#include "ui_dialog2nf.h"

#include "dialog_fd_input.h"
#include <QDebug>
#include <QTableWidget>
#include <QObject>
#include <QDebug>

int pk_index,t_index3;

Dialog2NF::Dialog2NF(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog2NF)
{
    ui->setupUi(this);
    //printf("t-count:%d\n",NF_count);
    t_index3=NF_count;

    int i,j,sim_k_blacklist[30],bl_count=0,cols,rows;
    QStringList det_k_titles,sim_k_titles,tIDs;

    tIDs << "table2NF1" << "table2NF2" << "table2NF3";

    for(i=0;i<NF_count;i++)
        bl_count=print2NF(i,bl_count,sim_k_blacklist,tIDs,parent);

    det_k_titles.clear();
    sim_k_titles.clear();
    cols=0;
    rows=0;

    for(i=0;i<fd_count;i++) {
        if(checkRowScope(i)) {
            rows++;
            det_k_titles << det_k[i];
            if(strcmp(det_k[i],pk)==0)
                pk_index=rows-1;
        }
    }
    for(j=0;j<sim_k_count;j++) {
           if(checkColScope(j,bl_count,sim_k_blacklist)) {
                cols++;
                sim_k_titles << sim_k[j];
           }
    }

    printf("\n col count:%d",cols);
    ui->tableClosure->setColumnCount(cols);
    ui->tableClosure->setRowCount(rows);
    ui->tableClosure->setHorizontalHeaderLabels(sim_k_titles);
    ui->tableClosure->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableClosure->setVerticalHeaderLabels(det_k_titles);
    ui->tableClosure->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableClosure->setEditTriggers(QAbstractItemView::NoEditTriggers);


    int a=0,b=0,flag=0;
    for(i=0;i<fd_count;i++) {
        flag=0;
        if(checkRowScope(i)) {
            flag=1;
            for(j=0;j<sim_k_count;j++) {
                if(checkColScope(j,bl_count,sim_k_blacklist)) {
                    //printf("\na:%d\tb:%d",a,b);
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
    ui->tableClosure->selectRow(pk_index);
    ui->tableClosure->setSelectionMode(QAbstractItemView::NoSelection);
    ui->label_3->setText(pk);
    printf("\nbl_count:%d",bl_count);
}

Dialog2NF::~Dialog2NF()
{
    delete ui;
}

void Dialog2NF::on_nextButton_clicked()
{
    hide();
    dialog3nf = new Dialog3nf(this);
    dialog3nf->show();
}

int Dialog2NF::checkRowScope(int index) {
    int i,scope=1;

    for(i=0;i<NF_count;i++)
        if(NF_array[i]==index)
            scope=0;
    return scope;
}

int Dialog2NF::checkColScope(int index, int bl_count, int sim_k_blacklist[]) {
    int i,scope=1;

    for(i=0;i<bl_count;i++)
        if(sim_k_blacklist[i]==index)
            scope=0;
    return scope;
}

int Dialog2NF::checkPkAttr(char det_k[]) {
    int pk_flag;
    char tok[]=",";
    char sub_det_k[30],sub_pk[30];
    char* poi_sub_det_k=(char*)sub_det_k;
    char* tmp=(char*)det_k;
    char* poi_sub_pk=(char*)sub_pk;

    printf("\ndet_k[i]:%s",det_k);
    pk_flag=0;
    do {
        int l=strcspn(tmp,tok);
        sprintf(poi_sub_det_k,"%.*s",l,tmp);
        printf("\nsub_det_k:%s",sub_det_k);
        char * tmp1=(char *)pk;
        do {
            int l=strcspn(tmp1,tok);
            sprintf(poi_sub_pk,"%.*s",l,tmp1);
            printf("\nsub_pk:%s",sub_pk);
            if(strcmp(sub_det_k,sub_pk)==0) {
                pk_flag=1;
                printf("\nsub_det_k:%s\n",sub_det_k);
                break;
            }
            tmp1+=l+1;
        }while(tmp1[-1]);
        if(pk_flag)
            break;
        tmp+=l+1;
    }while(tmp[-1]);

    if(pk_flag)
        return 1;
    return 0;
}

int Dialog2NF::print2NF(int index, int bl_count, int sim_k_blacklist[], QStringList uIDs, QWidget *parent) {
    QStringList det_k_titles,sim_k_titles;
    int j,k,scope,cols=0,bl_index;

    bl_index=bl_count;
    det_k_titles.clear();
    sim_k_titles.clear();
    det_k_titles << det_k[NF_array[index]];

    for(j=0;j<sim_k_count;j++) {
        scope=1;
        for(k=0;k<bl_count;k++)
            if(sim_k_blacklist[k]==j)
                scope=0;
        if(scope)
            if(strcmp(DM[NF_array[index]][j],"1")==0 || strcmp(DM[NF_array[index]][j],"2")==0) {
                sim_k_titles << sim_k[j];
                printf("\nblacklisted key:%s",sim_k[j]);
                sim_k_blacklist[bl_count++]=j;
                cols++;
            }
    }
    printf("\nending bl_count:%d",bl_count);

    QTableWidget *obj=parent->findChild<QTableWidget*>(uIDs[index]);

    obj->setColumnCount(cols);
    obj->setRowCount(1);
    obj->setHorizontalHeaderLabels(sim_k_titles);
    obj->setVerticalHeaderLabels(det_k_titles);
    obj->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for(j=bl_index,k=0;j<bl_count;j++,k++) {
        obj->setItem(0,k,new QTableWidgetItem(DM[NF_array[index]][sim_k_blacklist[j]]));
        obj->item(0,k)->setTextAlignment(Qt::AlignCenter);
        }
    obj->resizeColumnsToContents();
    obj->resizeRowsToContents();

    return bl_count;
}
