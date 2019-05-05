#include "dialog_closure_view.h"
#include "ui_dialog_closure_view.h"

#include "dialog_fd_input.h"
#include "dialog_dm_view.h"
#include "dialog_transitive_view.h"

#include <QDebug>

char DM2[20][20][30],pk[30],ck[30],new_pk[30];
int NF_array[15],NF_count,sim_k_blacklist[30],can_k_index[10],rhs_det_k[10],lhs_det_k[10],bl_count,can_k_count,rhs_count,lhs_count,can_flag,dm_row;
Dialog2NF *dialog_2nf;

Dialog_closure_view::Dialog_closure_view(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_closure_view)
{
    ui->setupUi(this);
    int i,j,can_k_rank[10],top_rank,pk_rank,pk_index,returnval,flag;
    char can_k[10][30];
    QStringList det_k_titles,sim_k_titles;

    can_k_count=0;NF_count=0;bl_count=0;can_flag=0;dm_row=fd_count;lhs_count=0;
    memset(NF_array,-1,sizeof(NF_array));
    for(i=0;i<10;i++)
        memset(can_k[i],0,sizeof(can_k[i]));

    for(i=0;i<dm_row;i++) {
        for(j=0;j<sim_k_count;j++)
            strcpy(DM2[i][j],DM[i][j]);
    }

    dependency_closure();

    //circular_dependency();

    can_k_count=candidate_keys(can_k,can_k_index);
    //printf("can_count:%d\n",can_k_count);

    if(can_k_count!=0) {
        top_rank=findKeyRank(can_k,can_k_rank,can_k_count,can_flag);
        pk_index=primary_key(can_k,can_k_rank,top_rank,can_k_index,can_k_count);
        for(i=0;i<can_k_count;i++)
            if(pk_index==can_k_index[i])
                pk_rank=can_k_rank[i];
        strcpy(pk,det_k[pk_index]);
        //printf("primary_key:%s",pk);
    }

    for(i=0;i<dm_row;i++) {
        for(j=0;j<sim_k_count;j++) {
            char temp[30];
            strcpy(temp,DM[i][j]);
            strcpy(DM[i][j],DM2[i][j]);
            strcpy(DM2[i][j],temp);
        }
    }

    dependency_closure2(can_k,can_k_count,pk_index);

    circular_dependency();

    if(can_k_count==0) {
        candidate_key(can_k,can_k_count);
        printf("new can:%s",can_k[can_k_count]);
        can_flag=1;
        printf("lhs:");
        for(i=0;i<lhs_count;i++)
            printf("\t:%s",det_k[lhs_det_k[i]]);
        append2DM();
        pk_index=dm_row;
        strcpy(pk,can_k[can_k_count]);
        strcpy(ck,can_k[can_k_count]);
        top_rank=findKeyRank(can_k,can_k_rank,can_k_count,can_flag);
        printf("top rank:%d\n",top_rank);
        pk_rank=can_k_rank[can_k_count];
        dm_row+=1;
    }

    for(i=0;i<sim_k_count;i++)
        sim_k_titles << sim_k[i];

    for(i=0;i<dm_row;i++)
        det_k_titles << det_k[i];
    if(can_flag)
        det_k_titles[dm_row-1]=can_k[can_k_count];

    ui->tableClosure->setColumnCount(sim_k_count);
    ui->tableClosure->setRowCount(dm_row);
    ui->tableClosure->setHorizontalHeaderLabels(sim_k_titles);
    ui->tableClosure->setVerticalHeaderLabels(det_k_titles);
    ui->tableClosure->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for(i=0;i<dm_row;i++) {
        flag=0;
        if(checkCanIndex(i,can_k_index))
            flag=1;
        for(j=0;j<sim_k_count;j++) {
            if(flag && strcmp(DM[i][j],"0")==0)
                strcpy(DM[i][j],DM2[i][j]);
            ui->tableClosure->setItem(i,j,new QTableWidgetItem(DM[i][j]));
            ui->tableClosure->item(i,j)->setTextAlignment(Qt::AlignCenter);
        }
    }

    ui->tableClosure->resizeColumnsToContents();
    ui->tableClosure->resizeRowsToContents();
    //ui->tableClosure->selectRow(pk_index);
    ui->tableClosure->setSelectionMode(QAbstractItemView::NoSelection);


    ui->label_3->setText(can_k[0]);
    ui->label_7->setText(can_k[1]);
    ui->label_4->setText(can_k[2]);
    ui->label_5->setText(can_k[3]);
    ui->label_6->setText(can_k[4]);

    ui->label_9->setText(pk);

    //if(can_k_count!=0) {
        returnval=findPartial(pk_index,&pk_rank,can_flag);
        if(returnval!=-1) {
            strcpy(pk,det_k[returnval]);
            returnval=findPartial(returnval,&pk_rank,can_flag);
        }
        printf("new Pk:%s\n",pk);
    //}

}

Dialog_closure_view::~Dialog_closure_view()
{
    delete ui;
}

void Dialog_closure_view::dependency_closure()
{
    int i,j,k;
    //Dependency closure routine
    for(i=0;i<dm_row;i++)
        for(j=0;j<dm_row;j++)
            if(i!=j && det_PATH[i][j]!=-1) {
                for(k=0;k<sim_k_count;k++)
                    if(strcmp(DM[j][k],"0")!=0 && strcmp(DM[j][k],"2")!=0) {
                        strcpy(DM[i][k],det_k[j]);
                    }
                }
}

void Dialog_closure_view::dependency_closure2(char can_k[][30],int can_k_count,int pk_index)
{
    int i,j,k,l,flag;
    //Dependency closure routine2
    for(i=0;i<dm_row;i++) {
        for(j=0;j<dm_row;j++) {
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

    for(i=0;i<dm_row;i++) {
        for(j=0;j<sim_k_count;j++) {
            if(strcmp(DM[i][j],"0")!=0 && strcmp(DM[i][j],"1")!=0 && strcmp(DM[i][j],"2")!=0) {
                if(FindOne(i,j,dm_row) && strcmp(DM2[i][j],"1")==0)
                    strcpy(DM[i][j],"1");
                else if(strcmp(DM2[i][j],"2")==0)
                    strcpy(DM[i][j],"2");
            }
        }
    }
}

int Dialog_closure_view::FindOne(int i,int j,int n)
{
    int a,b;
    char element[30];
    strcpy(element,DM[i][j]);
    for(a=0;a<fd_count;a++)
        if(strcmp(det_k[a],element)==0) {
            b=a;
            break;
        }

    if(strcmp(DM[b][j],"1")==0 && n>=1)
        return 0;
    else if(n<1)
        return 1;
    else return FindOne(i,j,n-1);
}

int Dialog_closure_view::candidate_keys(char can_k[][30],int can_k_index[])
{
    int i,j,flag,count=0;
    for(i=0;i<dm_row;i++) {
        flag=0;
        for(j=0;j<sim_k_count;j++) {
            if(strcmp(DM[i][j],"0")==0) {
                flag=1;
                break;
            }
        }
        if(flag==0) {
            can_k_index[count]=i;
            strcpy(can_k[count],det_k[i]);
            count++;
        }
    }
    return count;
}

void Dialog_closure_view::candidate_key(char can_k[][30],int can_k_count) {
    char temp[30]="";
    int i,j;

    for(i=0;i<dm_row;i++) {
        for(j=0;j<sim_k_count;j++)
            if(strcmp(DM[i][j],"1")!=0 && strcmp(DM[i][j],"2")!=0 && strcmp(DM[i][j],"0")!=0)
                rhs_det_k[rhs_count++]=getDetKIndex(DM[i][j]);
    }

    for(i=0;i<fd_count;i++)
        if(!checkRHS(i)) {
            lhs_det_k[lhs_count++]=i;
            strcat(temp,det_k[i]);
            strcat(temp,",");
        }
    temp[strlen(temp)-1]='\0';
    strcpy(can_k[can_k_count],temp);
}

int Dialog_closure_view::getDetKIndex(char rhs_det_k[]) {
    int i;
    printf("in function:%s",rhs_det_k);
    for(i=0;i<fd_count;i++)
        if(strcmp(det_k[i],rhs_det_k)==0)
            return i;
    return 0;
}

int Dialog_closure_view::findKeyRank(char can_k[][30],int can_k_rank[],int can_k_count,int can_flag)
{
    int i,count,min;
    char tok[]=",";
    if(can_flag)
        can_k_count+=1;
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
    if(can_flag)
        return count;

    min=can_k_rank[0];
    for(i=1;i<can_k_count;i++) {
        if(can_k_rank[i]<=min)
            min=can_k_rank[i];
    }
    return min;
}

int Dialog_closure_view::primary_key(char can_k[][30],int can_k_rank[],int top,int can_k_index[],int can_k_count)
{
    int i,j,k,flag1=0,flag2=0,returnval=-1;

    for(i=0;i<can_k_count;i++) {
        if(can_k_rank[i]==top)
            for(j=0;j<sim_k_count;j++) {
                flag2=0;
                if(strcmp(DM[can_k_index[i]][j],"1")!=0 && strcmp(DM[can_k_index[i]][j],"2")!=0) {
                    for(k=0;k<can_k_count;k++) {
                        flag1=0;
                        if(k!=i)
                            if(strcmp(DM[can_k_index[i]][j],can_k[k])==0) {
                                flag1=1;
                                break;
                            }
                    }
                    if(flag1==1) {
                        break;
                    }
                }
            }
        if(flag1!=1) {
            returnval=can_k_index[i];
            break;
        }
    }
    if(returnval!=-1)
        return returnval;
    else
        return primary_key(can_k,can_k_rank,top+1,can_k_index,can_k_count);
}

int Dialog_closure_view::findPartial(int pk_index,int *pk_rank,int can_flag)
{
    int i,j,k,partial_k_rank=0,sub_dm_index,flag,flag2,flag3,lossy_flag=0;
    char tok[]=",";
    char sub_dm_k[30];
    char *poi_sub_dm_k=(char *)sub_dm_k;

    for(i=0;i<dm_row;i++) {
        if(i!=pk_index) {
            partial_k_rank=0;
            char * tmp=(char *)det_k[i];
            do {
                flag=0;
                int l=strcspn(tmp,tok);
                sprintf(poi_sub_dm_k,"%.*s",l,tmp);
                partial_k_rank++;
                sub_dm_index=findSim_k_Index(sub_dm_k);
                if(!(strcmp(DM[i][sub_dm_index],"2")==0 && strcmp(DM[pk_index][sub_dm_index],"2")==0)) {
                    flag=1;
                    break;
                }
                tmp+=l+1;
            }while(tmp[-1]);

            if(flag==0)
                if(partial_k_rank<(*pk_rank)) {
                    // this flag is for detecting fully functional(all 1/2) can key in case of can_flag
                    flag3=0;
                        for(j=0;j<sim_k_count;j++) {
                            flag2=0;
                            if(!checkSim_k_blacklist(j)) {
                                if(strcmp(DM[pk_index][j],"1")!=0) {
                                    if(strcmp(DM[pk_index][j],"2")!=0) {
                                        flag3=1;
                                        qDebug() << "flag3 when:" << DM[pk_index][j];
                                    }
                                    if(strcmp(DM[i][j],"0")==0) {
                                        if(!checkLHSonly(j)) {
                                            flag2=1;
                                            break;
                                        }
                                    }
                                }
                                else
                                    if(can_flag)
                                        if(strcmp(DM[i][j],"0")==0) {
                                            flag2=1;
                                            break;
                                        }
                        }
                }

                if(flag2==0) {
                    if(!can_flag) {
                        NF_array[NF_count++]=pk_index;
                        //can_k_index[can_k_count++]=i;
                        qDebug() << "addedwithchange:" << pk_index;
                        maskAttr();
                        *pk_rank=partial_k_rank;
                        return i;
                    }
                    else if(can_flag && !flag3) {
                        NF_array[NF_count++]=i;
                        qDebug() << "added:" << i;
                        maskAttr();
                    }
                    else {
                        /*for(k=0;k<sim_k_count;k++)
                            if(strcmp(DM[i][k],"1")==0)
                                if(lossy(i,k))
                                    lossy_flag=1;

                    if(!lossy_flag) {*/
                        *pk_rank=partial_k_rank;
                        return i;
                    }
                    /*else {
                        NF_array[NF_count++]=i;
                        qDebug() << "added in else:" << i;
                        maskAttr();
                    }
                    }*/
                }
                else {
                    NF_array[NF_count++]=i;
                    qDebug() << "added:" << i;
                    maskAttr();
                }
            }
            else {
                NF_array[NF_count++]=i;
                qDebug() << "added:" << i;
                maskAttr();
            }
        }
    }
    return -1;
}

int Dialog_closure_view::checkLHSonly(int index) {
    int i,flag=0;
    for(i=0;i<noof_lhs;i++)
        if(strcmp(LHSonly[i],sim_k[index])==0) {
            flag=1;
            break;
        }
    return flag;
}

//Mask associated attributes w.r.t partial key
void Dialog_closure_view::maskAttr()
{
    int j,partial;
    partial=NF_array[NF_count-1];
    qDebug() << "partial" << partial;
    for(j=0;j<sim_k_count;j++) {
        if(strcmp(DM[partial][j],"1")==0) {
            /*for(k=0;k<bl_count;k++) {
                flag=0;
                if(sim_k_blacklist[k]==j) {
                    flag=1;
                    break;
                }
            }
            if(!flag)*/
            qDebug() << "checking lossy:" << det_k[partial];
            if(!lossy(partial,j))
                sim_k_blacklist[bl_count++]=j;
        }
        else if(strcmp(DM[partial][j],"2")==0) {
            qDebug() << "checking:" << sim_k[j];
            if(!checkMaskValidity(partial,j))
                sim_k_blacklist[bl_count++]=j;
        }
    }
}

int lossy(int key,int index) {
    int i,flag=0;
    for(i=0;i<fd_count;i++)
        if((checkRowScope(i) || i>key) && strcmp(DM[i][index],"1")==0) {
                    flag=1;
                    qDebug() << "found 1 at:" << det_k[i];
                    break;
                }
    return flag;
}

int checkMaskValidity(int key,int index) {
    int i,flag=0;
    qDebug() << "key" << key;
    for(i=0;i<fd_count;i++)
            if(i!=key)
                if(checkRowScope(i))
                if(!checkCK(i,can_k_index))
                    if(strcmp(DM[i][index],"0")!=0) {
                        qDebug() << "noremove:" << sim_k[index] << "at" << det_k[i];
                        flag=1;
                        break;
                    }
    return flag;
}

int checkCK(int index,int can_k_index[]) {
    int i,flag=0;
    for(i=0;i<can_k_count;i++)
        if(strcmp(det_k[can_k_index[i]],pk)!=0)
            if(can_k_index[i]==index) {
                flag=1;
                break;
            }
    return flag;
}

int Dialog_closure_view::checkSim_k_blacklist(int index) {
    int i,flag=0;
    for(i=0;i<bl_count;i++)
        if(sim_k_blacklist[i]==index) {
            flag=1;
            break;
        }
    return flag;
}

int Dialog_closure_view::findSim_k_Index(char sub_dm_k[])
{
    int i;
    for(i=0;i<sim_k_count;i++)
        if(strcmp(sim_k[i],sub_dm_k)==0)
            return i;
}

int checkCanIndex(int index,int can_k_index[]) {
    int i,flag=0;
    for(i=0;i<can_k_count;i++)
        if(can_k_index[i]==index) {
            flag=1;
            break;
        }
    return flag;
}

int Dialog_closure_view::checkRHS(int index) {
    int i,flag=0;
    for(i=0;i<rhs_count;i++)
        if(rhs_det_k[i]==index) {
            flag=1;
            break;
        }
    return flag;
}

void Dialog_closure_view::append2DM() {
    int i,j,flag;
    for(j=0;j<sim_k_count;j++) {
        flag=0;
        for(i=0;i<lhs_count;i++)
            if(strcmp(DM[lhs_det_k[i]][j],"2")==0) {
                flag=1;
                strcpy(DM[dm_row][j],DM[lhs_det_k[i]][j]);
                break;
        }
        if(!flag)
            for(i=0;i<lhs_count;i++)
                if(strcmp(DM[lhs_det_k[i]][j],"1")==0) {
                    flag=1;
                    strcpy(DM[dm_row][j],DM[lhs_det_k[i]][j]);
                    break;
            }
        if(!flag)
            for(i=0;i<lhs_count;i++)
                if(strcmp(DM[lhs_det_k[i]][j],"0")!=0) {
                    flag=1;
                    strcpy(DM[dm_row][j],DM[lhs_det_k[i]][j]);
                    break;
            }
        }
}

void Dialog_closure_view::on_backButton_clicked()
{
    hide();
    dialog_transitive_view->show();
}

void Dialog_closure_view::on_nextButton_clicked()
{
    hide();
    if(dialog_2nf!=nullptr)
        dialog_2nf->show();
    else {
        dialog_2nf=new Dialog2NF(this);
        dialog_2nf->show();
    }
}
