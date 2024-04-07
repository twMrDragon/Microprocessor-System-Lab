#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->checkboxes = {ui->checkBox,ui->checkBox_2,ui->checkBox_3,ui->checkBox_4};
    this->labels = {ui->label,ui->label_2,ui->label_3,ui->label_4};
    for (int i = 0; i < labels.size(); ++i) {
        labels[i]->setText("");
        updateLED(i,false);
    }
    connect(this->timer,SIGNAL(timeout()),this,SLOT(shine_LED()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    for (int i = 0; i < this->checkboxes.size(); ++i) {
        updateLED(i,this->checkboxes[i]->isChecked()?1:0);
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    this->counter = 0;
    for (int i = 0; i < this->checkboxes.size(); ++i) {
        updateLED(i,false);
    }
    this->timer->start(1000);
}

void MainWindow::shine_LED(){
    if(this->counter==ui->lineEdit->text().toInt()*2){
        for (int i = 0; i < this->checkboxes.size(); ++i) {
            updateLED(i,false);
        }
        this->timer->stop();
        return;
    }
    int flag = counter%2==0;
    for(int i=0;i<this->labels.size();i++){
        if(i==labels.size()/2)
            flag=!flag;
        updateLED(i,flag);
    }
    counter++;
}

void MainWindow::updateLED(int index,bool show){
    this->checkboxes[index]->setChecked(show);
    this->labels[index]->setStyleSheet(ledStyleSheets[show]);
}

