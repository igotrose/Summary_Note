# 内核控制
### taskYIELD
    #define taskYIELD()					portYIELD()
**taskYIELD()** 用于请求切换上下文到另一个任务, 但是如果没有其他任务的优先级高于等于调用 **taskYIELD()** 的任务，则RTOS调度器将只选择调用 **taskYIELD()** 的任务, 使其再次运行。    
如果 **configUSE_PREEMPTION** 设置为 1，则 RTOS 调度器将始终运行能够运行的最高优先级任务， 因此调用 **taskYIELD()** 始终不会切换到更高优先级的任务。

### taskDISABLE_INTERRUPTS() & taskENABLE_INTERRUPTS()
    #define taskDISABLE_INTERRUPTS()	portDISABLE_INTERRUPTS()
    #define taskENABLE_INTERRUPTS()		portENABLE_INTERRUPTS()
如果接口使用 **configMAX_SYSCALL_INTERRUPT_PRIORITY** 或 **configMAX_API_CALL_INTERRUPT_PRIORITY** 常量，那么 **taskDISABLE_INTERRUPTS()** 将禁用所有中断，或者在设置 **configMAX_SYSCALL_INTERRUPT_PRIORITY** 之前禁用所有中断。    
如果接口不使用 **configMAX_API_CALL_INTERRUPT_PRIORITY** 常量，那么 **taskDISABLE_INTERRUPTS()** 将对所有可屏蔽中断进行全局禁用。    
通常情况下不会直接调用该宏， 而应使用 **taskENTER_CRITICAL()** and **taskEXIT_CRITICAL()** 。
### taskENTER_CRITICAL() & taskEXIT_CRITICAL()
    #define taskENTER_CRITICAL()		portENTER_CRITICAL()
    #define taskEXIT_CRITICAL()			portEXIT_CRITICAL()
通过调用 **taskENTER_CRITICAL()** 进入临界区，随后通过调用 **taskEXIT_CRITICAL()** 退出临界区。     
宏 **taskENTER_CRITICAL()** 和 **taskEXIT_CRITICAL()** 提供了一个基本临界区实现，只需禁用中断即可使其全局运作，或在特定的中断优先级范围内运作。   
1. 临界区必须尽量简短，否则会对中断响应时间产生不利影响。 
2. 每次调用 **taskENTER_CRITICAL()** 时，都必须有对应的 **taskEXIT_CRITICAL()** 调用。    
3. 不得从临界区调用 FreeRTOS API 函数   
4. 不得从中断服务程序 (ISR) 调用 **taskENTER_CRITICAL()** 和 **taskEXIT_CRITICAL()**

**Demo**    

        void vDemoFunction( void )
        {
            taskENTER_CRITICAL();

            taskEXIT_CRITICAL();
        }

        void vTask1( void * pvParameters )
        {
            for( ;; )
            {

                taskENTER_CRITICAL();

                vDemoFunction();

                taskEXIT_CRITICAL();
            }
        }
### taskENTER_CRITICAL_FROM_ISR() & taskEXIT_CRITICAL_FROM_ISR()
    UBaseType_t taskENTER_CRITICAL_FROM_ISR( void );
    void taskEXIT_CRITICAL_FROM_ISR( UBaseType_t uxSavedInterruptStatus );

在 ISR 中，通过调用 **taskENTER_CRITICAL_FROM_ISR()** 进入临界区， 然后通过调用 **taskEXIT_CRITICAL_FROM_ISR()** 退出。    
**taskENTER_CRITICAL_FROM_ISR()** 和 **taskEXIT_CRITICAL_FROM_ISR()** 宏提供了 一种基本的临界区实现，工作原理是通过简单地禁用中断，可以是全局禁用，也可以是禁用到特定的中断优先级。


**DemoISR**

        void vDemoFunction( void )
        {
            UBaseType_t uxSavedInterruptStatus;

            uxSavedInterruptStatus = taskENTER_CRITICAL_FROM_ISR();

            taskEXIT_CRITICAL_FROM_ISR( uxSavedInterruptStatus );
        }

        void vDemoISR( void )
        {
            UBaseType_t uxSavedInterruptStatus;

            uxSavedInterruptStatus = taskENTER_CRITICAL_FROM_ISR();

            vDemoFunction();

            taskEXIT_CRITICAL_FROM_ISR( uxSavedInterruptStatus );
        }
**uxSavedInterruptStatus** 作为 **taskENTER_CRITICAL_FROM_ISR()**的返回值，也作为 **taskEXIT_CRITICAL_FROM_ISR()**的唯一参数，代表中断掩码状态。   
### vTaskStartScheduler() & vTaskEndScheduler()
    void vTaskStartScheduler( void );
    void vTaskEndScheduler( void );
启动 RTOS 调度器。调用后，RTOS 内核可以控制在何时执行哪些任务，空闲任务和定时器守护进程任务（可选）会在 RTOS 调度器启动时自动创建。        
**vTaskStartScheduler()** 仅在以下情况下返回：没有足够的 RTOS 堆 可用来创建空闲或定时器守护进程任务。    
所有 RTOS 演示应用程序项目都包含使用 **vTaskStartScheduler()** 的示例，通常在 **main.c** 中的 **main()** 函数中使用。         
停止 RTOS 内核滴答。所有已创建的任务将自动删除，多任务处理 （无论是抢占式还是协作式）亦将停止。执行将从调用 **vTaskStartScheduler()** 的位置恢复， 就像 **vTaskStartScheduler()** 刚刚返回一样。       
**Demo**      

    void vTaskCode( void * pvParameters )
    {
        for( ;; )
        {
            vTaskEndScheduler ();
        }
    }

    void vAFunction( void )
    {
        xTaskCreate( vTaskCode, "NAME", STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );

        vTaskStartScheduler();

    }
### vTaskSuspendAll() & vTaskResumeAll()
    void vTaskSuspendAll( void );
    BaseType_t xTaskResumeAll( void );
挂起调度器。挂起调度器会阻止上下文切换， 但会让中断处于启用状态。如果调度器被挂起时，中断请求切换上下文， 那么请求将会被挂起。而且只有在调度器恢复（取消挂起）时才会执行。    
在以下情况下调用 **xTaskResumeAll()** 会转换调度器的状态，取消其阻塞状态：在**vTaskSuspendAll()**  之后调用。     
对 **vTaskSuspendAll()** 的调用可以嵌套。调用 **xTaskResumeAll()** 的次数必须与先前调用 **vTaskSuspendAll()** 的次数相同，然后调度器将取消挂起状态并重新进入活动状态。      
**xTaskResumeAll()** 只能在正在执行的任务中调用，因此不能在调度器处于初始化状态时（启动调度器之前）调用。     
不得在调度器挂起时调用其他 FreeRTOS API 函数。     
**Demo**

    void vDemoFunction( void )
    {
        vTaskSuspendAll();

        xTaskResumeAll();
    }
    void vTask1( void * pvParameters )
    {
        for( ;; )
        {
            vTaskSuspendAll();

            vDemoFunction();

            if( xTaskResumeAll() == pdTRUE )
            {
            }
            else
            {
             }
        }
    }
