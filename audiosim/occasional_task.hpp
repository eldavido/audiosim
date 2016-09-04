//
//  occasional_task.hpp
//  audiosim
//
//  Created by David Albrecht on 9/3/16.
//  Copyright © 2016 David Albrecht. All rights reserved.
//

#ifndef occasional_task_hpp
#define occasional_task_hpp

#include "task.hpp"
#include <random>

class OccasionalTask : public Task {
public:
    OccasionalTask(int minDelaySecs, int maxDelaySecs);
    void run(TaskScheduler *ts);
    
private:
    int mState;
    int mMinDelaySecs;
    int mMaxDelaySecs;
    
    std::random_device mRd;
    std::mt19937 mRng;
    std::uniform_real_distribution<> mUniformDistribution;
};

#endif /* occasional_task_hpp */
