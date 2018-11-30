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
    string job_name; //������
    float arrival_time; //����ʱ��
    float need_time; //����ʱ��
    float wait_time; //�ȴ�ʱ��
    float start_time; //��ʼʱ��
    float remain_time; //ʣ��ʱ��
    float finish_time; //���ʱ��
    float turn_time; //��תʱ��
    float weight_turn_time; //��Ȩ��תʱ��
    int pri; //���ȼ�
    int locked; //������
};

#endif // PCB_H
