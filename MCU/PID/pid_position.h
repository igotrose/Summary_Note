#ifndef __PID_POSITION_H_
#define __PID_POSITION_H_

#include <stdio.h>

typedef struct 
{
    float target_val;
    float actual_val;
    float err;
    float err_last;
    float Kp, Ki, Kd;
    float integral;
}pid_position;

pid_position pid;

void pid_position_init(void);
float pid_position_realize(void);


#endif
