#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gpio.h"

#define TIMER_INTERVAL 1000

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
    ui->pushButton_4->setVisible(false);
    ui->pushButton_5->setVisible(false);
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
    this->timer->start(TIMER_INTERVAL*ui->spinBox->text().toInt()/100);
}

void MainWindow::shine_LED(){
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
    // GPIO::gpio_export(ledsPin[index]);
    // GPIO::gpio_set_dir(ledsPin[index],"out");
    // GPIO::gpio_set_value(ledsPin[index],show);
}


void MainWindow::on_pushButton_3_clicked()
{
    for (int i = 0; i < this->checkboxes.size(); ++i) {
        updateLED(i,false);
    }
    this->timer->stop();
    counter=0;
}


void MainWindow::on_pushButton_5_clicked()
{
    ui->spinBox->stepUp();
}


void MainWindow::on_pushButton_4_clicked()
{
    ui->spinBox->stepDown();
}


void MainWindow::on_progressBar_valueChanged(int value)
{
    timer->setInterval(TIMER_INTERVAL*ui->spinBox->text().toInt()/100);
}

