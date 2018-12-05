#ifndef PROMANAGER_H
#define PROMANAGER_H
#include "pcb.h"
#include "queue.h"
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>
using std::vector;
using std::stringstream;
using std::ifstream;
using std::cout;
using std::cin;
using std::getline;
using std::sort;
using std::pow;
#include <QTextEdit>


class ProManager
{
public:
    ProManager();
    void readfile(string filename);
    void reset();
    void runFCFS(PCB *p);
    void FCFS();
    void SJF();
    unsigned runSRTF(PCB *p,unsigned index);
    void SRTF();
    unsigned runRR(PCB *p,int ti,unsigned index);
    void RR();
    unsigned runPSA(PCB *p,unsigned index);
    void PSA(string input);
    void HRRN(string input);
    unsigned runMFQ(PCB *p,int ti,unsigned index);
    void MFQ();
    void print(QTextEdit *edit);
    string getOutput(){return ss.str();}
    void addPro(string name,int at,int nt);
    int getProlength();
private:
    Queue readyQueue;
    Queue finishQueue;
    vector<PCB*> pro_list;
    int time;
    string line;
    stringstream ss;
};

#endif // PROMANAGER_H
