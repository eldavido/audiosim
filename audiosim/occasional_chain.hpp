//
//  occasional_task.hpp
//  audiosim
//
//  Created by David Albrecht on 9/3/16.
//  Copyright © 2016 David Albrecht. All rights reserved.
//

#ifndef occasional_chain_hpp
#define occasional_chain_hpp

#include "playback_chain.hpp"

#include <random>

class OccasionalChain : public PlaybackChain {
public:
    OccasionalChain(Mixer &m, int minDelaySecs, int maxDelaySecs);
    void run(Scheduler &ts);
    
private:
    int mState;
    int mMinDelaySecs;
    int mMaxDelaySecs;
    
    std::random_device mRd;
    std::mt19937 mRng;
    std::uniform_real_distribution<> mUniformDistribution;
};

#endif /* occasional_chain_hpp */
