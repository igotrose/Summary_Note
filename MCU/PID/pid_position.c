#include "pid_position.h"

void pid_position_init(void)
{
    pid.target_val = 0.0;
    pid.actual_val = 0.0;
    pid.err = 0.0;
    pid.err_last = 0.0;
    pid.integral = 0.0;
    pid.Kp = 0.31;
    pid.Ki = 0.070;
    pid.Kd = 0.3;
}

float pid_position_realize(void)
{
    // 计算当前误差
    pid.err = pid.target_val - pid.actual_val;
    // 误差累积
    pid.integral += pid.err;
    // 算法实现
    pid.actual_val = \
    pid.Kp * pid.err + \ 
    pid.Ki * pid.integral + \ 
    pid.Kd * (pid.err - pid.err_last);
    // 更新误差
    pid.err_last = pid.err;
    // 返回新的值
    return pid.actual_val;
}
