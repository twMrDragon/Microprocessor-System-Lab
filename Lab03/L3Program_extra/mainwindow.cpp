#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    btns = {ui->pushButton,ui->pushButton_2,ui->pushButton_3,ui->pushButton_4};
    labels = {ui->label,ui->label_2,ui->label_3,ui->label_4};
    for(int i=0;i<labels.size();i++){
        labels[i]->setText("");
    }
    closeAllLED();
    connect(this->timer,SIGNAL(timeout()),this,SLOT(showNextLED()));

    for (int i = 0; i < btns.size(); i++) {
        connect(btns[i],&QPushButton::clicked,[this,i]{
            if(labels[i]->styleSheet() == ledStyleSheets[1]){
                updateLED(i,false);
                score+=20;
                updateScore();
            }else{
                timer->stop();
                ui->label_5->setText("Fail!");
                closeAllLED();
            }
        });
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeAllLED(){
    for(int i=0;i<labels.size();i++){
        updateLED(i,false);
    }
}

void MainWindow::updateLED(int index,int show){
    this->labels[index]->setStyleSheet(ledStyleSheets[show]);
    GPIO::gpio_export(ledsPin[index]);
    GPIO::gpio_set_dir(ledsPin[index],"out");
    GPIO::gpio_set_value(ledsPin[index],show);
}

void MainWindow::showNextLED(){
    if(labels[lastShowLEDIndex]->styleSheet() == ledStyleSheets[1]){
        timer->stop();
        ui->label_5->setText("Fail!");
        closeAllLED();
        return;
    }
    closeAllLED();
    int nextIndex = rand()%btns.size();
    while (nextIndex==lastShowLEDIndex) {
        nextIndex = rand()%btns.size();
    }
    updateLED(nextIndex,true);
    lastShowLEDIndex = nextIndex;
}

void MainWindow::on_pushButton_5_clicked()
{
    score=0;
    updateScore();
    timer->start(2000);
}

void MainWindow::updateScore(){
    ui->label_5->setText("Score:"+QString::number(score));
    if(score==MAX_SCORE){
        timer->stop();
        closeAllLED();
    }
}
