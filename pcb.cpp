#include "pcb.h"

PCB::PCB()
{

}
PCB::PCB(string name,int at,int nt):name(name),status('r'),arrive_time(at),need_time(nt),
    start_time(-1),finish_time(-1),wait_time(-1),remain_time(nt),turn_time(0),w_turn_time(0)
{

}
void PCB::printPCB(ostream &os)
{
    os << name << "\t" << arrive_time << "\t" << need_time << "\t" << start_time
       << "\t" << finish_time << "\t" << wait_time << "\t" << remain_time
       << "\t" << turn_time << "\t" << w_turn_time << endl;
}
void PCB::printPCBQt(QTextEdit *edit)
{
    string line;
    stringstream ss(line);
    ss << name << "\t" << arrive_time << "\t" << need_time << "\t" << start_time
       << "\t" << finish_time << "\t" << wait_time << "\t" << remain_time
       << "\t" << turn_time << "\t" << w_turn_time;
    edit->append(QString::fromStdString(ss.str()));
}
