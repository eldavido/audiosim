//
//  sine_source.hpp
//  audiosim
//
//  Created by David Albrecht on 9/3/16.
//  Copyright © 2016 David Albrecht. All rights reserved.
//

#ifndef sine_source_hpp
#define sine_source_hpp

#include <math.h>
#include "constants.h"

class SineSource {
public:
    SineSource(float frequency);
    void render_next(float buf[], int count);
    
private:
    float mFrequency;
    float mCoefficient;
    int mSamplesGenerated;
    
    
    
};

#endif /* sine_source_hpp */
