//
//  run_request.h
//  audiosim
//
//  Created by David Albrecht on 9/3/16.
//  Copyright © 2016 David Albrecht. All rights reserved.
//

#ifndef run_request_h
#define run_request_h

class Task;

struct run_request {
    long run_at_ms_time;
    Task* t;
};

typedef struct run_request run_request_t;

#endif /* run_request_h */
