# FreeRTOS的任务实用函数
|API函数|描述|
|------|-----|
|uxTaskGetSystemState()|获取所有任务信息|
|vTaskGetInfo()|获取单个任务信息|
|uxTaskGetStackHighWaterMark()|获取任务高水位值|
|uxTaskPriorityGet()|获取任务优先级|
|vTaskSuspend()|挂起任务|
|vTaskResume()|恢复被挂起的任务|

### 获取所有任务信息函数
    UBaseType_t uxTaskGetSystemState(
                       TaskStatus_t * const pxTaskStatusArray,
                       const UBaseType_t uxArraySize,
                       unsigned long * const pulTotalRunTime );
**uxTaskGetSystemState()** 为系统中的每个任务填充了 **TaskStatus_t** 结构体，这个结构体包含任务句柄成员、任务名称、 任务优先级、任务状态以及任务消耗的总运行时间等    

|参数|描述|
|------|-----|
|pxTaskStatusArray|指向 **TaskStatus_t** 结构体数组的指针|
|uxArraySize| **pxTaskStatusArray** 参数指向数组的大小|
|pulTotalRunTime|运行时间|

1. **configUSE_TRACE_FACILITY** 必须在 **FreeRTOSConfig.h** 中定义为 1
2. 使用该函数会导致调度器长时间处于挂起状态， 因此该函数仅用于调试

**example** 

    void vTaskGetRunTimeStats( char *pcWriteBuffer )
    {
        TaskStatus_t *pxTaskStatusArray;
        volatile UBaseType_t uxArraySize, x;
        unsigned long ulTotalRunTime, ulStatsAsPercentage;

        *pcWriteBuffer = 0x00;

        uxArraySize = uxTaskGetNumberOfTasks();

        pxTaskSatusArray = pvPortMalloc( uxArraySize * sizeof( TaskStatus_t ) );
        
        if( pxTaskSatusArray != NULL )
        {
            uxArraySize = uxTaskGetSystemState( pxTaskStatusArray, uxArraySize, &ulTotalRunTime ) ;
            
            ulTotalRunTime /= 100UL;

            if( ulTotalRunTime > 0 )
            {
                for( x = 0; x < uxArraySize; x++)
                {
                    ulStatusAsPercentage = pxTaskStatusArray[ x ].ulRunTimeCounter / ulTotalRunTime;

                    if( ulStatsAsPercentage > 0UL )
                    {
                        sprintf( pcWriteBuffer, "%stt%lutt%lu%%rn",
                                            pxTaskStatusArray[ x ].pcTaskName,
                                            pxTaskStatusArray[ x ].ulRunTimeCounter,
                                            ulStatsAsPercentage );
                    }
                    else
                    {
                        sprintf( pcWriteBuffer, "%stt%lutt<1%%rn",
                                        pxTaskStatusArray[ x ].pcTaskName,
                                        pxTaskStatusArray[ x ].ulRunTimeCounter );
                    }

                    pcWriteBuffer += strlen( ( char * ) pcWriteBuffer );
                }
            }
        }
    }
### 获取单个任务信息函数
    void vTaskGetInfo( TaskHandle_t xTask,
                   TaskStatus_t *pxTaskStatus,
                   BaseType_t xGetFreeStackSpace,
                   eTaskState eState );
**vTaskGetInfo()** 只为单个任务填充 **TaskStatus_t** 结构体 。**TaskStatus_t** 结构体包含任务句柄成员、任务名称、任务优先级、任务状态以及任务消耗的总运行时间等。


1. **configUSE\_TRACE\_FACILITY** 必须在 FreeRTOSConfig.h 中定义为 1
2. 使用该函数会导致调度器长时间处于挂起状态， 因此该函数仅用于调试。


|参数|描述|
|------|-----|
|xTask|正在查询的任务的句柄|
|pxTaskStatus|指向的 **TaskStatus_t** 结构体中将填入 **xTask** 参数中传递的句柄引用的任务信息|
|xGetFreeStackSpace| **TaskStatus_t** 结构体包含一个成员，用于报告所查询任务的堆栈高水位线。|
|eState|**TaskStatus_t** 结构体包含一个成员，用于报告所查询任务的状态|

**example** 

    void vAFunction( void )
    {
        TaskHandle_t xHandle;
        TaskStatus_t xTaskDetails;

        xHandle = xTaskGetHandle( "Task_Name" );

        configASSERT( xHandle );

        vTaskGetInfo( xHandle, &xTaskDetails, pdTRUE, eInvalid );
    }
### 获取任务高水位值函数
    UBaseType_t uxTaskGetStackHighWaterMark ( TaskHandle_t xTask );
随着任务的执行和中断的处理，任务使用的堆栈会增加和缩小。     
**uxTaskGetStackHighWaterMark()** 返回任务开始执行后任务可用的最小剩余堆栈空间量。     
即任务堆栈达到最大（最深）值时未使用的堆栈量。这就是 所谓的堆栈“高水位线”。   

|参数|描述|
|------|-----|
|xTask|正在查询的任务的句柄|

|返回|描述|
|------|-----|
|返回的值是以字为单位的高水位标记|如果返回值为零，则任务可能已溢出堆栈。如果返回值接近于零，则任务已接近堆栈溢出 。|

**example** 

    void vTask( void * pvParameters )
    {
        UBaseType_t uxHighWaterMark;
        uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
        
        for( ;; )
        {
            vTaskDelay( 1000 );
            uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
        }
    }
