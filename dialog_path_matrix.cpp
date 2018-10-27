#include "dialog_path_matrix.h"
#include "ui_dialog_path_matrix.h"

#include "dialog_fd_input.h"

Dialog_path_matrix::Dialog_path_matrix(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_path_matrix)
{
    ui->setupUi(this);
    //generate total_k[][] (total key set or nodes in graph)
    char total_k[20][20],ADJ[20][20];
    int i,j,total_k_count=sim_k_count;

    generate_total_k(total_k,&sim_k_count);
    generate_ADJ(ADJ,total_k,total_k_count);
}

Dialog_path_matrix::~Dialog_path_matrix()
{
    delete ui;
}

void Dialog_path_matrix::generate_total_k(char total_k[][20], int *n) {
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
            strcpy(total_k[(*n)++],det_k[i]);
    }
}

void Dialog_path_matrix::generate_ADJ(char ADJ[][20],char total_k[][20],int total_k_count) {
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