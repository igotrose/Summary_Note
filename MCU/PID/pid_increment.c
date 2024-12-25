#include "pid_increment.h"

void pid_increment_init(void)
{
    pid.target_val = 0.0;
    pid.actual_val = 0.0;
    pid.err = 0.0;
    pid.err_last = 0.0;
    pid.err_next =0.0;
    pid.Kp = 0.21;
    pid.Ki = 0.80;
    pid.Kd = 0.01;
}

float pid_increment_realize(void)
{
    pid.err = pid.target_val - pid.actual_val;

    float increment_val = \
    pid.Kp*(pid.err - pid.err_next) + \
    pid.Ki*pid.err + \
    pid.Kd*(pid.err - 2 * pid.err_next + pid.err_last);

    pid.err_last = pid.err_next;
    pid.err_next = pid.err;
    return pid.actual_val;
}
