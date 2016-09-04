//
//  mixer.cpp
//  audiosim
//
//  Created by David Albrecht on 9/4/16.
//  Copyright © 2016 David Albrecht. All rights reserved.
//

#include "mixer.hpp"

Mixer::Mixer() {
    mPbCmdQ = std::queue<playback_command_t*>();
}

void Mixer::enqueuePlaybackCmd(playback_command_t *cmd) {
    
}

void Mixer::pbCmdProcessorThreadEntry() {
    
}

