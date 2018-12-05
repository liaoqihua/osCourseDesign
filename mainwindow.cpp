#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    alname = "FCFS";
    this->resize(800,450);
    this->setStyleSheet("*{margin:0px;"
                        "padding:0px;}");
    win = new QWidget();
    this->setCentralWidget(win);
    QVBoxLayout *winLayout = new QVBoxLayout();
    win->setLayout(winLayout);

    //添加上部
    win1 = new QWidget();
    winLayout->addWidget(win1);
    win1->setStyleSheet("QWidget{border:1px solid #cccccc;"
                        "max-height:200px;"
                        "border-radius:10px;}");
    win1->setLayout(new QHBoxLayout());
    win11 = new QWidget();
    QGridLayout *win11layout = new QGridLayout();
    win11->setLayout(win11layout);
    win13 = new QWidget();
    win1->layout()->addWidget(win13);
    win13->setStyleSheet("min-width:100px;");
    initwin13();
    win12 = new QWidget();
    win12->setLayout(new QVBoxLayout());
    win1->layout()->addWidget(win11);
    win1->layout()->addWidget(win12);
    proname = new QLineEdit();
    arrivetime = new QLineEdit();
    needtime = new QLineEdit();
    addPri = new QLineEdit();
    addbutton = new QPushButton(QString::fromLocal8Bit("添加"));
    win11layout->addWidget(new QLabel(QString::fromLocal8Bit("进程名:")),0,0,nullptr);
    win11layout->addWidget(proname,0,1,nullptr);
    win11layout->addWidget(new QLabel(QString::fromLocal8Bit("到达时间:")),1,0,nullptr);
    win11layout->addWidget(arrivetime,1,1,nullptr);
    win11layout->addWidget(new QLabel(QString::fromLocal8Bit("服务时间:")),2,0,nullptr);
    win11layout->addWidget(needtime,2,1,nullptr);
    addPriLabel = new QLabel(QString::fromLocal8Bit("优先级:"));
    win11layout->addWidget(addPriLabel,3,0,nullptr);
    win11layout->addWidget(addPri,3,1,nullptr);
    addPriLabel->hide();
    addPri->hide();
    win11layout->addWidget(addbutton,4,0,1,2,nullptr);
    addbutton->setFixedWidth(100);

    initButtonGroup();
    connect(addbutton,SIGNAL(clicked()),this,SLOT(handleAddButton()));

    //添加下部
    win2 = new QWidget();
    winLayout->addWidget(win2);
    win2->setStyleSheet("QWidget{border:1px solid #cccccc;"
                        "max-height:250px;"
                        "border-radius:10px;}");
    win2->setLayout(new QHBoxLayout());
    win2Text = new QTextEdit();
    win2Text->setStyleSheet("QTextEdit{"
                            "height:230px;"
                            "width:100%;"
                            "border-radius:3px;}");
    win2->layout()->addWidget(win2Text);
}

MainWindow::~MainWindow()
{

}

void MainWindow::initButtonGroup()
{
    alChoose = new QButtonGroup();
    QString str[] = {"FCFS","SJF","SRTF","RR","PSA","HRRN","MFQ"};
    QRadioButton *radio[7];
    for(unsigned i=0;i<7;++i){
        radio[i] = new QRadioButton(str[i]);
        alChoose->addButton(radio[i]);
        win12->layout()->addWidget(radio[i]);
    }
    radio[0]->setChecked(true);
    connect(alChoose,SIGNAL(buttonClicked(QAbstractButton *)),this,SLOT(onchickButtonBroup(QAbstractButton *)));
}

void MainWindow::onchickButtonBroup(QAbstractButton * button)
{
    alname = button->text();
    if(alname == "PSA" || alname == "HRRN"){
        win2Text->append(QString::fromLocal8Bit("请输入优先级(提示:")+QString("%1").arg(pro.getProlength())+QString::fromLocal8Bit("个)"));
        addPriLabel->show();
        addPri->show();
    }else{
        addPriLabel->hide();
        addPri->hide();
    }
}

void MainWindow::handleAddButton()
{
    inputName = proname->text();
    arrTime = arrivetime->text().toInt();
    neeTime = needtime->text().toInt();
    string line;
    stringstream ss(line);
    ss << "进程名:" << inputName.toStdString() << "\n到达时间:" << arrTime << "\n服务时间:" << neeTime << "\n";
    win2Text->append(QString::fromLocal8Bit(ss.str().c_str()));
    pro.addPro(inputName.toStdString(), arrTime, neeTime);
}

void MainWindow::initwin13()
{
    QVBoxLayout *vbox = new QVBoxLayout();
    win13->setLayout(vbox);

    QLabel *l1 = new QLabel(QString::fromLocal8Bit("手动输入-->"));
    QLabel *l2 = new QLabel(QString::fromLocal8Bit("文件输入↓"));
    openfile = new QPushButton(QString::fromLocal8Bit("打开文件"));
    loadButton = new QPushButton(QString::fromLocal8Bit("加载文件"));
    displayButton = new QPushButton(QString::fromLocal8Bit("显示进程"));
    runButton = new QPushButton(QString::fromLocal8Bit("运行进程"));
    win13->layout()->addWidget(l1);
    win13->layout()->addWidget(l2);
    win13->layout()->addWidget(openfile);
    win13->layout()->addWidget(loadButton);
    win13->layout()->addWidget(displayButton);
    win13->layout()->addWidget(runButton);
    connect(openfile,SIGNAL(clicked()),this,SLOT(openfileButton()));
    connect(loadButton,SIGNAL(clicked()),this,SLOT(loadButtonHandle()));
    connect(displayButton,SIGNAL(clicked()),this,SLOT(displayPro()));
    connect(runButton,SIGNAL(clicked()),this,SLOT(runPro()));
}

void MainWindow::openfileButton()
{
    filename = QFileDialog::getOpenFileName(nullptr,"打开文件",".","*.txt");
    win2Text->append(QString::fromLocal8Bit("选择文件：")+filename+"\n");
    qDebug() << filename;
}

void MainWindow::loadButtonHandle()
{
    if(filename == ""){
        win2Text->clear();
        win2Text->append(QString::fromLocal8Bit("请选择文件夹\n"));
    }else{
        pro.readfile(filename.toStdString());
    }
}

void MainWindow::displayPro()
{
    pro.reset();
    pro.print(win2Text);
}

void MainWindow::runPro()
{
    if(alname.compare("FCFS") == 0){
        pro.reset();
        pro.FCFS();
        win2Text->clear();
        win2Text->append(QString::fromLocal8Bit(pro.getOutput().c_str()));
    }else if(alname.compare("SJF") == 0){
        pro.reset();
        pro.SJF();
        win2Text->clear();
        win2Text->append(QString::fromLocal8Bit(pro.getOutput().c_str()));
    }else if(alname.compare("SRTF") == 0){
        pro.reset();
        pro.SRTF();
        win2Text->clear();
        win2Text->append(QString::fromLocal8Bit(pro.getOutput().c_str()));
    }else if(alname.compare("RR") == 0){
        pro.reset();
        pro.RR();
        win2Text->clear();
        win2Text->append(QString::fromLocal8Bit(pro.getOutput().c_str()));
    }else if(alname.compare("PSA") == 0){
        pro.reset();
        pro.PSA(addPri->text().toStdString());
        win2Text->clear();
        win2Text->append(QString::fromLocal8Bit(pro.getOutput().c_str()));
    }else if(alname.compare("HRRN") == 0){
        pro.reset();
        pro.HRRN(addPri->text().toStdString());
        win2Text->clear();
        win2Text->append(QString::fromLocal8Bit(pro.getOutput().c_str()));
    }else if(alname.compare("MFQ") == 0){
        pro.reset();
        pro.MFQ();
        win2Text->clear();
        win2Text->append(QString::fromLocal8Bit(pro.getOutput().c_str()));
    }
}
