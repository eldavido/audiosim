//
//  two_state_task.cpp
//  audiosim
//
//  Created by David Albrecht on 9/3/16.
//  Copyright © 2016 David Albrecht. All rights reserved.
//

#include <iostream>
#include "scheduler.hpp"
#include "two_state_chain.hpp"

TwoStateChain::TwoStateChain(int delayMs) {
    mState = 0;
    mDelay = delayMs;
}

void TwoStateChain::run(Scheduler &sched) {
    std::cout << "In two state task, delay: " << mDelay << " " << std::endl;
    
    mState = (mState + 1) % 2;
    sched.scheduleDelayedExecutionRelative(*this, mDelay);
}
