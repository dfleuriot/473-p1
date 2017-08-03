//
//  main.cpp
//  Project1
//
//  Created by Dimitri Fleuriot on 2/26/17.
//  Copyright © 2017 Dimitri Fleuriot. All rights reserved.
//

// Project1.cpp : Defines the entry point for the console application.
//

#include "myscheduler.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[])
{
    int n;
    Policy p;
    
    n = 2;
    p = FCFS;
    
    MyScheduler schedule(p,n);
    
    schedule.CreateThread(0,5,1,1);
    schedule.CreateThread(3,4,1,2);
    schedule.CreateThread(6,5,1,3);
    
    schedule.Go();
    
    return 0;
}
