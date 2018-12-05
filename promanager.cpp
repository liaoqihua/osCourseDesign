#include "promanager.h"

ProManager::ProManager():time(0),line(),ss(line)
{

}

void ProManager::readfile(string filename)
{
    ifstream in(filename);
    string line;
    string name;
    int at;
    int nt;
    while(getline(in, line)){
        stringstream ss(line);
        ss >> name >> at >> nt;
        PCB *p = new PCB(name, at, nt);
        pro_list.push_back(p);
    }
}
bool cmpFCFS(PCB *a,PCB *b)
{
    return a->arrive_time < b->arrive_time;
}
void ProManager::runFCFS(PCB *p)
{
    time = p->arrive_time>time?p->arrive_time:time;
    p->start_time = time;
    time += p->need_time;
    p->finish_time = time;
    p->remain_time = 0;
    p->wait_time = p->start_time - p->arrive_time;
    p->turn_time = p->finish_time-p->arrive_time;
    p->w_turn_time = 1.0*p->turn_time/p->need_time;
    p->status = 'f';
}
void ProManager::FCFS()
{
    sort(pro_list.begin(),pro_list.end(),cmpFCFS);
    for(auto temp: pro_list){
        readyQueue.push_back(temp);
    }
    while(!readyQueue.empty()){
        PCB *top = readyQueue.pop();
        runFCFS(top);
        finishQueue.push_back(top);
    }
    ss << finishQueue.print();
}
void ProManager::SJF()
{
    sort(pro_list.begin(),pro_list.end(),cmpFCFS);
    auto n = pro_list.size();
    for(unsigned i=0;i<n;++i){
        PCB *p = nullptr;
        int shortTime = 1000;
        for(auto temp: pro_list){
            if(temp->arrive_time <= time && temp->status=='r'){
                if(shortTime > temp->need_time){
                    p = temp;
                    shortTime = temp->need_time;
                }
            }
        }
        if(p != nullptr){
            runFCFS(p);
            finishQueue.push_back(p);
        }else{
            for(auto temp: pro_list){
                if(temp->status == 'r'){
                    runFCFS(temp);
                    finishQueue.push_back(temp);
                    break;
                }
            }
        }
    }
    ss << finishQueue.print();
}
unsigned ProManager::runSRTF(PCB *p,unsigned index)
{
    time = p->arrive_time>time?p->arrive_time:time;
    if(p->need_time == p->remain_time){
        p->start_time = time;
    }
    ss << "时刻:" << time << "运行进程:" << p->name << endl;
    int shortTime = 1000;
    PCB *p1 = nullptr;
    for(auto temp: pro_list){
        if(temp->arrive_time < time+p->remain_time && temp->arrive_time>p->arrive_time && temp->need_time==temp->remain_time && temp!=p){
            if(temp->remain_time < p->remain_time+time-temp->arrive_time){
                if(shortTime>temp->remain_time){
                    shortTime = temp->remain_time;
                    p1 = temp;
                }
            }
        }
    }
    if(p1 != nullptr){
        p->remain_time -= p1->arrive_time-time;
        time = p1->arrive_time;
        ss << "进程:" << p->name << "在时刻:" << time << "被进程:" << p1->name << "抢断"
             << "剩余时间:" << p->remain_time << endl;
    }else{
        time+=p->remain_time;
        p->status = 'f';
        p->finish_time = time;
        p->remain_time = 0;
        p->wait_time = p->start_time-p->arrive_time;
        p->turn_time = p->finish_time - p->arrive_time;
        p->w_turn_time = 1.0*p->turn_time/p->need_time;
        finishQueue.push_back(p);
        index++;
    }
    return index;
}
void ProManager::SRTF()
{
    sort(pro_list.begin(),pro_list.end(),cmpFCFS);
    unsigned i=0;
    auto n = pro_list.size();
    while(i<n){
        PCB *p = nullptr;
        int shortTime = 1000;
        for(auto temp: pro_list){
            if(temp->arrive_time <= time && temp->status=='r'){
                if(shortTime > temp->remain_time){
                    p = temp;
                    shortTime = temp->remain_time;
                }
            }
        }
        if(p != nullptr){
            i = runSRTF(p, i);
        }else{
            for(auto temp: pro_list){
                if(temp->status == 'r'){
                    i = runSRTF(temp, i);
                    break;
                }
            }
        }
    }
    ss << finishQueue.print();
}
unsigned ProManager::runRR(PCB *p,int ti,unsigned index)
{
    if(p!=nullptr){
        if(p->need_time == p->remain_time){
            p->start_time = time;
        }
        ss << "时刻:" << time << "运行进程:" << p->name << endl;
        if(ti>=p->remain_time){
            time += p->remain_time;
            p->remain_time = 0;
            p->finish_time = time+p->remain_time;
            p->wait_time = p->start_time - p->arrive_time;
            p->turn_time = p->finish_time - p->arrive_time;
            p->w_turn_time = 1.0*p->turn_time/p->need_time;
            p->status = 'f';
            finishQueue.push_back(p);
            index++;
            ss << "时刻:" << time << "结束进程:" << p->name << endl;
        }else{
            p->remain_time -= ti;
            time += ti;
            for(auto temp: pro_list){
                if(temp->arrive_time < time && temp->status == 'r'){
                    readyQueue.push_back(temp);
                    temp->status = 'b';
                }
            }
            readyQueue.push_back(p);
        }
    }else{
        time++;
    }
    return index;
}
void ProManager::RR()
{
    sort(pro_list.begin(),pro_list.end(),cmpFCFS);
    unsigned i=0;
    auto n = pro_list.size();
    while(i<n){
        for(auto temp: pro_list){
            if(temp->arrive_time <= time && temp->status == 'r'){
                readyQueue.push_back(temp);
                temp->status = 'b';
            }
        }
        if(!readyQueue.empty()){
            PCB *top = readyQueue.pop();
            i = runRR(top,3,i);
        }else{
            i = runRR(nullptr,3,i);
        }
    }
    ss << finishQueue.print();
}

unsigned ProManager::runPSA(PCB *p,unsigned index)
{
    if(p){
        if(p->need_time == p->remain_time){
            p->start_time = time;
        }
        p->finish_time = time+p->remain_time;
        p->wait_time = p->start_time - p->arrive_time;
        time += p->remain_time;
        p->remain_time = 0;
        p->turn_time = p->finish_time - p->arrive_time;
        p->w_turn_time = 1.0*p->turn_time/p->need_time;
        p->status = 'f';
        finishQueue.push_back(p);
        index++;
    }else{
        time+=1;
    }
    return index;
}
bool cmpPSA(PCB *a,PCB *b){
    return a->pri > b->pri;
}
void ProManager::PSA(string input)
{
    sort(pro_list.begin(),pro_list.end(),cmpFCFS);
    unsigned i=0;
    auto n=pro_list.size();
    stringstream ss1(input);
    for(unsigned j=0;j<n;++j){
        int pri_t;
        ss1 >> pri_t;
        pro_list[j]->pri = pri_t;
    }
    while(i<n){
        for(auto temp: pro_list){
            if(temp->arrive_time <= time && temp->status=='r'){
                readyQueue.push_back(temp);
                temp->status = 'b';
            }
        }
        if(!readyQueue.empty()){
            //优先级排序
            vector<PCB*> pro_t;
            while(!readyQueue.empty()){
                pro_t.push_back(readyQueue.pop());
            }
            sort(pro_t.begin(),pro_t.end(),cmpPSA);
            for(auto temp: pro_t){
                readyQueue.push_back(temp);
            }
            PCB *top = readyQueue.pop();
            i = runPSA(top, i);
        }else{
            i = runPSA(nullptr,i);
        }
    }
    ss << finishQueue.print();
}
bool cmpHRRN(PCB *a,PCB *b){
    return a->priD > b->priD;
}
void ProManager::HRRN(string input)
{
    sort(pro_list.begin(),pro_list.end(),cmpFCFS);
    unsigned i=0;
    auto n=pro_list.size();
    stringstream ss1(input);
    for(unsigned j=0;j<n;++j){
        int pri_t;
        ss1 >> pri_t;
        pro_list[j]->pri = pri_t;
    }
    while(i<n){
        for(auto temp: pro_list){
            if(temp->arrive_time <= time && temp->status=='r'){
                readyQueue.push_back(temp);
                temp->status = 'b';
            }
        }
        if(!readyQueue.empty()){
            vector<PCB*> pro_t;
            while(!readyQueue.empty()){
                PCB *temp = readyQueue.pop();
                temp->priD = 1.0*(time-temp->arrive_time + temp->need_time)/temp->need_time;
                pro_t.push_back(temp);
            }
            sort(pro_t.begin(),pro_t.end(),cmpHRRN);
            for(auto temp: pro_t){
                readyQueue.push_back(temp);
            }
            PCB *top = readyQueue.pop();
            runFCFS(top);
            i++;
            finishQueue.push_back(top);
        }else{
            for(auto temp: pro_list){
                if(temp->status=='r'){
                    temp->status = 'b';
                    runFCFS(temp);
                    finishQueue.push_back(temp);
                    i++;
                    break;
                }
            }
        }
    }
    ss << finishQueue.print();
}
unsigned ProManager::runMFQ(PCB *p,int ti,unsigned index)
{
    time = p->arrive_time>time?p->arrive_time:time;
    if(p->need_time == p->remain_time){
        p->start_time = time;
    }
    ss << "时刻:" << time << "开始进程:" << p->name << " 时间片长度:" << ti << endl;
    if(p->remain_time <= ti){
        p->finish_time = time+p->remain_time;
        p->remain_time = 0;
        p->wait_time = p->start_time - p->arrive_time;
        p->turn_time = p->finish_time - p->arrive_time;
        p->w_turn_time = 1.0*p->turn_time/p->need_time;
        finishQueue.push_back(p);
        time = p->finish_time;
        index++;
        ss << "时刻:" << p->finish_time << "结束进程:" << p->name << " 时间片长度:" << ti << endl;
    }else{
        p->remain_time -= ti;
        time += ti;
        ss << "时刻:" << time << "进程:" << p->name << "时间片使用完" << " 时间片长度:" << ti << endl;
    }
    return index;
}
void ProManager::MFQ()
{
    unsigned q_size = 4;
    vector<Queue> mq(q_size);
    vector<int> mt(q_size);
    for(unsigned j=0;j<q_size;++j){
        mt[j] = static_cast<int>(pow(2.0,1.0*j));
    }
    sort(pro_list.begin(),pro_list.end(),cmpFCFS);
    unsigned i=0;
    auto n = pro_list.size();
    while(i<n){
        //新添加进程
        for(auto temp: pro_list){
            if(temp->arrive_time<=time && temp->status=='r'){
                mq[0].push_back(temp);
                temp->status = 'b';
            }
        }
        int flag = 0;
        for(unsigned mq_index=0;mq_index<mq.size();++mq_index){
            if(!mq[mq_index].empty()){
                //排序
                vector<PCB*> ar_t;
                while(!mq[mq_index].empty()){
                    ar_t.push_back(mq[mq_index].pop());
                }
                mq[mq_index].clear();
                sort(ar_t.begin(),ar_t.end(),cmpFCFS);
                for(auto temp: ar_t){
                    mq[mq_index].push_back(temp);
                }
                PCB *top = mq[mq_index].pop();
                auto j = runMFQ(top,mt[mq_index],i);
                if(j != i+1){
                    if(mq_index < q_size-1){
                        mq[mq_index+1].push_back(top);
                    }else{
                        mq[mq_index].push_back(top);
                    }
                }else{
                    i = j;
                }
                flag = 1;
                break;
            }
        }
        if(flag == 0){
            for(auto temp: pro_list){
                if(temp->status == 'r'){
                    mq[0].push_back(temp);
                    temp->status = 'b';
                    break;
                }
            }
        }
    }
    ss << finishQueue.print();
}
void ProManager::print(QTextEdit *edit)
{
    string line;
    stringstream ss1(line);
    ss1 << "进程名\t到达时间\t服务时间\t开始时间\t结束时间\t等待时间\t剩余时间\t周转时间\t带权周转时间";
    edit->clear();
    edit->append(QString::fromLocal8Bit(ss1.str().c_str()));
    for(auto temp: pro_list){
        temp->printPCBQt(edit);
    }
}
void ProManager::addPro(string name,int at,int nt)
{
    PCB *n = new PCB(name, at, nt);
    pro_list.push_back(n);
}
void ProManager::reset()
{
    vector<PCB*> new_pro_list;
    for(auto temp: pro_list){
        PCB *n = new PCB(temp->name,temp->arrive_time,temp->need_time);
        new_pro_list.push_back(n);
    }
    pro_list.clear();
    for(auto temp: new_pro_list){
        pro_list.push_back(temp);
    }
    finishQueue.clear();
    ss.str("");
    time = 0;
}
int ProManager::getProlength()
{
    return static_cast<int>(pro_list.size());
}
