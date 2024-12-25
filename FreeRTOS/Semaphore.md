# 信号量
|API|描述|
|----|---|
|xSemaphoreCreateBinary|动态创建二值信号量|    
|xSemaphoreCreateBinaryStatic|静态创建二值信号量| 
|xSemaphoreCreateCounting|动态创建计数信号量|
|xSemaphoreCreateCountingStatic|静态创建计数信号量|
|xSemaphoreTake|在非中断中获取信号量|
|xSemaphoreTakeFromISR|在中断中获取信号量|

1. 在许多使用场景中，使用直达任务通知要比使用二进制信号量的速度更快，内存效率更高。 
2. 动态创建，需要将 **configSUPPORT_DYNAMIC_ALLOCATION** 在**FreeRTOSConfig.h** 设置为1
3. 静态创建，需要将 **configSUPPORT_STATIC_ALLOCATION** 在**FreeRTOSConfig.h** 设置为1
4. 创建信号量，如果成功，都会返回信号量的句柄
5. 调用操作信号量的相关宏，信号量必须已经创建
6. 在中断服务函数中，不能使用互斥锁，因为互斥锁有优先级继承机制
7. 使用互斥锁，需要将 **configUSE_MUTEXES** 在**FreeRTOSConfig.h** 设置为1
 
## 二值信号量
### 创建二值信号量
#### 动态创建
    SemaphoreHandle_t xSemaphoreCreateBinary( void );

|参数/返回值|描述|
|----|---|
|NULL|因为可用 FreeRTOS 堆不足，所以无法创建信号量|
|Other|返回信号量的句柄|
##### Code Example

    SemaphoreHandle_t xSemaphore;

    void vATask( void * pvParameters )
    {
        xSemaphore = xSemaphoreCreateBinary();

        if ( xSemaphore == NULL )
        {
        }
        else
        {
        }
    }
#### 静态创建
    SemaphoreHandle_t xSemaphoreCreateBinaryStatic( StaticSemaphore_t *pxSemaphoreBuffer );

|参数/返回值|描述|
|----|---|
|pxSemaphoreBuffer|指向 **StaticSemaphore_t** 类型的变量，该变量将用于保存信号量的状态|
|NULL|因为可用 **pxSemaphoreBuffer** 为NULl ，所以无法创建信号量|
|Other|返回信号量的句柄|
##### Code Example
    SemaphoreHandle_t xSemaphore = NULL;
    StaticSemaphore_t xSemaphoreBuffer;

    void vATask( void * pvParameters )
    {
        xSemaphore = xSemaphoreCreateBinaryStatic(&xSemaphoreBuffer);
    }
## 计数信号量
### 创建计数信号量
#### 动态创建
    SemaphoreHandle_t xSemaphoreCreateCounting( UBaseType_t uxMaxCount, UBaseType_t uxInitialCount );
|参数/返回值|描述|
|----|---|
|uxMaxCount|可以达到的最大计数值|
|uxInitialCount|创建信号量时分配给信号量的计数值|
|NULL|因为保留信号量所需的 RAM 无法分配而无法创建信号量|
|Other|返回信号量的句柄|
##### Code Example
    void vATask( void * pvParameters )
    {
        SemaphoreHandle_t xSemaphore;

        xSemaphore = xSemaphoreCreateCounting( 10, 0 );

        if( xSemaphore != NULL )
        {
        }
    }
#### 静态创建
    SemaphoreHandle_t xSemaphoreCreateCountingStatic( UBaseType_t uxMaxCount, UBaseType_t uxInitialCount, StaticSemaphore_t *pxSemaphoreBuffer );
|参数/返回值|描述|
|----|---|
|uxMaxCount|可以达到的最大计数值|
|uxInitialCount|创建信号量时分配给信号量的计数值|
|pxSemaphoreBuffer|指向 **StaticSemaphore_t** 类型的变量，该变量将用于保存信号量的状态|
|NULL|因为保留信号量所需的 RAM 无法分配而无法创建信号量|
|Other|返回信号量的句柄|
##### Code Example
    static StaticSemaphore_t xSemaphoreBuffer;
    void vATask( void * pvParameters )
    {
        SemaphoreHandle_t xSemaphore;

        xSemaphore = xSemaphoreCreateCountingStatic( 10, 0, &xSemaphoreBuffer );

    }
## 互斥信号量
### 创建互斥信号量
#### 动态创建
    SemaphoreHandle_t xSemaphoreCreateMutex( void )
|参数/返回值|描述|
|----|---|
|NULL|因为保留信号量所需的 RAM 无法分配而无法创建信号量|
|Other|返回信号量的句柄|
##### Code Example
    SemaphoreHandle_t xSemaphore;

    void vATask( void * pvParameters )
    {
        xSemaphore = xSemaphoreCreateMutex();

        if( xSemaphore != NULL )
        {
        }
    }
#### 静态创建
    SemaphoreHandle_t xSemaphoreCreateMutexStatic( StaticSemaphore_t *pxMutexBuffer );
|参数/返回值|描述|
|----|---|
|pxMutexBuffer|指向 **StaticSemaphore_t** 类型的变量|
|NULL|**pxMutexBuffer** 为 NULL 而未创建互斥锁，则返回 NULL|
|Other|返回信号量的句柄|
##### Code Example
    SemaphoreHandle_t xSemaphore = NULL;
    StaticSemaphore_t xMutexBuffer;

    void vATask( void * pvParameters )
    {
        xSemaphore = xSemaphoreCreateMutexStatic( &xMutexBuffer );
    }


### 获取信号量
    xSemaphoreTake( SemaphoreHandle_t xSemaphore, TickType_t xTicksToWait );
|参数/返回值|描述|
|----|---|
|xSemaphore|信号量的句柄|
|xTicksToWait|阻塞时间|
|pdTURE|获取信号量成功|
|pdFALSE|信号量不可用|
##### Code Example
    SemaphoreHandle_t xSemaphore = NULL;
    void vATask( void * pvParameters )
    {
        xSemaphore = xSemaphoreCreateMutex();
    }
    void vAnotherTask( void * pvParameters )
    {
        if( xSemaphore != NULL )
        {

            if( xSemaphoreTake( xSemaphore, ( TickType_t ) 10 ) == pdTRUE )
            {
                xSemaphoreGive( xSemaphore );
            }
            else
            {
            }
        }
    }
### 释放信号量
    xSemaphoreGive( SemaphoreHandle_t xSemaphore );
|参数/返回值|描述|
|----|---|
|xSemaphore|信号量的句柄|
|pdTURE|释放信号量成功|
|pdFALSE|信号量不可用|
##### Code Example
    SemaphoreHandle_t xSemaphore = NULL;
    void vATask( void * pvParameters )
    {
        xSemaphore = xSemaphoreCreateMutex();

        if( xSemaphore != NULL )
        {
            if( xSemaphoreGive( xSemaphore ) != pdTRUE )
            {
            }
            if( xSemaphoreTake( xSemaphore, ( TickType_t ) 0 ) )
            {
                if( xSemaphoreGive( xSemaphore ) != pdTRUE )
                {
                }
            }
        }
    }
### 删除信号量
    void vSemaphoreDelete( SemaphoreHandle_t xSemaphore );
|参数/返回值|描述|
|----|---|
|xSemaphore|被删除的信号量的句柄|

# CMSIS - RTOS 封装
## 信号量
### 创建信号量
    osSemaphoreId_t osSemaphoreNew( uint32_t max_count, uint32_t initial_count,const osSemaphoreAttr_t * attr );	
### 释放信号量
    osStatus_t osSemaphoreRelease( osSemaphoreId_t semaphore_id)
### 获取信号量
    osStatus_t osSemaphoreAcquire( osSemaphoreId_t semaphore_id, uint32_t timeout )	
### 获取信号量名字
    const char * osSemaphoreGetName( osSemaphoreId_t semaphore_id)	
### 获取信号量计数值
    uint32_t osSemaphoreGetCount( osSemaphoreId_t semaphore_id )	
### 删除信号量
    osStatus_t osSemaphoreDelete( osSemaphoreId_t semaphore_id)	
#### Code Example
    osSemaphoreId_t sid_Semaphore;
    osThreadId_t tid_Thread_Semaphore;

    int Init_Semaphore( void )
    {
        sid_Semaphore = osSemaphoreNew(2, 2, NULL);
        if ( sid_Semaphore == NULL )
        {
        }
        tid_Thread_Semaphore = osThreadNew( Thread_Semaphore, NULL, NULL );
        if( tid_Thread_Semaphore == NULL )
        {
            return -1;
        }
        return 0;
    }
    void Thread_Semaphore (void *argument)
    {
        osStatus_t val;
        while (1)
        {
            val = osSemaphoreAcquire(sid_Semaphore, 10U); 
            switch (val)
            {
                case osOK:
                    osSemaphoreRelease(sid_Semaphore);             
                break;
                case osErrorResource:
                    break;
                case osErrorParameter:
                    break;
                default:
                    break;
            }
            osThreadYield();
        }
    }
## 互斥量
### 创建互斥量
    osMutexId_t osMutexNew(const osMutexAttr_t *attr)
### 获取互斥量的名字
    const char * osMutexGetName (osMutexId_t mutex_id)
### 获取互斥量
    osStatus_t osMutexAcquire(osMutexId_t mutex_id, uint32_t timeout)
### 释放互斥量
    osStatus_t osMutexRelease (osMutexId_t mutex_id)
### 获取互斥资源持有则
    osThreadId_t osMutexGetOwner (osMutexId_t mutex_id)
### 删除互斥量
    osStatus_t osMutexDelete (osMutexId_t mutex_id)

