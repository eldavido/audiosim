//
//  scheduler.hpp
//  audiosim
//
//  Created by David Albrecht on 9/3/16.
//  Copyright © 2016 David Albrecht. All rights reserved.
//

#ifndef scheduler_hpp
#define scheduler_hpp

#include <forward_list>
#include <queue>
#include "run_request.hpp"

class PlaybackChain;

struct comparator {
    bool operator()(run_request_t* i, run_request_t* j) {
        return i->run_at_ms_time > j->run_at_ms_time;
    }
};

class Scheduler {
public:
    Scheduler();
    void add(PlaybackChain &t);
    void run();
    void scheduleDelayedExecutionRelative(PlaybackChain &t, int delayMs);
    
private:
    std::forward_list<PlaybackChain*> mAllTasks;
    std::priority_queue<run_request_t*, std::vector<run_request_t*>, comparator> mRunQueue;
    bool mRunning;
    
    long getMillisecondTime();
};

#endif /* scheduler_hpp */
