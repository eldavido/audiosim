//
//  scheduler.cpp
//  audiosim
//
//  Created by David Albrecht on 9/3/16.
//  Copyright © 2016 David Albrecht. All rights reserved.
//

#include "scheduler.hpp"

#include <functional>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <sys/time.h>
#include "playback_chain.hpp"

Scheduler::Scheduler() {
    mAllTasks = std::forward_list<PlaybackChain*>();
    mRunQueue = std::priority_queue<run_request_t*, std::vector<run_request_t*>, comparator>();
}

void Scheduler::add(PlaybackChain &t) {
    mAllTasks.push_front(&t);
}

void Scheduler::run() {
    mRunning = true;
    
    // Start all the tasks
    for (std::forward_list<PlaybackChain*>::iterator itr = mAllTasks.begin(); itr != mAllTasks.end(); ++itr) {
        (*itr)->run(*this);
    }
    
    while (mRunning) {
        if (mRunQueue.size() == 0) {
            break;
        }
        
        run_request_t* nextReq = mRunQueue.top();
        int msUntilNextExecution = (int) (nextReq->run_at_ms_time - getMillisecondTime());
        
        if (msUntilNextExecution > 0) {
            usleep(msUntilNextExecution * 1000);
        }
        
        nextReq->t->run(*this);
        mRunQueue.pop();
        free(nextReq);
    }
}

void Scheduler::scheduleDelayedExecutionRelative(PlaybackChain &t, int delayMs) {
    long msTime = getMillisecondTime();
    
    run_request_t *rr = (run_request_t *)malloc(sizeof(run_request_t));
    rr->t = &t;
    rr->run_at_ms_time = msTime + delayMs;
    
    mRunQueue.push(rr);
}

long Scheduler::getMillisecondTime() {
    timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}
