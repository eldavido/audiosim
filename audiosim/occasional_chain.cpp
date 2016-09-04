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
#include "playback_command.hpp"

OccasionalChain::OccasionalChain(Mixer &m, int minDelay, int maxDelay) : PlaybackChain(m) {
    mState = 0;
    std::random_device rd;
    std::mt19937 rng(rd());
    mUniformDistribution = std::uniform_real_distribution<>(minDelay, maxDelay);
}

void OccasionalChain::run(Scheduler &sched) {
    int delayMs;
    
    switch (mState) {
        case 0:
            delayMs = mUniformDistribution(mRng) * 1000;
            mState = 1;
            sched.scheduleDelayedExecutionRelative(*this, delayMs);
            break;
        case 1:
            playback_command_t* cmd = (playback_command_t*) malloc(sizeof(playback_command_t));
            sendCommand(cmd);
            mState = 0;
            sched.scheduleDelayedExecutionRelative(*this, 0);
            break;
    }
}
