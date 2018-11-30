#ifndef PCB_H
#define PCB_H
#include <string>
#include <iostream>
using namespace std;

struct PCB
{
    string job_name;
    float arrival_time;
    float need_time;
    float wait_time;
    float start_time;
    float finish_time;
    float turn_time;
    float weight_turn_time;
    int pri;
    ostream& printPCB(ostream &os)const;
    PCB();
};

#endif // PCB_H
