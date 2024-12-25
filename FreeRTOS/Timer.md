# 软件定时器
创建和控制定时器以及定时器回调功能   
1. 使用软件定时器需要将在 **FreeRTOSConfig.h** 中的 **configUSE_TIMERS** 宏置1
2. 定时器是在休眠状态下创建的。
3. 软件定时器的超时回调函数是由软件定时器服务任务调用的，软件定时器的超时回调函数本身不是任务，因此不能在该回调函数中使用可能会导致任务阻塞的 API 函数。

|API|描述|
|----|----|
|xTimerCreate|动态创建定时器|
|xTimerCreateStatic|静态创建定时器|
|xTimerIsTimerActive|查询定时器状态|
|xTimerStart|开启定时器|
|xTimerStop|终止定时器|
|xTimerChangePeriod|改变定时器周期|
|xTimerDelete|删除定时器|
|xTimerReset|重置定时器|
|pvTimerGetTimerID|获取定时器ID|
|vTimerSetReloadMode|设置定时器重载模式|
|vTimerSetTimerID|设置定时器ID|
|pcTimerGetName|获取定时器名字|
|xTimerGetPeriod|获取定时器周期|

## 创建定时器
创建一个新的软件定时器实例， 并返回一个可以引用定时器的句柄。
### 动态创建
     TimerHandle_t xTimerCreate( const char * const pcTimerName,
                   const TickType_t xTimerPeriod,
                   const UBaseType_t uxAutoReload,
                   void * const pvTimerID,
                   TimerCallbackFunction_t pxCallbackFunction );
#### 参数
**pcTimerName**
- 定时器的名字    

**xTimerPeriod**
- 定时器的周期，以节拍为单位。可以调用 **pdMS_TO_TICKS()** 将以毫秒为单位的时间转换为以节拍为单位的时间。

**uxAutoReload** 
- 如果 uxAutoReload 设置为 pdTRUE， 那么定时器将以 xTimerPeriod 参数设置的频率重复过期。如果 uxAutoReload 设置为 pdFALSE，则此定时器为一次性定时器， 它会在到期后进入休眠状态。

**pvTimerID**
- 软件定时器 ID，用于多个软件定时器公用一个超时回调函数。

**pxCallbackFunction**
- 定时器到期时调用的函数。
#### 返回值
- 如果定时器创建成功， 则返回新创建的定时器的句柄。如果由于剩余的 FreeRTOS 堆不足以分配定时器结构体而无法创建定时器， 则返回 NULL。
## 查询定时器状态
    BaseType_t xTimerIsTimerActive( TimerHandle_t xTimer );
#### 参数
**xTimer**
- 被查询的定时器
#### 返回值
- 如果定时器处于休眠状态，将返回 **pdFALSE** 。
- 如果定时器处于活动状态，将返回 **pdFALSE** 以外的值。
## 开启定时器
     BaseType_t xTimerStart( TimerHandle_t xTimer, TickType_t xBlockTime );
#### 参数
**xTimer**
- 正在启动/重新启动的定时器的句柄。

**xBlockTime**
- 指定 在调用 **xTimerStart()** 时队列已满的情况下，调用任务处于阻塞状态以等待启动命令成功发送到定时器命令队列的时间（单位：滴答）。
#### 返回值
**pdFAIL**   
- 如果在以下情况下，启动命令无法发送至定时器命令队列，则返回 **pdFAIL**    

**pdPASS**   
- 如果能将此命令成功发送到定时器命令队列，则返回 **pdPASS**
## 终止定时器
     BaseType_t xTimerStop( TimerHandle_t xTimer, TickType_t xBlockTime );
#### 参数
**xTimer**
- 正在停止的定时器的句柄。

**xBlockTime**
- 指定 在调用 **xTimerStop()** 时队列已满的情况下，调用任务处于阻塞状态以等待启动命令成功发送到定时器命令队列的时间（单位：滴答）。
#### 返回值
**pdFAIL**   
- 如果在 xBlockTime 滴答已过之后仍无法向定时器命令队列发送删除命令，则返回 **pdFAIL**    

**pdPASS**   
- 如果能将此命令成功发送到定时器命令队列，则返回 **pdPASS**
## 更改定时器周期
     BaseType_t xTimerChangePeriod( TimerHandle_t xTimer, TickType_t xNewPeriod, TickType_t xBlockTime );
#### 参数
**xTimer**
- 待改变周期的定时器句柄。    

**xNewPeriod**
- 新周期   

**xBlockTime**
指定 在调用 **xTimerChangePeriod()** 时队列已满的情况下，调用任务处于阻塞状态以等待启动命令成功发送到定时器命令队列的时间（单位：滴答）
#### 返回值
**pdFAIL**   
- 如果在 xBlockTime 滴答已过之后仍无法向定时器命令队列发送删除命令，则返回 **pdFAIL**    

**pdPASS**   
- 如果能将此命令成功发送到定时器命令队列，则返回 **pdPASS**
## 删除定时器
     BaseType_t xTimerDelete( TimerHandle_t xTimer, TickType_t xBlockTime );
#### 参数
**xTimer**
- 正在删除的定时器的句柄。    

**xBlockTime**
指定 在调用 **xTimerDelete()** 时队列已满的情况下，调用任务处于阻塞状态以等待启动命令成功发送到定时器命令队列的时间（单位：滴答）
#### 返回值
**pdFAIL**   
- 如果在 xBlockTime 滴答已过之后仍无法向定时器命令队列发送删除命令，则返回 **pdFAIL**    

**pdPASS**   
- 如果能将此命令成功发送到定时器命令队列，则返回 **pdPASS**
## 重置定时器
     BaseType_t xTimerReset( TimerHandle_t xTimer, TickType_t xBlockTime );
**xTimer**
- 正在重置/启动/重新启动的定时器的句柄。    

**xBlockTime**
指定 在调用 **xTimerReset()** 时队列已满的情况下，调用任务处于阻塞状态以等待启动命令成功发送到定时器命令队列的时间（单位：滴答）
#### 返回值
**pdFAIL**   
- 如果在 xBlockTime 滴答已过之后仍无法向定时器命令队列发送删除命令，则返回 **pdFAIL**    

**pdPASS**   
- 如果能将此命令成功发送到定时器命令队列，则返回 **pdPASS**
## 获取软件定时器ID
     void *pvTimerGetTimerID( TimerHandle_t xTimer );
#### 参数
**xTimer**
- 正在查询的定时器的句柄。
#### 返回值
- 分配给被查询的定时器的 ID。
## 设置定时器重载模式
      void vTimerSetReloadMode( TimerHandle_t xTimer, const UBaseType_t  uxAutoReload );
将软件定时器的“模式”更新为自动重新加载定时器或一次性 定时器。
- 自动重新加载定时器每次过期都会自行重置，从而导致定时器定期到期（并因此执行其回调）
- 一次性定时器不会自动重置，因此除非手动重新启动，否则只会过期一次（并因此执行其回调）
#### 参数
**xTimer**
- 要更新的定时器的句柄。

**uxAutoReload**
- **pdTRUE** 为周期模式，**pdFALSE** 为单次模式。
## 设置定时器ID
     void vTimerSetTimerID( TimerHandle_t xTimer, void *pvNewID );
#### 参数
**xTimer**
- 要设置ID的定时器的句柄。

**pvNewID**
- 定时器新的标识符
## 获取定时器名字
     const char * pcTimerGetName( TimerHandle_t xTimer );
#### 参数
**xTimer**
- 待查询的定时器的句柄。
#### 返回值
- 指向定时器文本名称的指针
## 获取定时器周期
     TickType_t xTimerGetPeriod( TimerHandle_t xTimer );
#### 参数
**xTimer**
- 待查询的定时器的句柄。
#### 返回值
- 定时器的周期，以节拍为单位
## 获取定时器重载模式
     BaseType_t  xTimerGetReloadMode( TimerHandle_t xTimer );
     UBaseType_t uxTimerGetReloadMode( TimerHandle_t xTimer );
#### 参数
**xTimer**
- 待查询的定时器的句柄。
#### 返回值
- 如果为周期定时器则返回 **pdTURE**, 否则返回 **pdFALSE**