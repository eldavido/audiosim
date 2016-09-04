//
//  task.hpp
//  audiosim
//
//  Created by David Albrecht on 9/3/16.
//  Copyright © 2016 David Albrecht. All rights reserved.
//

#ifndef task_hpp
#define task_hpp

class TaskScheduler;

class Task {
public:
    Task();
    virtual void run(TaskScheduler *ts);
};

#endif /* task_hpp */
