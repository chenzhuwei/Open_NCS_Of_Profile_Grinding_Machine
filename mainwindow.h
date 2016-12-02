﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QButtonGroup>
#include <QPalette>
#include <QAxObject>
#include <QLabel>
#include <QDir>
#include <QThread>
#include "trioactivex.h"
#include "thread_ccd.h"
#include "thread_trio.h"
#define IMAGE_SIZE 2448*2550

namespace Ui {
class MainWindow;
}

enum BUTTON_GROUP_TYPE{MAIN,SUB,SUB2,ALL_SUB,ALL};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPushButton *mainButton[6],*helpButton,*subButton[5],*sub2Button[8];
    QStackedWidget *mainStack,*editStack;
    QButtonGroup *ButtonGroup_main,*ButtonGroup_sub,*ButtonGroup_sub2;
    QPalette Palette_Unpressed,Palette_Pressed,Palette_Unconnected,Palette_Connected;
    QLabel *Label_Connection_Status;
    int current_ButtonID_main,current_ButtonID_sub,current_ButtonID_sub2;
    QDir dir_of_txt;
    bool Connection_Status_of_Trio;
    double Axis_Paras[5];

    void qSleep(int ms);
    void button_pressed(QPushButton *button);
    void button_unpressed(QPushButton *button);
    void clear_button_text(BUTTON_GROUP_TYPE);

//    TrioPCLib::TrioPC *trio;
    thread_CCD *ccd;
    thread_Trio *trio_MC664;
    QThread *THREAD_CCD,*THREAD_TRIO;

private slots:
    void errors_handled(int);
    void errors_of_trio_handled(int, QString, QString, QString);

    void pressed_mainButtonGroup(int i);
    void pressed_subButtonGroup(int i);
    void pressed_sub2ButtonGroup(int i);

    void txtfile_new_built();
    void txtfile_readin();
    void txtfile_save();
    void txtfile_undo();
    void txtfile_grammar_check();
    void txtfile_send_to_trio();

    void cB_Txt_Dir_Content(QString);
    void cB_current_index_changed(QString);

    void pB_Connection();

    //Receive from multi-threads
    void receive_Trio_axis_paras(double*);

signals:
    void cB_Txt_Changed(QString);
    void status_Changed(int);
    void errors_in_runtime(int);

    //for ccd thread
    void initialize_ccd();
    void capture_picture(char*);

    //for trio thread
    void call_Trio_connect(bool*);
    void call_Trio_send_txt(bool*,const QString,const QString);
    void call_Trio_run_program(bool*,QString);
    void call_Trio_return_axis_paras(bool*,double*);
};

#endif // MAINWINDOW_H
