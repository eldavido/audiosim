//
//  mixer.cpp
//  audiosim
//
//  Created by David Albrecht on 9/4/16.
//  Copyright © 2016 David Albrecht. All rights reserved.
//

#include "mixer.hpp"
#include <iostream>
#include "constants.h"

Mixer::Mixer() : _cmdQueue(), _cmdQueueMutex(), _cmdQueueCondVar() {
    initializeBuffers();
}

Mixer::Mixer(const Mixer &m) : _cmdQueue(m._cmdQueue), _cmdQueueMutex(), _cmdQueueCondVar() {
    initializeBuffers();
}

Mixer::~Mixer() {
    while (_cmdQueue.size() > 0) {
        free(_cmdQueue.front());
        _cmdQueue.pop();
    }
    
    free(_outputRingBuf);
}

//
// Command processor
//

void Mixer::enqueuePlaybackCmd(playback_command_t *cmd) {
    std::unique_lock<std::mutex> lock(_cmdQueueMutex);
    _cmdQueue.push(cmd);
    _cmdQueueCondVar.notify_all();
}

void Mixer::pbCmdProcessorThreadEntry() {
    while(true) {
        std::unique_lock<std::mutex> lock(_cmdQueueMutex);
        _cmdQueueCondVar.wait(lock, [=]{ return !_cmdQueue.empty(); });
        
        playback_command_t * cmd = _cmdQueue.front();
        std::cout << "Dequeued item from queue!!" << std::endl;
        
        // append this to the playing list
        
        free(cmd);
        _cmdQueue.pop();
    }
}

//
// PCM rendering
//

void Mixer::lpcmWriterThreadEntry() {
    while (true) {
        // Mix the next PCM_WRITER_STEP_SIZE frames
        //mSource1->renderNext(mSrc1Buf, inNumberFrames);
        //mSource2->renderNext(mSrc2Buf, inNumberFrames);
        //mSource3->renderNext(mSrc3Buf, inNumberFrames);
        
        //for (int i = 0; i < inNumberFrames; ++i) {
        //    buffer[i] = (0.33 * mSrc1Buf[i]) + (0.33 * mSrc2Buf[i]) + (0.33 * mSrc3Buf[i]);
        //}
    }
}

void Mixer::getNextLPCMFrames(float* buf, int frameCount) {
    // Copy the frames from the ring buffer into buf
    // Update the buffer's tail position
}

void Mixer::initializeBuffers() {
    // Allocate output buffer
    _outputRingBuf = (float*) malloc(OUTPUT_BUFFER_FRAMES * sizeof(float));
    
    // Allocate the source buffers
    for (int i=0; i < SOURCE_BUFFER_COUNT; ++i) {
        float *src_buf = (float*) malloc(SOURCE_BUFFER_FRAMES * sizeof(float));
        _sourceBuffers[i] = src_buf;
    }
}
