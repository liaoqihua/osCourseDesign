#include "pcb.h"

PCB::PCB():remain_time(0),finish_time(0),turn_time(0),locked(1)
{

}
PCB::PCB(PCB &data):job_name(data.job_name),
    arrival_time(data.arrival_time),need_time(data.need_time),
    wait_time(data.wait_time),start_time(data.start_time),
    remain_time(data.remain_time),finish_time(data.finish_time),
    turn_time(data.turn_time),weight_turn_time(data.weight_turn_time),
    pri(data.pri),locked(0)
{

}
PCB& PCB::create(string name,float at,float nt)
{
    job_name = name;
    arrival_time = at;
    need_time = nt;
    return *this;
}
