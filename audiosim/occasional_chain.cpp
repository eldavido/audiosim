//
//  occasional_chain.cpp
//  audiosim
//
//  Created by David Albrecht on 9/3/16.
//  Copyright © 2016 David Albrecht. All rights reserved.
//

#include "occasional_chain.hpp"

#include <iostream>
#include <random>
#include "scheduler.hpp"

OccasionalChain::OccasionalChain(int minDelay, int maxDelay) {
    mState = 0;
    std::random_device rd;
    mRng = std::mt19937(rd());
    mUniformDistribution = std::uniform_real_distribution<>(minDelay, maxDelay);
}

void OccasionalChain::run(Scheduler &sched) {
    int delayMs;
    
    switch (mState) {
        case 0:
            delayMs = mUniformDistribution(mRng) * 1000;
            std::cout << "occ task, delaying " << delayMs << "ms" << std::endl;
            
            mState = 1;
            sched.scheduleDelayedExecutionRelative(*this, delayMs);
            break;
        case 1:
            std::cout << "would play sound here" << std::endl;
            
            mState = 0;
            sched.scheduleDelayedExecutionRelative(*this, 0);
            break;
    }
}
