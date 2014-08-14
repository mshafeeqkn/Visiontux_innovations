#include "mainwindow.h"
#include "options.h"
#include "help.h"

#include "ui_mainwindow.h"
#include <QTableWidget>
#include <stdio.h>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <string.h>
#include <QDebug>

int player,winner=1,temp=0;
int col_total,row_total;
int tab_wid,tab_hei;
int matrix[16][16]={};
int flag=0;
char path[50],path2[100]={};
int tsize;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    FILE *p = popen("pwd","r");
    temp=fscanf(p,"%s",path);
    pclose(p);
	temp=0;



    /*=====================FILE Menu===================*/
    QMenu *menuFile = new QMenu("&File");

    /*============New game=================*/
    QAction *actionNewGame;
    actionNewGame = new QAction("&New Game", this);
    actionNewGame->setShortcut(QKeySequence::New);
    menuFile->addAction(actionNewGame);
    menuBar()->addMenu(menuFile);
    connect(actionNewGame, SIGNAL(triggered()), this, SLOT(Newgame()));
    /*=====================Options======================*/
    QAction *actionOptions;
    actionOptions = new QAction("&Options", this);
    //actionOptions->setShortcut(QKeySequence::New);
    menuFile->addAction(actionOptions);
    menuBar()->addMenu(menuFile);
    connect(actionOptions, SIGNAL(triggered()), this, SLOT(options()));

    QAction *actionQuit;
    actionQuit = new QAction("&Quit", this);
    actionQuit->setShortcut(QKeySequence::Quit);
    menuFile->addAction(actionQuit);
    menuBar()->addMenu(menuFile);
    connect(actionQuit, SIGNAL(triggered()), this, SLOT(quit()));


    QMenu *menuHelp = new QMenu("&Help");

    QAction *actionHowto;
    actionHowto=new QAction("&Howto",this);
    menuHelp->addAction(actionHowto);
    menuBar()->addMenu(menuHelp);
    connect(actionHowto,SIGNAL(triggered()),this,SLOT(how()));




    strcat(path2,"background-image: url(");
    strcat(path2,path);
    strcat(path2,"/true1.png)");
    QString path1 = path2;
    ui->widget1->setStyleSheet(path1);
    strcpy(path2,"");
    strcat(path2,"background-image: url(");
    strcat(path2,path);
    strcat(path2,"/false1.png)");
    path1 = path2;
    ui->widget2->setStyleSheet(path1);
    strcpy(path2,"");
    strcat(path2,"background-image: url(");
    strcat(path2,path);
    strcat(path2,"/true1.png)");
    path1 = path2;
    ui->widget3->setStyleSheet(path1);
    strcpy(path2,"");
    strcat(path2,"background-image: url(");
    strcat(path2,path);
    strcat(path2,"/false1.png)");
    path1 = path2;
    ui->widget4->setStyleSheet(path1);



    ui->comboBox1->setCurrentIndex(0);
    ui->comboBox2->setCurrentIndex(1);

    restart(8);
}


void MainWindow::restart(int count){

    col_total=count;
    row_total=count;
    tab_wid=400/col_total;
    tab_hei=400/row_total;
    tab_wid*=col_total;
    tab_hei*=row_total;

    player=ui->comboBox1->currentIndex()+2;

    if(player==2){
        ui->widget4->hide();
        ui->widget3->show();
    }
    else if (player==3){
        ui->widget4->show();
        ui->widget3->hide();
    }


    ui->tableWidget->setRowCount(row_total);
    ui->tableWidget->setColumnCount(col_total);
    ui->tableWidget->setMaximumWidth(tab_wid+2);
    ui->tableWidget->setMaximumHeight(tab_hei+2);
    ui->tableWidget->setIconSize(QSize(tab_wid/col_total-5, tab_hei/row_total-5));



    for(int i=0;i<col_total;i++)
        ui->tableWidget->setColumnWidth(i,tab_wid/col_total);
    for(int i=0;i<row_total;i++)
        ui->tableWidget->setRowHeight(i,tab_hei/row_total);

    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->horizontalHeader()->hide();


    ui->comboBox1->setEnabled(true);

    for(int i=0;i<row_total;i++){
        for(int j=0;j<col_total;j++){
            matrix[i][j]=0;
            ui->tableWidget->setItem(i,j,new QTableWidgetItem(""));
        }
    }
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Newgame(){
    QMessageBox msgBox;
    ui->comboBox1->setEnabled(true);
    msgBox.setWindowTitle("test");
    msgBox.setText("Do you want to take new game??");
    msgBox.setStandardButtons(0);
    msgBox.addButton(QMessageBox::No);
    msgBox.addButton(QMessageBox::Yes);
    if(msgBox.exec()==QMessageBox::Yes){
        player=3;
        restart(tsize);
    }
}

void MainWindow::options(){
    ui->tableWidget->setDisabled(true);
    Options *opt = new Options;
    opt->exec();
    restart(tsize);
    ui->tableWidget->setEnabled(true);
}


void MainWindow::quit(){
    QMessageBox msgBox;
    msgBox.setWindowTitle("test");
    msgBox.setText("Do you want quit?");
    msgBox.setStandardButtons(0);
    msgBox.addButton(QMessageBox::No);
    msgBox.addButton(QMessageBox::Yes);
    if(msgBox.exec()==QMessageBox::Yes){
        this->close();
    }
}

void MainWindow::how(){
    Help *hel = new Help;
    hel->exec();
}


void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    char out_string[25];
    ui->comboBox1->setDisabled(true);


    if(matrix[row][column]==0){

        if(player==2){
            ui->widget4->show();
            ui->widget3->hide();
        }
        else if (player==3){
            ui->widget4->hide();
            ui->widget3->show();
        }

        matrix[row][column]=player;
        //sprintf(out_string,"%d,%d->%d",row,column,matrix[row][column]);
        QMessageBox msgBox;
        winner=checkwinner(player);
        QTableWidgetItem *item = new QTableWidgetItem;
        if(player==3){
            strcpy(path2,path);
            strcat(path2,"/false.png");
            item->setIcon(QIcon(path2));
        }
        else if(player==2){
            strcpy(path2,path);
            strcat(path2,"/true.png");
            item->setIcon(QIcon(path2));
        }
        ui->tableWidget->setItem(row, column, item);

        if(winner==1){
            if(flag==1)
                player^=1;
            sprintf(out_string,"Player %d Won the game",player-1);
            msgBox.setWindowTitle("Result");
            msgBox.setText(out_string);
            msgBox.exec();
            msgBox.setWindowTitle(" ");
            msgBox.setText("Do you want to play new game?");
            msgBox.setStandardButtons(0);
            msgBox.addButton(QMessageBox::No);
            msgBox.addButton(QMessageBox::Yes);
            if(msgBox.exec()==QMessageBox::Yes){
                restart(8);
                if(ui->widget4->isHidden()){
                    ui->widget4->show();
                    ui->widget3->hide();
                }else{
                    ui->widget4->hide();
                    ui->widget3->show();
                }
            }
        }
        player^=1;
    }
}






int MainWindow::checkwinner(int player){
    if(testRow(player)||testCol(player)||rtdwn(player)||ltdwn(player))
        return 1;
    else
        return 0;
}


bool MainWindow::testRow(int player){
    int count=0,row=0,col=0;
    for(row=0;row<row_total;row++){
        count=0;
        for(col=0;col<col_total;col++){
            if(matrix[row][col]==player){
                count++;
                if(count>=5)
                    return true;
            }
            else
                count=0;
        }
    }
    return false;
}


bool MainWindow::testCol(int player){
    int count=0,row=0,col=0;
    for(col=0;col<col_total;col++){
        count=0;
        for(row=0;row<row_total;row++){
            if(matrix[row][col]==player){
                count++;
                if(count>=5)
                    return true;
            }
            else
                count=0;
        }
    }
    return false;
}

bool MainWindow::rtdwn(int player){
    int count=0,row=0,col=0,i;
    for(row=0;row<row_total-4;row++){
        count=0;
        for(col=0;col<col_total-4;col++){
            for(i=0;i<6;i++){
                if(matrix[row+i][col+i]==player){
                    count++;
                    if(count>=5)
                        return true;
                }
                else
                    count=0;
            }
        }
    }
    return false;
}

bool MainWindow::ltdwn(int player){
    int count=0,row=0,col=0,i;
    for(row=0;row<row_total;row++){
        count=0;
        for(col=0;col<col_total;col++){
            for(i=0;i<6;i++){
                if(matrix[row-i][col+i]==player){
                    count++;
                    if(count>=5)
                        return true;
                }
                else
                    count=0;
            }
        }
    }
    return false;
}


void MainWindow::on_comboBox1_currentIndexChanged(int index)
{
    if(ui->comboBox1->currentIndex()==0){
        ui->comboBox2->setCurrentIndex(1);
        player=3;
        ui->widget4->hide();
        ui->widget3->show();
        flag=0;
    }
    else{
        flag=1;
        ui->comboBox2->setCurrentIndex(0);
        player=2;
        ui->widget4->show();
        ui->widget3->hide();
    }
    restart(8);
}
