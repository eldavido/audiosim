//
//  playback_chain.hpp
//  audiosim
//
//  Created by David Albrecht on 9/3/16.
//  Copyright © 2016 David Albrecht. All rights reserved.
//

#ifndef playback_chain_hpp
#define playback_chain_hpp

class Scheduler;

class PlaybackChain {
public:
    PlaybackChain();
    virtual void run(Scheduler &ts);
};

#endif /* playback_chain_hpp */
