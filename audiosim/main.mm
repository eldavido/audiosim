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
#include "task_scheduler.hpp"
#include "two_state_task.hpp"

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        //CoreAudioOutput* op = new CoreAudioOutput();
        //op->Init();
        //op->Start();
        
        TaskScheduler ts = TaskScheduler();
        
        TwoStateTask *fastTst = new TwoStateTask(500);
        ts.add(fastTst);
        TwoStateTask *slowTst = new TwoStateTask(1000);
        ts.add(slowTst);
        
        ts.run();
    }
    return 0;
}
