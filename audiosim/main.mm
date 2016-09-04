//
//  main.m
//  audiosim
//
//  Created by David Albrecht on 9/3/16.
//  Copyright © 2016 David Albrecht. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AudioUnit/AudioUnit.h>

#include "core_audio_output.hpp"
#include "mixer.hpp"
#include "occasional_chain.hpp"
#include "scheduler.hpp"
#include "two_state_chain.hpp"

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // Audio mixer writes PCM output to OS-level audio output, based on
        // commands received from playback chains
        Mixer m = Mixer();
        
        // Scheduler implements a run loop (single-threaded) over the playback
        // chains, allowing them to enqueue playback tasks for the mixer
        Scheduler s = Scheduler();
        
        OccasionalChain occChain(5, 15);
        s.add(occChain);
        TwoStateChain fastTst(500);
        s.add(fastTst);
        TwoStateChain slowTst(1000);
        s.add(slowTst);
        
        //CoreAudioOutput op = CoreAudioOutput(m);
        //p.init();
        //op->Start();
        
        s.run();
    }
    
    return 0;
}
