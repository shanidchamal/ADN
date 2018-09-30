#include "dialog_fd_display.h"
#include "ui_dialog_fd_display.h"
#include "dialog_fd_input.h"

#include <QProcess>

Dialog_fd_display::Dialog_fd_display(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_fd_display)
{
    ui->setupUi(this);

    ui->label_9->setText(print_det_fd(0));

    ui->label_22->setText(print_dep_fd(0));

    ui->label_10->setText(print_det_fd(1));

    ui->label_23->setText(print_dep_fd(1));

    ui->label_11->setText(print_det_fd(2));

    ui->label_24->setText(print_dep_fd(2));

    ui->label_12->setText(print_det_fd(3));

    ui->label_25->setText(print_dep_fd(3));

    ui->label_13->setText(print_det_fd(4));

    ui->label_26->setText(print_dep_fd(4));

    ui->label_14->setText(print_det_fd(5));

    ui->label_27->setText(print_dep_fd(5));

}

Dialog_fd_display::~Dialog_fd_display()
{
    delete ui;
}

char* Dialog_fd_display::print_det_fd(int count) {
    static char fds[30]="";
    memset(fds,0,sizeof(fds));
    struct det_fd_node *temp;
    temp=det_head[count];

    while(temp!=NULL)
    {
        strcat(fds,temp->fd);
        strcat(fds,",");
        temp=temp->next;
    }
    fds[strlen(fds)-1]='\0';
    return fds;
}

char* Dialog_fd_display::print_dep_fd(int count) {
    static char fds[30]="";
    memset(fds,0,sizeof(fds));
    struct dep_fd_node *temp;
    temp=dep_head[count];

    while(temp!=NULL)
    {
        strcat(fds,temp->fd);
        strcat(fds,",");
        temp=temp->next;
    }
    fds[strlen(fds)-1]='\0';
    return fds;
}

int Dialog_fd_display::create_dg_edges(char det_edge[][30],char dep_edge[][30]) {
    int i,j=0,k=0;
    for(i=0;i<fd_count;i++) {
        struct det_fd_node *temp;
        temp=det_head[i];
        memset(det_edge[j],0,sizeof(det_edge[j]));
        while(temp!=NULL) {
            strcat(det_edge[j],temp->fd);
            strcat(det_edge[j],",");
            temp=temp->next;
        }
        det_edge[j][strlen(det_edge[j])-1]='\0';

        struct dep_fd_node *temp2;
        temp2=dep_head[i];
        while(temp2!=NULL) {
            memset(dep_edge[k],0,sizeof(dep_edge[k]));
            strcpy(dep_edge[k],temp2->fd);
            if(j<k) {
                memset(det_edge[j+1],0,sizeof(det_edge[j+1]));
                strcpy(det_edge[j+1],det_edge[j]);
                j++;
            }
            k++;
            temp2=temp2->next;
        }
        j++;
    }
    return k;
}

void Dialog_fd_display::writeFile(char det_edge[][30],char dep_edge[][30],int n) {
    FILE *dg_file=fopen("dg_edges", "w");
    int results,i;
    putc('[',dg_file);
    for(i=0;i<n;i++) {
        putc('(',dg_file);
        putc('\'',dg_file);
        results=fputs(det_edge[i],dg_file);
        putc('\'',dg_file);
        putc(',',dg_file);
        putc('\'',dg_file);
        results=fputs(dep_edge[i],dg_file);
        putc('\'',dg_file);
        putc(')',dg_file);
        putc(',',dg_file);
    }
    putc(']',dg_file);
    fclose(dg_file);
}

void Dialog_fd_display::on_graph_Button_clicked()
{
    char det_edge[30][30],dep_edge[30][30];
    int size;

    size=create_dg_edges(det_edge,dep_edge);
    writeFile(det_edge,dep_edge,size);

    QProcess process;
    process.setProgram("graphPY.py");
    process.start("python /home/shanid/QtWorkSpace/ADN/graphPY.py");
    process.waitForFinished(-1);
}
