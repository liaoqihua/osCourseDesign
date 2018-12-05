#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include <QMainWindow>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QButtonGroup>
#include <QRadioButton>
#include <QDebug>
#include <QFileDialog>
#include "promanager.h"
#include <iostream>
using std::cout;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void initButtonGroup();
    void initwin13();
    ~MainWindow();
public slots:
    void onchickButtonBroup(QAbstractButton * button);
    void handleAddButton();
    void loadButtonHandle();
    void openfileButton();
    void displayPro();
    void runPro();
private:
    QWidget *win;
    QWidget *win1;
    QWidget *win2;
    QWidget *win11;
    QWidget *win12;
    QWidget *win13;
    QTextEdit *win2Text;
    QPushButton *openfile;
    QPushButton *runButton;
    QPushButton *displayButton;
    QPushButton *loadButton;
    QLineEdit *proname;
    QLineEdit *arrivetime;
    QLineEdit *needtime;
    QLineEdit *addPri;
    QLabel *addPriLabel;
    QPushButton *addbutton;
    QButtonGroup *alChoose;
    QString alname;
    QString inputName;
    QString filename;
    int arrTime;
    int neeTime;
    ProManager pro;
};

#endif // MAINWINDOW_H
