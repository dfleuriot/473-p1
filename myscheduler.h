#pragma once
//myschedule.h
/* Students need to define their own data structure to contain
   and access objects from 'thread class'. The 'CreateThread()' 
   function should insert the threads into the student defined
   data structure after creating them.
   They are allowed to add any additional functionality (only 
   declaration in this file, define in 'myschedule.cpp')
   which they might find helpful.*/

#include "scheduler.h"
#include <vector>
#include <iostream>


//Define your data structure here.

/*struct thread_queue{
	int tid;
	int rem_time;
	int arr_time;
	int prio;
	int scheduled; //scheduled will tell you if a thread has finished or not (1: scheduled 0:waiting to be scheduled )
};*/

//vector<ThreadDescriptorBlock> rqueue; // vector for the ready queue
//vector<ThreadDescriptorBlock> temp; // temporary vector [same as rqueue]


class MyScheduler: public Scheduler {
public:
	MyScheduler(Policy p, unsigned int n) : Scheduler(p, n) {}
	bool Dispatch() override; //Function to implement scheduling policy and to keep a check on processed threads
	void CreateThread(int arriving_time, int remaining_time, int priority, int tid) override; //Function to create threads and insert them in student defined data structure

	//Declare additional methods(s) below if needed.

	struct compareArrivalTime
	{
		inline bool operator() (const ThreadDescriptorBlock* instance1, const ThreadDescriptorBlock* instance2) //overloading < operator
		{
			return (instance1->arriving_time < instance2->arriving_time);
		}
	};

	struct compareRemaningTime
	{
		inline bool operator() (const ThreadDescriptorBlock* instance1, const ThreadDescriptorBlock* instance2) //overloading < operator
		{
			return (instance1->remaining_time < instance2->remaining_time);
		}
	};
    
    void deletevec (ThreadDescriptorBlock &vector);
};
