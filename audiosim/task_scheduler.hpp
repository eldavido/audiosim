//
//  task_scheduler.hpp
//  audiosim
//
//  Created by David Albrecht on 9/3/16.
//  Copyright © 2016 David Albrecht. All rights reserved.
//

#ifndef task_scheduler_hpp
#define task_scheduler_hpp

#include <forward_list>
#include <queue>
#include "run_request.hpp"

class Task;

struct comparator {
    bool operator()(run_request_t i, run_request_t j) {
        return i.run_at_ms_time > j.run_at_ms_time;
    }
};

class TaskScheduler {
public:
    TaskScheduler();
    void add(Task *t);
    void run();
    void scheduleDelayedExecutionRelative(Task *t, int delayMs);
    
private:
    std::forward_list<Task*> *mAllTasks;
    std::priority_queue<run_request_t, std::vector<run_request_t>, comparator> *mRunQueue;
    bool mRunning;
    
    long getMillisecondTime();
};

#endif /* task_scheduler_hpp */
