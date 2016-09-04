//
//  main.m
//  audiosim
//
//  Created by David Albrecht on 9/3/16.
//  Copyright © 2016 David Albrecht. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AudioUnit/AudioUnit.h>
#include <thread>

#include "core_audio_output.hpp"
#include "mixer.hpp"
#include "occasional_chain.hpp"
#include "scheduler.hpp"
#include "two_state_chain.hpp"

void runCmdProcessor(Mixer *m) {
    m->pbCmdProcessorThreadEntry();
}

void runScheduler(Scheduler *s) {
    s->run();
}

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // Audio mixer writes PCM output to OS-level audio output, based on
        // commands received from playback chains
        Mixer m;
        std::thread cmdProcessor (runCmdProcessor, &m);
        
        // Scheduler implements a run loop (single-threaded) over the playback
        // chains, allowing them to enqueue playback tasks for the mixer
        Scheduler s;
        
        OccasionalChain occChain(m, 5, 15);
        s.add(occChain);
        TwoStateChain fastTst(m, 500);
        s.add(fastTst);
        TwoStateChain slowTst(m, 1000);
        s.add(slowTst);
        
        //CoreAudioOutput op = CoreAudioOutput(m);
        //p.init();
        //op->Start();
        
        std::thread scheduler (runScheduler, &s);
        
        cmdProcessor.join();
        scheduler.join();
    }
    
    return 0;
}

