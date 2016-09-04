//
//  task_scheduler.cpp
//  audiosim
//
//  Created by David Albrecht on 9/3/16.
//  Copyright © 2016 David Albrecht. All rights reserved.
//

#include <functional>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <sys/time.h>

#include "task_scheduler.hpp"
#include "task.hpp"

TaskScheduler::TaskScheduler() {
    mAllTasks = new std::forward_list<Task*>();
    mRunQueue = new std::priority_queue<run_request_t, std::vector<run_request_t>, comparator>();
}

void TaskScheduler::add(Task *t) {
    mAllTasks->push_front(t);
}

void TaskScheduler::run() {
    mRunning = true;
    
    // Start all the tasks
    for (std::forward_list<Task*>::iterator itr = mAllTasks->begin(); itr != mAllTasks->end(); ++itr) {
        (*itr)->run(this);
    }
    
    while (mRunning) {
        if (mRunQueue->size() == 0) {
            break;
        }
        
        run_request_t nextReq = mRunQueue->top();
        int msUntilNextExecution = (int) (nextReq.run_at_ms_time - getMillisecondTime());
        
        if (msUntilNextExecution > 0) {
            usleep(msUntilNextExecution * 1000);
        }
        
        nextReq.t->run(this);
        mRunQueue->pop();
    }
}

void TaskScheduler::scheduleDelayedExecutionRelative(Task *t, int delayMs) {
    long msTime = getMillisecondTime();
    
    run_request_t rr;
    rr.t = t;
    rr.run_at_ms_time = msTime + delayMs;
    
    mRunQueue->push(rr);
}

long TaskScheduler::getMillisecondTime() {
    timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}
