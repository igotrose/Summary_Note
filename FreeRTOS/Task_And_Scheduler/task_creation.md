# FreeRTOS的任务创建和删除

## FreeRTOS API函数
任务的创建和删除本质就是调用Free RTOS的API函数    

|API函数|描述|
|--------|------|   
|xTaskCreate()|动态方式创建任务|
|xTaskCreateStatic()|静态方式创建任务|
|vTaskDelete()|删除任务|

**动态创建任务:** 任务的任务控制块(**TCB**)以及任务的栈空间所需的内存，均由FreeRTOS从FreeRTOS
管理的堆中分配    
**静态创建任务:** 任务的任务控制块(**TCB**)以及任务的栈空间所需的内存，需要用户分配提供      
任务创建成功后会立刻进入就绪态，由任务调度器调度运行   

### 任务句柄
    TaskHandle_t
任务引用的类型。例如，调用 **xTaskCreate**（通过指针参数） 返回 **TaskHandle_t** 变量，然后可以将该变量用作 **vTaskDelete** 的参数来删除任务。
### 线程句柄 - CMSIS-RTOS封装
    osThreadId_t
线程引用的类型。例如，调用 **osThreadNew**（通过指针参数） 返回 **osThreadId_t** 变量，然后可以将该变量用作 **osThreadTerminate** 的参数来删除任务。

### 任务控制块结构体成员
    typedef struct tskTaskControlBlock
    {
        volatile StackType_t        *pxTopOfStack;                      /* 任务栈栈顶，必须为TCB的第一列表项 */
        ListItem_t                  xStateListItem;                     /* 任务状态列表项 */
        ListItem_t                  xEventListItem;                     /* 任务事件列表项 */
        UBaseType_t                 uxPriority;                         /* 任务优先级，数值越大，优先级越高 */
        StackType_t                 *pxStack;                           /* 任务栈起始地址 */
        char                        pcTackName[configMAX_TASK_NAME_LEN];/* 任务名字 */
        ... 
        省略很多条件编译的成员
    }takTCB;
任务栈栈顶，在任务切换时的任务上下文保存、任务恢复息息相关  
### 线程属性结构体成员 - CMSIS-RTOS封装
    typedef struct 
    {
        const char                   *name;   // 任务的名字，主要用于调试和任务的识别
        uint32_t                 attr_bits;   // 属性位，用于配置任务的特殊属性
        void                      *cb_mem;    // 控制块的内存指针
        uint32_t                   cb_size;   // 控制块内存的大小（字节）
        void                   *stack_mem;    // 任务堆栈的内存指针
        uint32_t                stack_size;   // 任务堆栈的大小（字节）
        osPriority_t              priority;   // 任务的初始优先级
        TZ_ModuleId_t            tz_module;   // TrustZone 模块标识符
        uint32_t                  reserved;   // 保留字段，必须设为0
    } osThreadAttr_t;

**Note**
1. 如果进行静态任务创建，则需要提供控制块**cb_mem**的内存, **stack_mem** 指向任务堆栈的预分配内存空间
2. 在动态创建任务时可以设置为，**cb_mem** 可以为NULL，由RTOS自动分配控制块，**stack_mem** 可以为NULL，由RTOS自动分配任务栈堆


### 创建任务函数
#### 动态创建任务函数
    BaseType_t xTaskCreate
    (
        TaskFunction_t                  pxTaskCode,   /* 指向任务函数的指针 */
        const char *const               pcName,       /* 任务名字，最大长度configMAX_TASK_NAME_LEN */
        const configSTACK_DEPTH_TYPE    usStackDepth, /* 任务栈堆大小，单位为字 */
        void *const                     pvParameters, /* 传递给任务函数的参数 */
        UBaseType_t                     uxPriority,   /* 任务优先级，范围：0~configMAX_PRIORITIES - 1 */
        TaskHandle_T *const             pxCreatedTask /* 任务句柄，就是任务控制块 */
    );
任务创建成功返回**pdPASS**，任务创建失败返回**errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY**
##### 实现动态创建任务流程
使用步骤：  
1. 将宏**configSUPPORT_DYNAMIC_ALLOCATION**配置为1
2. 定义函数入口参数
3. 编写任务函数     
  
动态创建任务函数的内部实现   
1. 申请栈堆内存&任务控制块内存
2. TCB结构体成员赋值
3. 添加新任务到就绪列表中      
        
**demo**

    void vTaskCode( void * pvParameters )
    {
        configASSERT( ( ( uin32_t ) pvParameters) == 1);
        while(1)
        {
            ;
        }
    }
    void vOtherFunction(void)
    {
        BaseType_t xReturned;
        TaskHandle_t xHandle = NULL;
        xReturned = xTaskCreate(vTaskCode, "NAME", STACK_SIZE, ( void * )1, tskIDLE_PRIORITY, &xHandle);
        if( xReturn == pdPass )
        {
            vTasKDelete( xHandle );
        }
    }
    
### 静态创建任务函数
    BaseType_t xTaskCreateStatic
    (
        TaskFunction_t                  pxTaskCode,     /* 指向任务函数的指针 */
        const char *const               pcName,         /* 任务名字，最大长度configMAX_TASK_NAME_LEN */
        const configSTACK_DEPTH_TYPE    usStackDepth,   /* 任务栈堆大小，单位为字 */
        void *const                     pvParameters,   /* 传递给任务函数的参数 */
        UBaseType_t                     uxPriority,     /* 任务优先级，范围：0~configMAX_PRIORITIES - 1 */
        StackType_t* const              puxStackBuffer, /* 任务对战，一般为数组，由用户分配 */
        StaticTask_t* const             pxTaskBuffer    /* 任务控制块指针，由用户分配 */
    )
任务创建失败，用户没有提供响应的内存，返回**NULL**，任务创建成功返回任务句柄
#### 实现静态创建任务流程
使用步骤：  
1. 将宏**configSUPPORT_STATIC_ALLOCATION**配置为1
2. 定义空闲任务和定时器任务的任务堆栈及TCB
3. 定义**vApplicationGetIdleTaskMemory()** 和 **vApplicationTimerTaskMemory()** 接口函数
4. 定义函数入口参数
5. 编写任务函数     

静态创建任务函数的内部实现  
1. TCB结构体成员赋值
2. 添加新任务到就绪列表中
    
**demo**

    #define STACK_SIZE 200
    StaticTask_t xTaskBuffer;
    StackType_t xStack[ STACK_SIZE ];
    void vTaskCode( void * pvParameters )
    {
        configASSERT( ( ( uin32_t ) pvParameters) == 1);
        while(1)
        {
            ;
        }
    }
    void vOtherFunction(void)
    {
        TaskHandle_t xHandle = NULL;
        xHandle = xTaskCreateStatic(vTaskCode, "NAME", STACK_SIZE, ( void * )1, tskIDLE_PRIORITY, xStack, &xTaskBuffer);
        if( xReturn == pdPass )
        {
            vTasKDelete( xHandle );
        }
    }
#### 创建线程函数 - CMSIS-RTOS封装
    osThreadId_t osThreadNew(osThreadFunc_t	func, void *argument, const osThreadAttr_t *attr)	
|形参|描述|
|----|----|
|func|任务的函数|
|argument|任务的参数|
|attr|任务的属性|    

### 任务删除函数
    void vTaskDelete(TaskHandle_t xTaskToDelete);
|形参|描述|
|----|---|
|xTaskToDelete|待删除任务的任务句柄|        

用于删除已被创建的任务，被删除的任务将从就绪任务列表、阻塞态任务列表、挂起态任务列表和事件列表中移除    
**注意！**
1. 当传入参数为NULL，则代表删除任务自身（当前正在运行的任务）
2. 空闲任务会负责释放被删除任务中由系统分配的内存，但是由用户在任务删除前申请的内存，需要由用户在任务被删除前提前释放，否则导致内存泄漏
#### 删除任务流程
使用步骤：
1. 使用删除任务函数，需要就宏**INCLUDE_vTaskDelete**配置为1
2. 入口参数输入需要删除的任务句柄（NULL代表删除自身）   

删除任务函数的内部实现
1. 获取所要删除的任务控制块
2. 将要被删除任务，移除所在列表
3. 判断所需要删除的任务
4. 更新下一个任务的阻塞事件
### 删除任务函数 - CMSIS-RTOS封装
    osStatus_t osThreadTerminate(osThreadId_t thread_id)
|形参|描述|
|----|----|
|thread_id|任务的句柄|



