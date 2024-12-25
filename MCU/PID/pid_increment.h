#ifndef __PID_INCREMENT_H_
#define __PID_INCREMENT_H_

#include <stdio.h>

typedef struct 
{
    float target_val;
    float actual_val;
    float err, err_last, err_next;
    float Kp, Ki, Kd;
}pid_increment;

pid_increment pid;

void pid_increment_init(void);
float pid_increment_realize(void);


#endif
