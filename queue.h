#ifndef QUEUE_H
#define QUEUE_H
#include "pcb.h"
struct node{
    PCB data;
    node *next;
    node():data(),next(nullptr){}
    node(PCB &nd):data(nd),next(nullptr){}
};

class Queue
{
public:
    Queue();
private:
    node *head;
};

#endif // QUEUE_H
