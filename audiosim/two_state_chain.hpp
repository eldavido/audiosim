//
//  two_state_task.hpp
//  audiosim
//
//  Created by David Albrecht on 9/3/16.
//  Copyright © 2016 David Albrecht. All rights reserved.
//

#ifndef two_state_chain_hpp
#define two_state_chain_hpp

#include "playback_chain.hpp"

class TwoStateChain : public PlaybackChain {
public:
    TwoStateChain(Mixer &m, int delayMs);
    void run(Scheduler &ts);
    
private:
    int mState;
    int mDelay;
};

#endif /* two_state_chain_hpp */
