# FreeRTOS的任务控制
## API函数
|API函数|描述|
|------|-----|
|vTaskDelay()|相对延时|
|xTaskDelayUntil()|绝对延时|
|uxTaskPriorityGet()|设置任务优先级|
|uxTaskPriorityGet()|获取任务优先级|
|vTaskSuspend()|挂起任务|
|vTaskResume()|恢复被挂起的任务|

### 延时函数
#### 相对延时函数
    void vTaskDelay( const TickType_t xTicksToDelay );

|形参|描述|
|----|---|
|xTicksToDelay|调用任务应阻塞的 tick 周期数|
1. 此任务用于阻塞任务，需要将 **INCLUDE_vTaskDelay** 配置为1
2. 指每次延时都是从执行函数 **vTaskDelay()** 开始，直到延时指定的时间结束
#### 绝对延时函数
    void xTaskDelayUntil( TickType_t *pxPreviousWakeTime, const TickType_t xTimeIncrement );

|形参|描述|
|----|---|
|pxPreviousWakeTime|一个指向 TickType_t 类型变量的指针，用于记录任务上一次被唤醒的时间点（tick 值）|
|xTimeIncrement|表示任务的周期时间，以 tick 为单位|
1. 此任务用于阻塞任务，需要将 **INCLUDE_xTaskDelayUntil** 配置为1
2. 延时时间从任务开始时计算直到任务结束
#### 相对延时函数 - CMSIS-RTOS封装
    osStatus_t osDelay (uint32_t ticks);
1. 阻塞任务，底层调用的是 **vTaskDelay**

### 任务优先级函数
#### 获取任务优先级函数
    UBaseType_t uxTaskPriorityGet( const TaskHandle_t xTask );
|形参|描述|
|----|---|
|xTask|待查询任务的句柄。传递 NULL 句柄会返回调用任务的优先级|
1. **INCLUDE_uxTaskPriorityGet** 必须定义为 1，才可使用此函数。
#### 设置任务优先级函数
    void vTaskPrioritySet( TaskHandle_t xTask, UBaseType_t uxNewPriority );
|形参|描述|
|----|---|
|xTask|待设置任务的句柄。传递 NULL 句柄会代表设置自身任务的优先级|
|uxNewPriority|需要设置的优先级|
1. **INCLUDE_vTaskPrioritySet** 必须定义为 1，才可使用此函数。
2. 如果正在设置的优先级高于当前执行任务的优先级，则函数返回之前将发生上下文切换。

**demo**

    void vAFunction( void )
    {
        TaskHandle_t xHandle;
        xTaskCreate( vTaskCode, "NAME", STACK_SIZE, NULL, tskIDLE_PRIORITY, &xHandle );
        if ( uxTaskPriorityGet( xHandle ) != tskIDLE_PRIORITY )
        {
        }
        vTaskPrioritySet( xHandle, tskIDLE_PRIORITY + 1 )  
        if( uxTaskPriorityGet( xHandle ) < uxTaskPriorityGet( NULL ) )
        {
        }
        vTaskPrioritySet( NULL, tskIDLE_PRIORITY + 1 )  
    } 

#### 获取任务优先级函数 - CMSIS-RTOS封装
    osPriority_t osThreadGetPriority( osThreadId_t thread_id );	
|形参|描述|
|----|---|
|thread_id|待查询任务的句柄。传递 NULL 句柄会返回调用任务的优先级|
#### 设置任务优先级函数 - CMSIS-RTOS封装
    osStatus_t osThreadSetPriority(	osThreadId_t thread_id, osPriority_t priority );
|形参|描述|
|----|---|
|thread_id|待设置任务的句柄。传递 NULL 句柄会代表设置自身任务的优先级|
|priority|需要设置的优先级|	

### 任务控制函数
#### 任务挂起函数
    void vTaskSuspend(TaskHandle_t xTaskToSuspend)

|形参|描述|
|----|---|
|xTaskToSuspend|待挂起任务的任务句柄|   

1. 此函数用于挂起任务，需要将**INCLUDE_vTaskSuspend**配置为1
2. 无论优先级如何，被挂起的任务都及那个不被再执行，直到任务被恢复
3. 当传入的参数为NULL，则代表挂起任务自身（当前正在运行的任务）
#### 任务恢复函数
    void vTaskResume(TaskHandle_t xTaskToResume)

|形参|描述|
|----|---|
|xTaskToResume|待恢复任务的任务句柄|  
1. 此函数用于挂起任务，需要将**INCLUDE_vTaskSuspend**配置为1
2. 任务无论被 **vTaskSuspend()** 挂起多少次，只需要再任务中调用 **vTaskResume()** 恢复一次，就可以继续运行

**demo**

    void vAFunction( void )
    {
        TaskHandle_t xHandle;
        xTaskCreate( vTaskCode, "NAME", STACK_SIZE, NULL, tskIDLE_PRIORITY, &xHandle );
        vTaskSuspend( xHandle );
        vTaskResume( xHandle );
    }

#### 任务挂起函数 - CMSIS-RTOS封装
    osStatus_t osThreadSuspend(osThreadId_t	thread_id)
|形参|描述|
|----|---|
|thread_id|待挂起任务的任务句柄|   
#### 任务恢复函数 - CMSIS-RTOS封装
    osStatus_t osThreadResume(osThreadId_t thread_id)	
|形参|描述|
|----|---|
|thread_id|待恢复任务的任务句柄|