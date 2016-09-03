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

class CoreAudioOutput {
public:
    CoreAudioOutput();
    void Init();
    void Start();
  
private:
    AudioComponentDescription mDefaultDescription;
    AudioComponent mOutput;
    AudioComponentInstance mOutputInstance;
    AudioStreamBasicDescription mStreamFormat;
    AURenderCallbackStruct mRenderCallback;
    long mRenderedFrames;
    
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
