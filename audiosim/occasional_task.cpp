//
//  occasional_task.cpp
//  audiosim
//
//  Created by David Albrecht on 9/3/16.
//  Copyright © 2016 David Albrecht. All rights reserved.
//

#include <iostream>
#include <random>
#include "task_scheduler.hpp"
#include "occasional_task.hpp"

OccasionalTask::OccasionalTask(int minDelay, int maxDelay) {
    mState = 0;
    std::random_device rd;
    mRng = std::mt19937(rd());
    mUniformDistribution = std::uniform_real_distribution<>(minDelay, maxDelay);
}

void OccasionalTask::run(TaskScheduler *ts) {
    int delayMs;
    
    switch (mState) {
        case 0:
            delayMs = mUniformDistribution(mRng) * 1000;
            std::cout << "occ task, delaying " << delayMs << "ms" << std::endl;
            
            mState = 1;
            ts->scheduleDelayedExecutionRelative(this, delayMs);
            break;
        case 1:
            std::cout << "would play sound here" << std::endl;
            
            mState = 0;
            ts->scheduleDelayedExecutionRelative(this, 0);
            break;
    }
}
