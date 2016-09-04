//
//  two_state_task.cpp
//  audiosim
//
//  Created by David Albrecht on 9/3/16.
//  Copyright © 2016 David Albrecht. All rights reserved.
//

#include <iostream>
#include "two_state_task.hpp"
#include "task_scheduler.hpp"

TwoStateTask::TwoStateTask(int delayMs) {
    mState = 0;
    mDelay = delayMs;
}

void TwoStateTask::run(TaskScheduler *ts) {
    std::cout << "In two state task, delay: " << mDelay << " " << std::endl;
    
    mState = (mState + 1) % 2;
    ts->scheduleDelayedExecutionRelative(this, mDelay);
}
