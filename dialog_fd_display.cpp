#include "dialog_fd_display.h"
#include "ui_dialog_fd_display.h"
#include "dialog_fd_input.h"

#include <QProcess>

char det_edge[30][30],dep_edge[30][30];
int edge_count,reflex_edge_count=0,dg_generated_flag=0;

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
    static char fds[50]="";
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
    static char fds[100]="";
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

int Dialog_fd_display::create_dg_edges(char det_edge[][30],char dep_edge[][30],char reflex_det_edge[][30],char reflex_dep_edge[][30],int *n) {
    char sub_reflex_edge[30],sub_det_fd[10][30];
    char tok[]=",";
    char * poi_sub_reflex_edge=(char *)sub_reflex_edge;
    int i,j=0,k=0,sub_det_fd_count=0,sub_det_fd_count2=0;
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

        //store reflexive edges
        char * tmp=(char *)det_edge[j];
        do {
            int l=strcspn(tmp,tok);
            sprintf(poi_sub_reflex_edge,"%.*s",l,tmp);
            //store each sub determinant fd for reflexivity rule calculations
            strcpy(sub_det_fd[sub_det_fd_count++],sub_reflex_edge);
            if(strcmp(det_edge[j],sub_reflex_edge)!=0) {
                strcpy(reflex_det_edge[(*n)++],det_edge[j]);
                strcpy(reflex_dep_edge[*n-1],sub_reflex_edge);
                tmp+=l+1;
            }
        }while(tmp[-1]);

        //check for multi level reflexivity rule dependencies
        if(sub_det_fd_count>2) {
            unsigned int pow_set_size=pow(2,sub_det_fd_count);
            int pow_counter,a,b,flag=0;
            char sub_pow_set[30];

            //Run from 000..0 to 111..1(finding power set)
            for(pow_counter=0;pow_counter<pow_set_size;pow_counter++) {
                memset(sub_pow_set,0,sizeof(sub_pow_set));
                sub_det_fd_count2=0;
                for(a=0;a<sub_det_fd_count;a++) {
                    //check if bth bit in the pow_counter is set
                    //if set then print bth fd from sub_det_fd[]
                    if(pow_counter & (1<<a)) {
                        strcat(sub_pow_set,sub_det_fd[a]);
                        strcat(sub_pow_set,",");
                        sub_det_fd_count2++;
                    }
                }
                sub_pow_set[strlen(sub_pow_set)-1]='\0';

                //eliminate single element fd in sub_pow_set
                if(sub_det_fd_count2>1 && strcmp(det_edge[j],sub_pow_set)!=0) {
                    for(b=0;b<fd_count;b++) {
                        if(strcmp(det_k[b],sub_pow_set)==0) {
                            flag=1;
                            break;
                        }
                    }
                    //sub reflexive edge present which is a determinant key
                    if(flag==1) {
                        strcpy(reflex_det_edge[(*n)++],det_edge[j]);
                        strcpy(reflex_dep_edge[*n-1],sub_pow_set);
                    }
                    flag=0;
                }
            }
        }
        sub_det_fd_count=0;

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

void Dialog_fd_display::writeFile(char det_edge[][30],char dep_edge[][30],char reflex_det_edge[][30],char reflex_dep_edge[][30],int m,int n) {
    FILE *dg_file=fopen("dg_edges", "w");
    int results,i;

    //write dependency edgeset
    putc('[',dg_file);
    for(i=0;i<m;i++) {
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
    putc('\n',dg_file);
    //write reflexivity rule dependencies
    putc('[',dg_file);
    for(i=0;i<n;i++) {
        putc('(',dg_file);
        putc('\'',dg_file);
        results=fputs(reflex_det_edge[i],dg_file);
        putc('\'',dg_file);
        putc(',',dg_file);
        putc('\'',dg_file);
        results=fputs(reflex_dep_edge[i],dg_file);
        putc('\'',dg_file);
        putc(')',dg_file);
        putc(',',dg_file);
    }
    putc(']',dg_file);
    fclose(dg_file);
}

void Dialog_fd_display::on_graph_Button_clicked()
{
    char reflex_det_edge[30][30],reflex_dep_edge[30][30];

    if(dg_generated_flag==0){
        edge_count=create_dg_edges(det_edge,dep_edge,reflex_det_edge,reflex_dep_edge,&reflex_edge_count);
        writeFile(det_edge,dep_edge,reflex_det_edge,reflex_dep_edge,edge_count,reflex_edge_count);
        dg_generated_flag=1;
    }

    QProcess process;
    process.setProgram("graphPY.py");
    process.start("python ../ADN/graphPY.py");
    process.waitForFinished(-1);
}

void Dialog_fd_display::on_nextButton_clicked()
{
    char reflex_det_edge[30][30],reflex_dep_edge[30][30];

    if(dg_generated_flag==0) {
        edge_count=create_dg_edges(det_edge,dep_edge,reflex_det_edge,reflex_dep_edge,&reflex_edge_count);
        writeFile(det_edge,dep_edge,reflex_det_edge,reflex_dep_edge,edge_count,reflex_edge_count);
        dg_generated_flag=1;
    }
    hide();
    dialog_dm_view=new Dialog_DM_view(this);
    dialog_dm_view->show();
}
