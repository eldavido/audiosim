//
//  sine_source.cpp
//  audiosim
//
//  Created by David Albrecht on 9/3/16.
//  Copyright © 2016 David Albrecht. All rights reserved.
//

#include "sine_source.hpp"

SineSource::SineSource(float frequency) {
    mSamplesGenerated = 0;
    mFrequency = frequency;
    mCoefficient = 2 * M_PI * mFrequency / SAMPLE_RATE;
}

void SineSource::render_next(float buf[], int count) {
    for (int i = 0; i < count; ++i) {
        buf[i] = sin(mCoefficient * (i+mSamplesGenerated));
    }
    
    mSamplesGenerated += count;
}
