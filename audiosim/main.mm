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

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        CoreAudioOutput* op = new CoreAudioOutput();
        op->Init();
        op->Start();
        
        sleep(2000);
    }
    return 0;
}
