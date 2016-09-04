//
//  core_audio_output.hpp
//  audiosim
//
//  Created by David Albrecht on 9/3/16.
//  Copyright © 2016 David Albrecht. All rights reserved.
//

#ifndef core_audio_output_hpp
#define core_audio_output_hpp

#import <AudioUnit/AudioUnit.h>

#include <math.h>
#include <stdlib.h>
#include "constants.h"

class Mixer;

class CoreAudioOutput {
public:
    CoreAudioOutput(Mixer &m);
    void init();
    void start();
  
private:
    AudioComponentDescription _defaultDescription;
    AudioComponent _output;
    AudioComponentInstance _outputInstance;
    AudioStreamBasicDescription _streamFormat;
    AURenderCallbackStruct _renderCallback;
    long _renderedFrames;
    Mixer &_mixer;
    
    void initializeConstantValuedStructures();
    static OSStatus coreAudioCallback(void *inRefCon,
                                      AudioUnitRenderActionFlags *ioActionFlags,
                                      const AudioTimeStamp *inTimeStamp, UInt32 inBusNumber,
                                      UInt32 inNumberFrames, AudioBufferList *ioData);
    
    OSStatus render(AudioUnitRenderActionFlags *ioActionFlags,
                const AudioTimeStamp *inTimeStamp, UInt32 inBusNumber,
                UInt32 inNumberFrames, AudioBufferList *ioData);
};

#endif /* core_audio_output_hpp */
