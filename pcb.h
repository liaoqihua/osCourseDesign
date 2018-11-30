#ifndef PCB_H
#define PCB_H
#include <string>
#include <iostream>
using namespace std;

class PCB
{
public:
    PCB();
    PCB(PCB &data);
    ~PCB(){}
    string getName(){return job_name;}
    float getATime(){return arrival_time;}
    float getNTime(){return need_time;}
    int getPri(){return pri;}
    PCB& create(string name,float at,float nt);
    ostream& printPCB(ostream &os)const;
private:
    string job_name; //进程名
    float arrival_time; //到达时间
    float need_time; //服务时间
    float wait_time; //等待时间
    float start_time; //开始时间
    float remain_time; //剩余时间
    float finish_time; //完成时间
    float turn_time; //周转时间
    float weight_turn_time; //带权周转时间
    int pri; //优先级
    int locked; //进程锁
};

#endif // PCB_H
