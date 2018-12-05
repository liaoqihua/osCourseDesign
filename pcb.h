#ifndef PCB_H
#define PCB_H
#include <string>
#include <iostream>
#include <sstream>
using std::string;
using std::ostream;
using std::endl;
using std::cout;
using std::stringstream;
#include <QTextEdit>



struct PCB
{
    string name;
    char status;
    int arrive_time;
    int need_time;
    int start_time;
    int finish_time;
    int wait_time;
    int remain_time;
    int turn_time;
    double w_turn_time;
    int pri;
    double priD;
    PCB();
    PCB(string name,int at,int nt);
    void printPCB(ostream &os);
    void printPCBQt(QTextEdit *edit);
};

#endif // PCB_H
