//
//  mixer.hpp
//  audiosim
//
//  Created by David Albrecht on 9/4/16.
//  Copyright © 2016 David Albrecht. All rights reserved.
//

#ifndef mixer_hpp
#define mixer_hpp

#include <mutex>
#include <queue>
#include "playback_command.hpp"
#include "constants.h"

class Mixer {
public:
    Mixer();
    Mixer(const Mixer &m);
    ~Mixer();
    
    // Command processing section
    // This implements a cross-thread command dispatcher used by the playback tasks to request
    // playback. Playback chains call enqueuePlaybackCmd; external code should run pbCmdProcessorThreadEntry
    // on a separate thread to process the incoming commands.
    void enqueuePlaybackCmd(playback_command_t *cmd);
    void pbCmdProcessorThreadEntry();
    
    // PCM rendering section
    // This performs the actual mixing of PCM data on a thread.
    // When 
    void getNextLPCMFrames(float* buf, int frameCount);
    void lpcmWriterThreadEntry();
    
private:
    std::queue<playback_command_t *> _cmdQueue;
    std::mutex _cmdQueueMutex;
    std::condition_variable _cmdQueueCondVar;
    float* _outputRingBuf;
    float** _sourceBuffers;
    
    void initializeBuffers();
};

#endif /* mixer_hpp */
