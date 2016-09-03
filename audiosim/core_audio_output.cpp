//
//  core_audio_output.cpp
//  audiosim
//
//  Created by David Albrecht on 9/3/16.
//  Copyright © 2016 David Albrecht. All rights reserved.
//

#include "core_audio_output.hpp"

const Float32 SAMPLE_RATE = 44100;
const Float32 FREQ = 440;

CoreAudioOutput::CoreAudioOutput() {
    initializeConstantValuedStructures();
    mRenderedFrames = 0;
}

void CoreAudioOutput::Init() {
    mOutput = AudioComponentFindNext(NULL, &mDefaultDescription);
    //NSCAssert(mOutput, "Can't find default output");
    
    OSErr err = ::AudioComponentInstanceNew(mOutput, &mOutputInstance);
    //NSCAssert1(mOutputInstance, @"Error creating unit %hd", err);
    
    // Set the render callback
    err = AudioUnitSetProperty(mOutputInstance, kAudioUnitProperty_SetRenderCallback, kAudioUnitScope_Input,
                               0, &mRenderCallback, sizeof(AURenderCallbackStruct));
    //NSCAssert1(err == noErr, @"Error setting callback: %hd", err);
    
    // Set the stream description
    err = AudioUnitSetProperty(mOutputInstance, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Input,
                               0, &mStreamFormat, sizeof(mStreamFormat));
    //NSCAssert1(err == noErr, @"Error setting stream format: %hd", err);
    
    err = AudioUnitInitialize(mOutputInstance);
    //NSCAssert1(err == noErr, @"Error initializing unit: %hd", err);
}

void CoreAudioOutput::Start() {
    AudioOutputUnitStart(mOutputInstance);
    //NSCAssert1(err == noErr, @"Error starting unit: %hd", err);
}

void CoreAudioOutput::initializeConstantValuedStructures() {
    mDefaultDescription.componentType = kAudioUnitType_Output;
    mDefaultDescription.componentSubType = kAudioUnitSubType_DefaultOutput;
    mDefaultDescription.componentManufacturer = kAudioUnitManufacturer_Apple;
    mDefaultDescription.componentFlags = 0;
    mDefaultDescription.componentFlagsMask = 0;
    
    mStreamFormat.mSampleRate = SAMPLE_RATE;
    mStreamFormat.mFormatID = kAudioFormatLinearPCM;
    mStreamFormat.mFormatFlags = kAudioFormatFlagIsFloat;
    mStreamFormat.mBytesPerPacket = 4;   // float32
    mStreamFormat.mFramesPerPacket = 1;
    mStreamFormat.mBytesPerFrame = 4;    // float32
    mStreamFormat.mChannelsPerFrame = 1; // mono
    mStreamFormat.mBitsPerChannel = 32;  // float32
    
    mRenderCallback.inputProc = coreAudioCallback;
    mRenderCallback.inputProcRefCon = this;
}

OSStatus CoreAudioOutput::coreAudioCallback(void *inRefCon,
                                            AudioUnitRenderActionFlags *ioActionFlags,
                                            const AudioTimeStamp *inTimeStamp, UInt32 inBusNumber,
                                            UInt32 inNumberFrames, AudioBufferList *ioData) {
    CoreAudioOutput *obj = (CoreAudioOutput*)inRefCon;
    return obj->render(ioActionFlags, inTimeStamp, inBusNumber, inNumberFrames, ioData);
}

OSStatus CoreAudioOutput::render(AudioUnitRenderActionFlags *ioActionFlags,
                                            const AudioTimeStamp *inTimeStamp, UInt32 inBusNumber,
                                            UInt32 inNumberFrames, AudioBufferList *ioData) {
    const double amplitude = 1.0;
    const int channel = 0;
    
    Float32 *buffer = (Float32 *)ioData->mBuffers[channel].mData;
    Float32 coeff = 2*M_PI*FREQ/SAMPLE_RATE;
    
    // Generate the samples
    for (UInt32 frame = 0; frame < inNumberFrames; ++frame) {
        buffer[frame] = amplitude * sin(coeff * (frame+mRenderedFrames));
    }
    
    mRenderedFrames += inNumberFrames;
    return noErr;
}
