#include "dialog_fd_input.h"
#include "ui_dialog_fd_input.h"

struct det_fd_node *det_head[6];
struct dep_fd_node *dep_head[6];
int fd_count=0;

Dialog_fd_input::Dialog_fd_input(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_fd_input)
{
    ui->setupUi(this);
    //initialize head to NULL
    int i;
        for(i=0;i<6;i++)
        {
             det_head[i]=NULL;
             dep_head[i]=NULL;
        }
}

Dialog_fd_input::~Dialog_fd_input()
{
    delete ui;
}

void Dialog_fd_input::create_det_FD(int count, char* fd) {
    char sub_fd[30];
    char * subs = (char *)sub_fd;
    char tok[]=",";
    char * tmp = (char *)fd;

    do {
        int l = strcspn(tmp, tok);
        sprintf(subs, "%.*s", l, tmp);
        tmp += l+1;

        struct det_fd_node *temp;
        if(det_head[count]==NULL) {
            temp = (struct det_fd_node*)malloc(sizeof (struct det_fd_node));
            strcpy(temp->fd,sub_fd);
            temp->next = NULL;
            det_head[count] = temp;
        }
        else {
            temp->next = (struct det_fd_node*)malloc(sizeof (struct det_fd_node));
            temp = temp->next;
            strcpy(temp->fd,sub_fd);
            temp->next = NULL;
        }
    } while(tmp[-1]);
}

void Dialog_fd_input::create_dep_FD(int count, char* fd) {
    char sub_fd[30];
    char * subs = (char *)sub_fd;
    char tok[]=",";
    char * tmp = (char *)fd;

    do {
        int l = strcspn(tmp, tok);
        sprintf(subs, "%.*s", l, tmp);
        tmp += l+1;

        struct dep_fd_node *temp;
        if(dep_head[count]==NULL) {
            temp = (struct dep_fd_node*)malloc(sizeof (struct dep_fd_node));
            strcpy(temp->fd,sub_fd);
            temp->next = NULL;
            dep_head[count] = temp;
        }
        else {
            temp->next = (struct dep_fd_node*)malloc(sizeof (struct dep_fd_node));
            temp = temp->next;
            strcpy(temp->fd,sub_fd);
            temp->next = NULL;
        }
    } while(tmp[-1]);
}

void Dialog_fd_input::on_push_fd_Button_clicked()
{
    //int count=0;
    char det_fd[30],dep_fd[30];
    if(!(ui->lineEdit_1->text().isEmpty() || ui->lineEdit_7->text().isEmpty())){
        QString det_fd1 = ui->lineEdit_1->text();
        QString dep_fd1 = ui->lineEdit_7->text();
        strcpy(det_fd, det_fd1.toStdString().c_str());
        strcpy(dep_fd, dep_fd1.toStdString().c_str());
        create_det_FD(fd_count,det_fd);
        create_dep_FD(fd_count,dep_fd);
        fd_count++;
    }

    if(!(ui->lineEdit_2->text().isEmpty() || ui->lineEdit_8->text().isEmpty())){
        QString det_fd1 = ui->lineEdit_2->text();
        QString dep_fd1 = ui->lineEdit_8->text();
        strcpy(det_fd, det_fd1.toStdString().c_str());
        strcpy(dep_fd, dep_fd1.toStdString().c_str());
        create_det_FD(fd_count,det_fd);
        create_dep_FD(fd_count,dep_fd);
        fd_count++;
    }

    if(!(ui->lineEdit_3->text().isEmpty() || ui->lineEdit_9->text().isEmpty())){
        QString det_fd1 = ui->lineEdit_3->text();
        QString dep_fd1 = ui->lineEdit_9->text();
        strcpy(det_fd, det_fd1.toStdString().c_str());
        strcpy(dep_fd, dep_fd1.toStdString().c_str());
        create_det_FD(fd_count,det_fd);
        create_dep_FD(fd_count,dep_fd);
        fd_count++;
    }

    if(!(ui->lineEdit_4->text().isEmpty() || ui->lineEdit_10->text().isEmpty())){
        QString det_fd1 = ui->lineEdit_4->text();
        QString dep_fd1 = ui->lineEdit_10->text();
        strcpy(det_fd, det_fd1.toStdString().c_str());
        strcpy(dep_fd, dep_fd1.toStdString().c_str());
        create_det_FD(fd_count,det_fd);
        create_dep_FD(fd_count,dep_fd);
        fd_count++;
    }

    if(!(ui->lineEdit_5->text().isEmpty() || ui->lineEdit_11->text().isEmpty())){
        QString det_fd1 = ui->lineEdit_5->text();
        QString dep_fd1 = ui->lineEdit_11->text();
        strcpy(det_fd, det_fd1.toStdString().c_str());
        strcpy(dep_fd, dep_fd1.toStdString().c_str());
        create_det_FD(fd_count,det_fd);
        create_dep_FD(fd_count,dep_fd);
        fd_count++;
    }

    if(!(ui->lineEdit_6->text().isEmpty() || ui->lineEdit_12->text().isEmpty())){
        QString det_fd1 = ui->lineEdit_6->text();
        QString dep_fd1 = ui->lineEdit_12->text();
        strcpy(det_fd, det_fd1.toStdString().c_str());
        strcpy(dep_fd, dep_fd1.toStdString().c_str());
        create_det_FD(fd_count,det_fd);
        create_dep_FD(fd_count,dep_fd);
        fd_count++;
    }

    if(fd_count>0) {
        hide();
        dialog_fd_display = new Dialog_fd_display(this);
        dialog_fd_display->show();
    }
}
