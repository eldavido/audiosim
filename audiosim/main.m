//
//  main.m
//  audiosim
//
//  Created by David Albrecht on 9/3/16.
//  Copyright © 2016 David Albrecht. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AudioUnit/AudioUnit.h>

const float PI = 3.141592;
const int SAMPLE_RATE = 44100;
const int FREQ = 440;
long renderedFrames = 0;

OSStatus RenderTone(void *inRefCon, AudioUnitRenderActionFlags *ioActionFlags,
                    const AudioTimeStamp *inTimeStamp, UInt32 inBusNumber,
                    UInt32 inNumberFrames, AudioBufferList *ioData) {
    const double amplitude = 0.25;
    const int channel = 0;
    
    Float32 *buffer = (Float32 *)ioData->mBuffers[channel].mData;
    Float32 coeff = 2*PI*FREQ/SAMPLE_RATE;
    
    // Generate the samples
    for (UInt32 frame = 0; frame < inNumberFrames; ++frame) {
        buffer[frame] = amplitude * sin(coeff * (frame+renderedFrames));
    }
    
    renderedFrames += inNumberFrames;
    return noErr;
}

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        AudioComponentDescription defaultOutputDescription;
        defaultOutputDescription.componentType = kAudioUnitType_Output;
        defaultOutputDescription.componentSubType = kAudioUnitSubType_DefaultOutput;
        defaultOutputDescription.componentManufacturer = kAudioUnitManufacturer_Apple;
        defaultOutputDescription.componentFlags = 0;
        defaultOutputDescription.componentFlagsMask = 0;
        
        AudioComponent defaultOutput = AudioComponentFindNext(NULL, &defaultOutputDescription);
        NSCAssert(defaultOutput, @"Can't find default output");
        
        AudioComponentInstance toneUnit;
        OSErr err = AudioComponentInstanceNew(defaultOutput, &toneUnit);
        NSCAssert1(toneUnit, @"Error creating unit %hd", err);
        
        // Set our tone rendering function on the unit
        AURenderCallbackStruct input;
        input.inputProc = RenderTone;
        err = AudioUnitSetProperty(toneUnit, kAudioUnitProperty_SetRenderCallback, kAudioUnitScope_Input,
                                   0, &input, sizeof(input));
        NSCAssert1(err == noErr, @"Error setting callback: %hd", err);
        
        AudioStreamBasicDescription streamFormat;
        streamFormat.mSampleRate = SAMPLE_RATE;
        streamFormat.mFormatID = kAudioFormatLinearPCM;
        streamFormat.mFormatFlags = kAudioFormatFlagsNativeFloatPacked | kAudioFormatFlagIsNonInterleaved;
        streamFormat.mBytesPerPacket = 4;   // it's a float
        streamFormat.mFramesPerPacket = 1;
        streamFormat.mBytesPerFrame = 4;    // float
        streamFormat.mChannelsPerFrame = 1; // mono
        streamFormat.mBitsPerChannel = 32;  // float32
        err = AudioUnitSetProperty(toneUnit, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Input,
                                   0, &streamFormat, sizeof(AudioStreamBasicDescription));
        NSCAssert1(err == noErr, @"Error setting stream format: %hd", err);
        
        err = AudioUnitInitialize(toneUnit);
        NSCAssert1(err == noErr, @"Error initializing unit: %hd", err);
        
        err = AudioOutputUnitStart(toneUnit);
        NSCAssert1(err == noErr, @"Error starting unit: %hd", err);
        
        sleep(2000);
    }
    return 0;
}
