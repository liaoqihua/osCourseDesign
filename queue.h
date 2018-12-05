#ifndef QUEUE_H
#define QUEUE_H
#include "pcb.h"
#include <iostream>
using std::cout;

struct node{
    PCB *pcb;
    node *pre;
    node *next;
    node():pcb(nullptr),pre(nullptr),next(nullptr){}
    node(PCB *p):pre(nullptr),next(nullptr){pcb = p;}
};

class Queue
{
public:
    Queue();
    void push_back(PCB *p);
    PCB* pop();
    bool empty(){return length==0;}
    string print();
    void clear();
    double calcTurn();
    double calcWTurn();
private:
    node *head;
    node *tail;
    int length;
};

#endif // QUEUE_H
