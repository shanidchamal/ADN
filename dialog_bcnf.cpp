#include "dialog_bcnf.h"
#include "ui_dialog_bcnf.h"
#include "dialog_fd_input.h"
#include "dialog3nf.h"

int BCNF_blacklist[30],bcnf_count,NF3_index;

Dialog_BCNF::Dialog_BCNF(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_BCNF)
{
    ui->setupUi(this);

    int i;
    NF3_index=NF_count;
    QStringList det_k_titles,sim_k_titles,tIDs;

    tIDs << "tableBCNF1" << "tableBCNF2" << "tableBCNF3";

    findBCNF();

    for(i=NF3_index;i<NF_count;i++)
        printBCNF(i,tIDs,parent);

    printClosureBCNF(parent);

    ui->label_3->setText(pk);
}

Dialog_BCNF::~Dialog_BCNF()
{
    delete ui;
}

void Dialog_BCNF::findBCNF() {
    int i,j;

    for(i=0;i<dm_row;i++) {
        if(checkRowScope(i))
            if(strcmp(det_k[i],pk)!=0)
                for(j=0;j<sim_k_count;j++) {
                    if(checkColScope(j,bl_count2))
                        if(!checkNF3_blacklist(j))
                            if(strcmp(DM[i][j],"0")==0) {
                                NF_array[NF_count++]=i;
                                break;
                        }
                }
    }
}

void Dialog_BCNF::printBCNF(int index, QStringList uIDs, QWidget *parent) {
    QStringList det_k_titles,sim_k_titles;
    int j,k,cols=0;
    det_k_titles << det_k[NF_array[index]];

    for(j=0;j<sim_k_count;j++)
    if(checkColScope(j,bl2_index))
        if(!checkNF3_blacklist(j))
        if(strcmp(DM[NF_array[index]][j],"1")==0 || strcmp(DM[NF_array[index]][j],"2")==0) {
            sim_k_titles << sim_k[j];
            if(!checkNF3_blacklist(j))
                if(strcmp(DM[NF_array[index]][j],"1")==0)
                    BCNF_blacklist[bcnf_count++]=j;
            cols++;
        }

    QTableWidget *obj;
    obj=parent->findChild<QTableWidget*>(uIDs[index-NF3_index]);

    obj->setColumnCount(cols);
    obj->setRowCount(1);
    obj->setHorizontalHeaderLabels(sim_k_titles);
    obj->setVerticalHeaderLabels(det_k_titles);
    obj->setEditTriggers(QAbstractItemView::NoEditTriggers);

        k=0;
        for(j=0;j<sim_k_count;j++) {
            if(checkColScope(j,bl2_index))
                if(!checkNF3_blacklist(j)) {
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

void Dialog_BCNF::printClosureBCNF(QWidget *parent) {

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
                    if(!checkNF3_blacklist(j) && !checkBCNF_blacklist(j)) {
                        cols++;
                        sim_k_titles << sim_k[j];
                }
    }

    QTableWidget *obj;
    obj=parent->findChild<QTableWidget*>("tableClosureBCNF");

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
                    if(checkColScope(j,bl_count2))
                        if(!checkNF3_blacklist(j) && !checkBCNF_blacklist(j)) {
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

int Dialog_BCNF::checkBCNF_blacklist(int index) {
    int i,flag=0;

    for(i=0;i<bcnf_count;i++)
        if(BCNF_blacklist[i]==index) {
            flag=1;
            break;
        }
    return flag;
}


void Dialog_BCNF::on_backButton_clicked()
{
    hide();
    dialog3nf->show();
}
