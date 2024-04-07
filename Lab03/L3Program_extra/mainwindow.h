#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define MAX_SCORE 100
#define LED1 466
#define LED2 255
#define LED3 481
#define LED4 254

#include <QMainWindow>
#include <vector>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include "gpio.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_5_clicked();
    void showNextLED();

private:
    Ui::MainWindow *ui;
    int lastShowLEDIndex = 0;
    int score = 0;
    QTimer *timer = new QTimer(this);
    std::vector<QPushButton*> btns;
    std::vector<QLabel*> labels;
    std::vector<QString> ledStyleSheets = {"image: url(:/led_off.png);","image: url(:/led_on.png);"};
    std::vector<int> ledsPin = {LED1,LED2,LED3,LED4};
    void updateLED(int index,int show);
    void closeAllLED();
    void updateScore();
};
#endif // MAINWINDOW_H
