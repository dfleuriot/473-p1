//myschedule.cpp
/*Define all the functions in 'myschedule.h' here.*/
#include "myscheduler.h"
#include <iostream>
#include <vector>
#include <algorithm>

vector<ThreadDescriptorBlock*> readyQueue;
vector<ThreadDescriptorBlock*> arriveQueue;
vector<ThreadDescriptorBlock*> scheduleQueue;

void MyScheduler::CreateThread(int arriving_time, int remaining_time, int priority, int tid) //Thread ID not Process ID
{
    //Function to Create Thread(s) and insert them in the student
    //defined data structure
    
    ThreadDescriptorBlock *newThread = new ThreadDescriptorBlock;
    newThread->tid = tid;
    newThread->arriving_time = arriving_time;
    newThread->remaining_time = remaining_time;
    newThread->priority = priority;
    
    readyQueue.push_back(newThread);
}

//MEET 3:30 on friday

bool MyScheduler::Dispatch()
{
    //Todo: Check and remove finished threads
    //Todo: Check if all the threads are finished; if so, return false
    
    int counter;
    int arriveCounter;
    
    switch(policy)
    {
        case FCFS:		//First Come First Serve
            /*
             for(int i = 0; i < num_cpu; ++i)
             if(CPUs[i]) cout << "CPU: " << i << "  Thread: "<< CPUs[i]->tid << ";";
             cout<<endl;
             cout<<"Time: "<<timer<<endl;
             */
            
            for (int y = 0; y < num_cpu; y++){
                if (CPUs[y] == NULL){
                    // cout<<"   CPU: "<<y<<endl;
                    for(int b = 0; b < readyQueue.size(); b++){
                        if(readyQueue[b]->arriving_time <= timer)
                        {
                            //cout<<"        Thread: "<<readyQueue[b]->tid<<endl;
                            scheduleQueue.push_back(readyQueue[b]);
                            readyQueue.erase(readyQueue.begin()+b);
                            int size = (int)scheduleQueue.size()-1;
                            CPUs[y] = scheduleQueue[size];
                        }
                    }
                }
            }
            
            
            counter = 0;
            while (counter < scheduleQueue.size()){
                if(scheduleQueue[counter]->remaining_time == 0){
                    scheduleQueue.erase(scheduleQueue.begin()+counter);
                    counter = 0;
                }
                else{
                    counter ++;
                }
            }
            
            if (readyQueue.size() == 0 && scheduleQueue.size() == 0){ // return false if there's nothing to schedule'
                // cout<< "Simulation ended. Queue is empty";
                return false;
            }
            
            break;
            
        case STRFwoP:	//Shortest Time Remaining First, without preemption
            
            //            for(int i = 0; i < num_cpu; ++i)
            //                if(CPUs[i]) cout << "CPU: " << i << "  Thread: "<< CPUs[i]->tid << ";";
            //            cout<<endl;
            //            cout<<"Time: "<<timer<<endl;
            
            
            
            arriveCounter = 0;
            
            while(arriveCounter < readyQueue.size()){
                if(readyQueue[arriveCounter]->arriving_time == timer){
                    arriveQueue.push_back(readyQueue[arriveCounter]);
                    readyQueue.erase(readyQueue.begin()+arriveCounter);
                    arriveCounter = 0;
                }
                else{
                    arriveCounter ++;
                }
            }
            
            //            for(int i=0; i < readyQueue.size(); i++){
            //                if(readyQueue[i]->arriving_time == timer){
            //                    arriveQueue.push_back(readyQueue[i]);
            //                    readyQueue.erase(readyQueue.begin()+i);
            //                }
            //            }
            
            sort(arriveQueue.begin(), arriveQueue.end(), compareRemaningTime());
            
            /*for(int i=0; i < arriveQueue.size(); i++){
             cout<<"thread id "<<arriveQueue[i].tid<<endl;
             cout<< arriveQueue[i].remaining_time<<endl;
             }*/
            
            for (int y = 0; y < num_cpu; ++y){
                if (CPUs[y] == NULL){
                    if(arriveQueue.size() > 0){
                        // for(int b = 0; b < arriveQueue.size(); b++){
                        // cout<< "arrive thread ID " << arriveQueue[0].tid << endl;
                        scheduleQueue.push_back(arriveQueue[0]);
                        arriveQueue.erase(arriveQueue.begin());
                        CPUs[y] = scheduleQueue.back();
                        //cout << y << endl;
                        //cout << "schedule thread ID "<<readyQueue[b]->tid << endl;
                        // cout << "remaing time for thread "<<readyQueue[b]->remaining_time << endl;
                        //cout << timer << endl;
                        //cout << "------"<<endl;
                    }
                }
            }
            
            counter = 0;
            while (counter < scheduleQueue.size()){
                if(scheduleQueue[counter]->remaining_time == 0){
                    scheduleQueue.erase(scheduleQueue.begin()+counter);
                    counter = 0;
                }
                else{
                    counter ++;
                }
            }
            
            if (readyQueue.size() == 0 && scheduleQueue.size() == 0){  //return false if there's nothing to schedule'
                cout<< "Simulation ended. Queue is empty";
                return false;
            }
            
            break;
        case STRFwP:	//Shortest Time Remaining First, with preemption
            
            for(int i = 0; i < num_cpu; ++i)
                if(CPUs[i]) cout << "CPU: " << i << "  Thread: "<< CPUs[i]->tid << ";";
            cout<<endl;
            cout<<"Time: "<<timer<<endl;
            cout<<endl;
            
            arriveCounter = 0;
            
            while(arriveCounter < readyQueue.size()){
                if(readyQueue[arriveCounter]->arriving_time == timer){
                    arriveQueue.push_back(readyQueue[arriveCounter]);
                    readyQueue.erase(readyQueue.begin()+arriveCounter);
                    arriveCounter = 0;
                }
                else{
                    arriveCounter ++;
                }
            }
            
            sort(arriveQueue.begin(), arriveQueue.end(), compareRemaningTime());
            
            for(int i=0; i<arriveQueue.size(); i++){
                if(arriveQueue[i]->remaining_time == 0){
                    arriveQueue.erase(arriveQueue.begin()+i);
                }
            }
            
            for (int y = 0; y < num_cpu; ++y){
                if (CPUs[y] == NULL){
                    if(arriveQueue.size() > 0){
                        scheduleQueue.push_back(arriveQueue.front());
                        arriveQueue.erase(arriveQueue.begin());
                        CPUs[y] = scheduleQueue.back();
                    }
                }
                
            }
            
            cout<<"before 2nd loop"<<endl;
            for(int i = 0; i < num_cpu; ++i)
                if(CPUs[i]) cout << "CPU: " << i << "  Thread: "<< CPUs[i]->tid << ";";
            cout<<endl;
            cout<<"Time: "<<timer<<endl;
            cout<<endl;
            
            
            for (int y = 0; y < num_cpu; ++y){
                if(CPUs[y] != NULL){
                    if(arriveQueue.size() > 0){
                        if(CPUs[y]->remaining_time > arriveQueue.front()->remaining_time){
                            for(int i = 0; i<scheduleQueue.size(); i++){
                                if(CPUs[y]->tid == scheduleQueue[i]->tid){
                                    scheduleQueue.push_back(arriveQueue.front());
                                    CPUs[y] = scheduleQueue.back();
                                    arriveQueue.push_back(scheduleQueue[i]);
                                    scheduleQueue.erase(scheduleQueue.begin()+i);
                                }
                            }
                        }
                    }
                }
            }
            
            for(int i = 0; i < num_cpu; ++i)
                if(CPUs[i]) cout << "CPU: " << i << "  Thread: "<< CPUs[i]->tid << ";";
            cout<<endl;
            cout<<"Time: "<<timer<<endl;
            cout<<"----------"<<endl;
            
            counter = 0;
            while (counter < scheduleQueue.size()){
                if(scheduleQueue[counter]->remaining_time == 0){
                    scheduleQueue.erase(scheduleQueue.begin()+counter);
                    counter = 0;
                }
                else{
                    counter ++;
                }
            }
            
            if (readyQueue.size() == 0 && scheduleQueue.size() == 0 && arriveQueue.size() == 0){  //return false if there's nothing to schedule'
                cout<< "Simulation ended. Queue is empty";
                return false;
            }
            
            //            for(int i = 0; i< scheduleQueue.size(); i++){
            //                cout<<"tid "<<scheduleQueue[i]->tid<<" remaningTime "<<scheduleQueue[i]->remaining_time<<endl;
            //            }
            
            //cout<<"readyQueue " << readyQueue.size() << ";" << "scheduleQueue " << scheduleQueue.size() << " arriveQueue "<< arriveQueue.size() <<endl;
            
            break;
            
            
            
        case PBS:		//Priority Based Scheduling, with preemption
            
            break;
        default :
            cout<<"Invalid policy!";
            throw 0;
    }
    return true;
}

