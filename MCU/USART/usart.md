# USART 
USART：**universal synchronous asynchronous receiver transmitter**， 通用同步异步接收机发送机   
## USART 框图
![alt text](<USART block diagram.png>)    
接口通过三个pin连接外部设备通信，任何USART双向通信至少需要两个pin:接收数据(RX)和发送数据(TX)    
### 异步模式 
**RX**：接收数据输入是串行数据输入   
**TX**：发送数据输出。当发送机被禁止时，该引脚返回他的I/O端口配置；当发送机使能时并且没有发送数据时，该引脚处于高电平状态。再单总线和智能卡模式下，该I/O被用于接收和发送数据。（在USART，使用SW_RX接收数据）    
通过这些引脚，在USART模式下，串行数据接收和发送框架如下：   
1. 传输或接收前的空闲线
2. 一个开始位
3. 一个最不重要的数据字 **(8、9-bit)**
4. 帧完成时的停止位 **(0.5、1、1.5、2-bit)**   
5. 接口使用一个小数波特率生成器 **(12-bit mantissa and 4-bit fraction)**
6. 一个状态寄存器 **(USART_SR)**
7. 一个波特率寄存器 **(USART_BRR)**
8. (智能卡模式下)一个监护时间寄存器 **(USART_GTPR)**   

### USART 字符描述
可通过**USART_CR1**寄存器编程字长，可选8或9位长    
**TX**引脚在开始位时为低电平，在停止位时为高点平      
![alt text](<Word length programming.png>)    
空闲字符是被解释全为**1**的完整数据帧(包括停止位)，随后是下一数据帧的开始位和包含数据    
中断字符是在数据帧周期，被解释全为**0**的完整数据帧，在中断字符的末尾处，发送器会插入一位或两位长停止位去获取开始位    
### 发送器
当**TE**位被置1，在移位寄存器的数据通过**TX**引脚传输并且**SCLK**输出相应的时钟脉冲。当该位使能时，会发送一个空闲数据帧。在数据传输期间，不能重置该位，否则会使数据传输出错，因为波特率计数器被冻结了。发出的数据也将丢失   
#### 字符传输
在USART传输模式下，首先通过**TX**引脚发出最不重要的位。在这个模式下，**USART_DR**寄存器包含了一个内部总线和发送移位寄存器的缓冲区。    
每个字符之前都有一个开始位，这是一个为周期的逻辑级别。这个字符可以配置停止位数终止    
#### 配置停止位
停止位数的设置可以在**USART_CR2**寄存器的第13，12位进行编程设置         
1. **1 stop bit:** 默认停止位数
2. **2 stop bits:** 支持USART、单总线和调制解调器模式
3. **0.5 stop bit:** 用于智能卡模式下接收数据   
4. **1.5 stop bits** 用于智能卡模式下发送和接收数据   

![alt text](<Configurable stop bits.png>)
**流程**   
1. 通过向**USART_CR1**寄存器的**UE**位写入1使能USART   
2. 在**USART_CR1**寄存器的**M**位定义字长    
3. 在**USART_CR2**寄存器编写停止位   
4. 如果使用多通道通信，在**USART_CR3**寄存器选择启用DMA(**DMAT**)，按照多通道通信所述配置DMA的寄存器  
5. 通过**USART_BRR**寄存器选择期望波特率    
6. 第一次传输时，设置**USART_CR1**寄存器的**TE**位发送一个空闲数据帧   
7. 向**USART_DR**寄存器写入要发送的数据(这会将TXE位清除)，对于单个缓冲区每个数据需要重复这样去操作   
8. 再将数据写入**USART_DR**寄存器后，等待直到最后一个数据帧传输完成(**TC=1**)
#### 单个字节通信
清楚**TXE**位总是通过写入数据寄存器来执行   
**TXE**位通过硬件设置，并且他预示着：
1. 数据已经从**TDR**寄存器移动至移位寄存器并且已经开始传输   
2. **TDR**寄存器是空的
3. 下一个数据会被写入**USART_DR**寄存器，不会覆盖先前的数据      

如果**TXEIE**位被设置，将会产生中断    
当传输发生时，对**USART_DR**寄存器的写入指令将数据存储到**TDR**寄存器，并在传输结束时被复制到移位寄存器     
当没有传输发生时，对**USAER_DR**寄存器的写入指令直接将数据放置在移位寄存器，传输开始，**TXE**位会被立即设置      
如果一个数据帧被发送(停止位之后)并且**TXE**位被设置，**TC**位变高，如果在**USART_CR1**寄存器设置了**TXIC**位，中断将会发生     
在向**USART_DR**寄存器写入最后一个数据之后，在禁用USART或者造成微控制器进入低功耗模式，需要强制等待到**TC=1**
一下操作**TC**位会被清除
1. 读取**USART_SR**寄存器
2. 写入**USART_DR**寄存器 
![alt text](<TC or TXE behavior when transmitting.png>)
### 接收器
#### 起始位检测
当特定序列被识别时，起始位将会被检测        
该序列是 **1 1 1 0 X 0 x 0 x 0 0 0 0**    
![alt text](<Start bit detection when oversampling.png>)
#### 字符接收   
在USART接收模式下，首先通过**RX**引脚发出最不重要的位。在这个模式下，**USART_DR**寄存器包含了一个内部总线和接收移位寄存器的缓冲区。      
**当字符被接收**    
1. **RXNE**位被设置，这意味着移位寄存器的内容转移到了**RDR**寄存器。换言之，数据已经接收并且可以读   
2. 如果**RXNEIE**位被设置，中断会产生
3. 如果数据帧在接收期间检测到错误，噪声，溢出，错误标志可以设置
4. 多缓冲区，在每个字节被接收后**RXNE**会被设置，并且被DMA督导数据寄存器后清除
5. 单缓冲区模式下，通过软件读取**USART_DR**寄存器清除**RXNE**位。也可以向改位写入**0**清除，必须在下一个字符结束前**RXNE**位必须清除避免造成一处错误    

在接收数据期间**RE**位不能重置。如果在接收期间，**RE**位被禁用，当前字节的数据接收会被停止    
#### 溢出错误
当一个字符被接受且**RXNE**位没被重置时，溢出错误将会发生。数据不能从移位寄存器移动到**RDR**寄存器直到**RXNE**位被清除
 