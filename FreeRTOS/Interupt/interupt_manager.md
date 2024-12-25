# FreeRTOS的中断管理
## 中断
让CPU打断正常运行去处理紧急事件的行为称之为中断    
**中断执行流程**   
1. 中断请求
2. 响应中断
3. 退出中断
## 中断优先级分组设置(RTOS中)
1. 低于**configMAX_SYSCALL_INTERRUPT_PRIORITY**优先级的中断里才允许调用FreeRTOS的API函数
2. 将所有优先级设置为抢占式优先级，方便RTOS进行中断管理

        HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4)
3. 中断优先级数值越小越优先，任务优先级数值越大越优先

## FreeRTOS API函数

