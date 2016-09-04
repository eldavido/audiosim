//
//  mixer.hpp
//  audiosim
//
//  Created by David Albrecht on 9/4/16.
//  Copyright © 2016 David Albrecht. All rights reserved.
//

#ifndef mixer_hpp
#define mixer_hpp

#include <queue>
#include "playback_command.h"

class Mixer {
public:
    Mixer();
    
    void pbCmdProcessorThreadEntry();
    void enqueuePlaybackCmd(playback_command_t *cmd);
    
private:
    std::queue<playback_command_t *> mPbCmdQ;
};

#endif /* mixer_hpp */
