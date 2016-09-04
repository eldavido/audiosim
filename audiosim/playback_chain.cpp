//
//  playback_chain.cpp
//  audiosim
//
//  Created by David Albrecht on 9/3/16.
//  Copyright © 2016 David Albrecht. All rights reserved.
//

#include "playback_chain.hpp"
#include "mixer.hpp"

class Mixer;

PlaybackChain::PlaybackChain(Mixer &m) : _mixer(m) { }

void PlaybackChain::run(Scheduler &ts) {
    return;
}

void PlaybackChain::sendCommand(playback_command_t *cmd) {
    _mixer.enqueuePlaybackCmd(cmd);
}
