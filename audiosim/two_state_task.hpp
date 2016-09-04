//
//  two_state_task.hpp
//  audiosim
//
//  Created by David Albrecht on 9/3/16.
//  Copyright © 2016 David Albrecht. All rights reserved.
//

#ifndef two_state_task_hpp
#define two_state_task_hpp

#include "task.hpp"

class TwoStateTask : public Task {
public:
    TwoStateTask(int delayMs);
    void run(TaskScheduler *ts);
    
private:
    int mState;
    int mDelay;
};

#endif /* two_state_task_hpp */
