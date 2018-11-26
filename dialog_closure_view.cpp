#include "dialog_closure_view.h"
#include "ui_dialog_closure_view.h"

#include "dialog_fd_input.h"
#include "dialog_dm_view.h"
#include "dialog_transitive_view.h"

char DM2[20][20][30];
int can_k_count;

Dialog_closure_view::Dialog_closure_view(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_closure_view)
{
    ui->setupUi(this);
    int i,j,can_k_index[10],can_k_rank[10],top_rank,pk_index;
    char can_k[10][30],pk[30];
    can_k_count=0;
    for(i=0;i<10;i++)
        memset(can_k[i],0,sizeof(can_k[i]));
    QStringList det_k_titles,sim_k_titles;
    for(i=0;i<sim_k_count;i++)
        sim_k_titles << sim_k[i];

    for(i=0;i<fd_count;i++)
        det_k_titles << det_k[i];

    ui->tableClosure->setColumnCount(sim_k_count);
    ui->tableClosure->setRowCount(fd_count);
    ui->tableClosure->setHorizontalHeaderLabels(sim_k_titles);
    ui->tableClosure->setVerticalHeaderLabels(det_k_titles);
    ui->tableClosure->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for(i=0;i<fd_count;i++) {
        for(j=0;j<sim_k_count;j++)
            strcpy(DM2[i][j],DM[i][j]);
    }

    dependency_closure();

    circular_dependency();

    can_k_count=candidate_keys(can_k,can_k_index);
    printf("can_count:%d\n",can_k_count);

    for(i=0;i<fd_count;i++) {
        for(j=0;j<sim_k_count;j++)
            strcpy(DM[i][j],DM2[i][j]);
    }

    dependency_closure2(can_k,can_k_count);

    circular_dependency();

    top_rank=findKeyRank(can_k,can_k_rank,can_k_count);

    if(can_k_count!=0) {
        pk_index=primary_key(can_k,can_k_rank,top_rank,can_k_index,can_k_count);
        strcpy(pk,det_k[pk_index]);
        printf("primary_key:%s",pk);
    }
    for(i=0;i<can_k_count;i++) {
        printf("\n%s\t",can_k[i]);
        printf("%d\t",can_k_index[i]);
        printf("%d\t",can_k_rank[i]);
    }

    for(i=0;i<fd_count;i++) {
        for(j=0;j<sim_k_count;j++) {
            ui->tableClosure->setItem(i,j,new QTableWidgetItem(DM[i][j]));
            ui->tableClosure->item(i,j)->setTextAlignment(Qt::AlignCenter);
        }
    }

    ui->tableClosure->resizeColumnsToContents();
    ui->tableClosure->resizeRowsToContents();

    if(can_k_count!=0) {
        ui->label_3->setText(can_k[0]);
        ui->label_7->setText(can_k[1]);
        ui->label_4->setText(can_k[2]);
        ui->label_5->setText(can_k[3]);
        ui->label_6->setText(can_k[4]);

        ui->label_9->setText(pk);
    }
    else {
        ui->label_3->setText("No Candidate keys");
        ui->label_9->setText("No primary key");
    }
}

Dialog_closure_view::~Dialog_closure_view()
{
    delete ui;
}

void Dialog_closure_view::dependency_closure()
{
    int i,j,k;
    //Dependency closure routine
    for(i=0;i<fd_count;i++) {
        for(j=0;j<fd_count;j++) {
            if(i!=j && det_PATH[i][j]!=-1 && strcmp(det_k[j],"clientNo,rentStart")!=0 && strcmp(det_k[j],"propertyNo,rentStart")!=0 && strcmp(det_k[j],"clientNo,propertyNo") && strcmp(det_k[j],"B,C,H")!=0 && strcmp(det_k[j],"B,C,F")!=0) {
            //if(i!=j && det_PATH[i][j]!=-1 && strcmp(det_k[j],"B,C,F")!=0 && strcmp(det_k[j],"B,C,H")!=0) {
            //if(i!=j && det_PATH[i][j]!=-1) {
                for(k=0;k<sim_k_count;k++) {
                    if(strcmp(DM[j][k],"0")!=0 && strcmp(DM[j][k],"2")!=0)
                        strcpy(DM[i][k],det_k[j]);
                }
            }
        }
    }
}

void Dialog_closure_view::dependency_closure2(char can_k[][30],int can_k_count)
{
    int i,j,k,l,flag;
    //Dependency closure routine2
    for(i=0;i<fd_count;i++) {
        for(j=0;j<fd_count;j++) {
            flag=0;
            //consider dependency through potential candidate keys
            for(l=0;l<can_k_count;l++) {
                if(strcmp(det_k[j],can_k[l])==0) {
                    flag=1;
                    break;
                }
                }
            if(flag!=1) {
                if(i!=j && det_PATH[i][j]!=-1) {
                    for(k=0;k<sim_k_count;k++) {
                        if(strcmp(DM[j][k],"0")!=0 && strcmp(DM[j][k],"2")!=0)
                            strcpy(DM[i][k],det_k[j]);
                    }
                }
            }
        }
    }
}

void Dialog_closure_view::circular_dependency()
{
    int i,j;

    for(i=0;i<fd_count;i++) {
        for(j=0;j<sim_k_count;j++) {
            if(strcmp(DM[i][j],"0")!=0 && strcmp(DM[i][j],"1")!=0 && strcmp(DM[i][j],"2")!=0)
                if(FindOne(i,j,j,fd_count) && strcmp(DM2[i][j],"1")==0)
                    strcpy(DM[i][j],"1");
        }
    }
}

int Dialog_closure_view::FindOne(int i,int j,int k,int n)
{
    if(strcmp(DM[j][k],"1")==0 && n>=1)
        return 0;
    else if(n<1)
        return 1;
    else return FindOne(i,i,k,n-1);
}

int Dialog_closure_view::candidate_keys(char can_k[][30],int can_k_index[])
{
    int i,j,flag,count=0;
    for(i=0;i<fd_count;i++) {
        flag=0;
        for(j=0;j<sim_k_count;j++)
            if(strcmp(DM[i][j],"0")==0) {
                flag=1;
                break;
            }
        if(flag==0) {
            can_k_index[count]=i;
            strcpy(can_k[count],det_k[i]);
            count++;
        }
    }
    return count;
}

int Dialog_closure_view::findKeyRank(char can_k[][30],int can_k_rank[],int can_k_count)
{
    int i,count,min;
    char tok[]=",";
    for(i=0;i<can_k_count;i++) {
        char * tmp=(char *) can_k[i];
        count=0;
        do {
            int l=strcspn(tmp,tok);
            count++;
            tmp+=l+1;
        }while(tmp[-1]);
        can_k_rank[i]=count;
    }

    min=can_k_rank[0];
    for(i=1;i<can_k_count;i++) {
        if(can_k_rank[i]<=min)
            min=can_k_rank[i];
    }
    return min;
}

int Dialog_closure_view::primary_key(char can_k[][30],int can_k_rank[],int top,int can_k_index[],int can_k_count)
{
    int i,j,k,flag1=0,flag2,flag3,flag4,returnval=-1;
    char tok[]=",";
    char sub_can_k[30],sub_det_k[30],sub_dm_k[30];
    char *poi_sub_can_k=(char *)sub_can_k;
    char *poi_sub_det_k=(char *)sub_det_k;
    char *poi_sub_dm_k=(char *)sub_dm_k;

    for(i=0;i<can_k_count;i++) {
        flag3=0;
        if(can_k_rank[i]==top)
            for(j=0;j<sim_k_count;j++) {
                flag2=0;
                if(strcmp(DM[can_k_index[i]][j],"1")!=0 && strcmp(DM[can_k_index[i]][j],"2")!=0) {
                    char * tmp=(char *)DM[can_k_index[i]][j];
                    do {
                        flag1=0;
                        int l=strcspn(tmp,tok);
                        sprintf(poi_sub_dm_k,"%.*s",l,tmp);
                        for(k=0;k<can_k_count;k++) {
                            if(k!=i) {
                                char * tmp2=(char *)can_k[k];
                                do {
                                    int m=strcspn(tmp2,tok);
                                    sprintf(poi_sub_can_k,"%.*s",m,tmp2);
                                    if(strcmp(sub_dm_k,sub_can_k)==0) {
                                        flag1=1;
                                        break;
                                    }
                                    tmp2+=m+1;
                                }while(tmp2[-1]);
                                if(flag1==1) {
                                    char * tmp3=(char *)can_k[i];
                                    do {
                                        flag4=0;
                                        int n=strcspn(tmp3,tok);
                                        sprintf(poi_sub_det_k,"%.*s",n,tmp3);
                                        if(strcmp(sub_det_k,sub_dm_k)==0) {
                                            flag4=1;
                                            break;
                                        }
                                        tmp3+=n+1;
                                    }while(tmp3[-1]);
                                    if(flag4==1)
                                        flag1=0;
                                    break;
                                }
                            }
                        }
                        if(flag1==1) {
                            flag2=1;
                            break;
                        }
                        tmp+=l+1;
                    }while(tmp[-1]);
                    if(flag2==1) {
                        flag3=1;
                        break;
                    }
                }
            }
        if(flag3!=1) {
            returnval=can_k_index[i];
            break;
        }
    }
    if(returnval!=-1)
        return returnval;
    else
        return primary_key(can_k,can_k_rank,top+1,can_k_index,can_k_count);
}

void Dialog_closure_view::on_backButton_clicked()
{
    hide();
    dialog_transitive_view->show();
}
