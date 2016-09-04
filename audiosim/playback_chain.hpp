//
//  playback_chain.hpp
//  audiosim
//
//  Created by David Albrecht on 9/3/16.
//  Copyright © 2016 David Albrecht. All rights reserved.
//

#ifndef playback_chain_hpp
#define playback_chain_hpp

#include "playback_command.hpp"

class Mixer;
class Scheduler;

class PlaybackChain {
public:
    PlaybackChain(Mixer &m);
    virtual void run(Scheduler &ts);

protected:
    void sendCommand(playback_command_t *);

private:
    Mixer &_mixer;
};

#endif /* playback_chain_hpp */
