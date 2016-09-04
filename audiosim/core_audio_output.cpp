//
//  core_audio_output.cpp
//  audiosim
//
//  Created by David Albrecht on 9/3/16.
//  Copyright © 2016 David Albrecht. All rights reserved.
//

#include "core_audio_output.hpp"

CoreAudioOutput::CoreAudioOutput(const Mixer &m) : _mixer(m), _renderedFrames(0) {
    initializeConstantValuedStructures();
}

void CoreAudioOutput::init() {
    _output = AudioComponentFindNext(NULL, &_defaultDescription);
    //NSCAssert(mOutput, "Can't find default output");
    
    OSErr err = ::AudioComponentInstanceNew(_output, &_outputInstance);
    //NSCAssert1(mOutputInstance, @"Error creating unit %hd", err);
    
    // Set the render callback
    err = AudioUnitSetProperty(_outputInstance, kAudioUnitProperty_SetRenderCallback, kAudioUnitScope_Input,
                               0, &_renderCallback, sizeof(AURenderCallbackStruct));
    //NSCAssert1(err == noErr, @"Error setting callback: %hd", err);
    
    // Set the stream description
    err = AudioUnitSetProperty(_outputInstance, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Input,
                               0, &_streamFormat, sizeof(_streamFormat));
    //NSCAssert1(err == noErr, @"Error setting stream format: %hd", err);
    
    err = AudioUnitInitialize(_outputInstance);
    //NSCAssert1(err == noErr, @"Error initializing unit: %hd", err);
}

void CoreAudioOutput::start() {
    AudioOutputUnitStart(_outputInstance);
    //NSCAssert1(err == noErr, @"Error starting unit: %hd", err);
}

void CoreAudioOutput::initializeConstantValuedStructures() {
    _defaultDescription.componentType = kAudioUnitType_Output;
    _defaultDescription.componentSubType = kAudioUnitSubType_DefaultOutput;
    _defaultDescription.componentManufacturer = kAudioUnitManufacturer_Apple;
    _defaultDescription.componentFlags = 0;
    _defaultDescription.componentFlagsMask = 0;
    
    _streamFormat.mSampleRate = SAMPLE_RATE;
    _streamFormat.mFormatID = kAudioFormatLinearPCM;
    _streamFormat.mFormatFlags = kAudioFormatFlagIsFloat;
    _streamFormat.mBytesPerPacket = 4;   // float32
    _streamFormat.mFramesPerPacket = 1;
    _streamFormat.mBytesPerFrame = 4;    // float32
    _streamFormat.mChannelsPerFrame = 1; // mono
    _streamFormat.mBitsPerChannel = 32;  // float32
    
    _renderCallback.inputProc = coreAudioCallback;
    _renderCallback.inputProcRefCon = this;
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
    int channel = 0;
    Float32 *buffer = (Float32 *)ioData->mBuffers[channel].mData;
    
    //mSource1->renderNext(mSrc1Buf, inNumberFrames);
    //mSource2->renderNext(mSrc2Buf, inNumberFrames);
    //mSource3->renderNext(mSrc3Buf, inNumberFrames);
    
    //for (int i = 0; i < inNumberFrames; ++i) {
    //    buffer[i] = (0.33 * mSrc1Buf[i]) + (0.33 * mSrc2Buf[i]) + (0.33 * mSrc3Buf[i]);
    //}
    
    return noErr;
}
