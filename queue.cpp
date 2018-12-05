#include "queue.h"

Queue::Queue():length(0)
{
    head = new node();
    tail = head;
}

void Queue::push_back(PCB *p)
{
    node *n = new node(p);
    tail->next = n;
    tail = n;
    length++;
}

PCB* Queue::pop()
{
    if(length == 0){
        return nullptr;
    }
    node *n = head->next;
    head->next = n->next;
    length--;
    if(n == tail){
        tail = head;
    }
    PCB *p = n->pcb;
    delete  n;
    return p;
}

string Queue::print()
{
    string line;
    stringstream ss(line);
    ss << "������\t����ʱ��\t����ʱ��\t��ʼʱ��\t����ʱ��\t�ȴ�ʱ��\tʣ��ʱ��\t��תʱ��\t��Ȩ��תʱ��" << endl;
    node *top = head->next;
    while(top){
        top->pcb->printPCB(ss);
        top = top->next;
    }
    ss << "ƽ����תʱ��:" << calcTurn() << endl;
    ss << "ƽ����Ȩ��תʱ��:" << calcWTurn() << endl;
    return ss.str();
}

void Queue::clear()
{
    if(length != 0){
        node *n = head->next;
        node *temp = nullptr;
        while(n){
            temp = n;
            n = n->next;
            delete temp;
        }
        length = 0;
        head->next = nullptr;
        tail = head;
    }
}

double Queue::calcTurn()
{
    node *top = head->next;
    int ttsum = 0;
    int i=0;
    while(top){
        ttsum += top->pcb->turn_time;
        top = top->next;
        i++;
    }
    return 1.0*ttsum/i;
}

double Queue::calcWTurn()
{
    node *top = head->next;
    double ttsum = 0;
    int i=0;
    while(top){
        ttsum += top->pcb->w_turn_time;
        top = top->next;
        i++;
    }
    return ttsum/i;
}
