#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QLabel>
#include <QCheckBox>
#include <QTimer>

#define LED1 466
#define LED2 255
#define LED3 481
#define LED4 254

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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void shine_LED();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_progressBar_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    std::vector<QString> ledStyleSheets = {"image: url(:/led_off.png);","image: url(:/led_on.png);"};
    std::vector<QLabel*> labels;
    std::vector<QCheckBox*> checkboxes;
    QTimer *timer = new QTimer(this);
    int counter=0;
    std::vector<int> ledsPin = {LED1,LED2,LED3,LED4};

    void updateLED(int index,bool show);
};
#endif // MAINWINDOW_H
