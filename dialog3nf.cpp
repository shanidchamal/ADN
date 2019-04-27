#include "dialog3nf.h"
#include "ui_dialog3nf.h"

#include "dialog_fd_input.h"
#include "dialog2nf.h"

#include <QDebug>

int NF3_blacklist[30],bl3_count;

Dialog3nf::Dialog3nf(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog3nf)
{
    ui->setupUi(this);

    int i;
    QStringList det_k_titles,sim_k_titles,tIDs;

    tIDs << "table3NF1" << "table3NF2" << "table3NF3" << "table3NF4" << "table3NF5";

    findTransitive();

    qDebug() << "nf2_index:" << NF2_index << "Nf_count:" << NF_count;

    for(i=NF2_index;i<NF_count;i++)
        printNF3(i,tIDs,parent);

    printClosure3NF(parent);
}

Dialog3nf::~Dialog3nf()
{
    delete ui;
}

void Dialog3nf::findTransitive() {
    int i,j;

    for(i=0;i<fd_count;i++) {
        if(checkRowScope(i))
            if(strcmp(det_k[i],pk)!=0)
                if(!checkPkAttr(det_k[i]))
                    for(j=0;j<sim_k_count;j++) {
                        if(checkColScope(j,bl_count2))
                            if(strcmp(DM[i][j],"1")==0) {
                                NF_array[NF_count++]=i;
                                qDebug() << "i:%d" << i;
                                break;
                            }
                    }
    }
}

int Dialog3nf::checkPkAttr(char det_k[]) {
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
        char * tmp1=(char *)pk;
        do {
            int l=strcspn(tmp1,tok);
            sprintf(poi_sub_pk,"%.*s",l,tmp1);
            if(strcmp(sub_det_k,sub_pk)==0) {
                pk_flag=1;
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

void Dialog3nf::printNF3(int index, QStringList uIDs, QWidget *parent) {
    QStringList det_k_titles,sim_k_titles;
    int j,k,cols=0;

    bl2_index=bl_count2;
    det_k_titles << det_k[NF_array[index]];

    for(j=0;j<sim_k_count;j++)
    if(checkColScope(j,bl2_index))
        if(strcmp(DM[NF_array[index]][j],"1")==0 || strcmp(DM[NF_array[index]][j],"2")==0) {
            sim_k_titles << sim_k[j];
            if(!checkNF3_blacklist(j))
                if(strcmp(DM[NF_array[index]][j],"1")==0)
                    NF3_blacklist[bl3_count++]=j;
            cols++;
        }

    QTableWidget *obj;
    obj=parent->findChild<QTableWidget*>(uIDs[index-NF2_index]);

    obj->setColumnCount(cols);
    obj->setRowCount(1);
    obj->setHorizontalHeaderLabels(sim_k_titles);
    obj->setVerticalHeaderLabels(det_k_titles);
    obj->setEditTriggers(QAbstractItemView::NoEditTriggers);

        k=0;
        for(j=0;j<sim_k_count;j++) {
            if(checkColScope(j,bl2_index)) {
                if(strcmp(DM[NF_array[index]][j],"1")==0 || strcmp(DM[NF_array[index]][j],"2")==0) {
                    obj->setItem(0,k,new QTableWidgetItem(DM[NF_array[index]][j]));
                    obj->item(0,k)->setTextAlignment(Qt::AlignCenter);
                    k++;
                }
            }
        }
    obj->resizeColumnsToContents();
    obj->resizeRowsToContents();
}

int checkNF3_blacklist(int index) {
    int i,flag=0;

    for(i=0;i<bl3_count;i++)
        if(NF3_blacklist[i]==index) {
            flag=1;
            break;
        }
    return flag;
}

void Dialog3nf::printClosure3NF(QWidget *parent) {

    int i,j,rows=0,cols=0,a=0,b=0,flag=0;
    QStringList det_k_titles,sim_k_titles;

    for(i=0;i<fd_count;i++) {
        if(checkRowScope(i)) {
            rows++;
            det_k_titles << det_k[i];
        }
    }

    for(j=0;j<sim_k_count;j++) {
            if(checkColScope(j,bl_count2))
                    if(!checkNF3_blacklist(j)) {
                        cols++;
                        sim_k_titles << sim_k[j];
                }
    }

    QTableWidget *obj;
    obj=parent->findChild<QTableWidget*>("tableClosure3NF");

    obj->setColumnCount(cols);
    obj->setRowCount(rows);
    obj->setHorizontalHeaderLabels(sim_k_titles);
    obj->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    obj->setVerticalHeaderLabels(det_k_titles);
    obj->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    obj->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for(i=0;i<fd_count;i++) {
        flag=0;
        if(checkRowScope(i)) {
            flag=1;
            for(j=0;j<sim_k_count;j++) {
                    if(checkColScope(j,bl_count2))
                        if(!checkNF3_blacklist(j)) {
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
    obj->setSelectionMode(QAbstractItemView::NoSelection);
}

void Dialog3nf::on_nextButton_clicked()
{
    hide();
    dialog_bcnf=new Dialog_BCNF(this);
    dialog_bcnf->show();
}
