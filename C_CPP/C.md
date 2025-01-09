## C笔面试题   
#### 1.指针
    char *const *(*next)();
1. **(*next)**-->next是一个指针 
2. **(*next)()**-->next是个函数指针
3. **char \*const** -->是一个不可修改常量指针

next 是一个函数指针，指向一个没有参数的函数，并且该函数的返回值是一个指针，该指针指向不可修改的字符指针 **char \*const**
#### 2. 函数指针数组
    char *(*c[10])(int **p);
1. *c[10]*:c 是一个数组，包含 10 个元素。数组的每个元素都是一个指针。
2. (*c[10]):表示数组中的每个元素是一个指向函数的指针。
3. (int **p):每个函数指针所指向的函数的参数是一个 int **p，即函数的参数是一个指向 int * 类型的指针（也就是一个指向整数指针的指针）。
4. char *:每个函数指针指向的函数的返回值是一个 char *，即返回一个指向字符的指针。

c 是一个 函数指针数组，数组中的每个函数指针指向的函数有一个参数 int **p，并返回一个 char * 类型的指针
#### 3. 字符串常量
    char *s = "AAA";
    printf("%s", s);
    s[0] = 'B'
    printf("%s", s);
1. **”AAA“** 是一个字符串常量，放在只读区，不能被修改
#### 4. 访问指定内存地址
要求设置一绝对内存地址为0x40020800的位置，将该地址里面的内容设置为整型值0x3456，编写一段代码完成

    1.
    int *pt;
    pt = (unsigned long *)0x40020800;
    *pt = 0x3456
    2.
    #define ADDR (*(volatile unsigned long *)0x40020800)
    ADDR = 0x3456
#### 5. #define 对比 typedef
    #define DPS struct s *
    typedef struct s * TPS; 

1. DPS p1; --> struct s *p1   
   TPS p2;
2. DPS p1, p2; --> struct s * p1, p2; --> p1是结构体指针, p2是结构体s的对象
   TPS p3, p4;   

**#define**是预处理指令，对文本进行替换    
**typedef**是起别名
在同时定义多个变量时，由于要考虑符号优先级的问题，**typedef**会更加适用
#### 6.函数返回局部变量地址的问题
    #include <stdio.h>
    char *get_str(void);
    int main(void)
    {
        char *p = get_str();            // 栈
        printf("%s\n", p);
        return 0;
    }
    char *get_str(void)
    {
        char str[] = {"abcd"};          // 栈
        return str;
    }
**get_str**这个函数返回一个局部变量的指针,    
**str**数组, 内容常量 **"abcd"** 常量 **"abcd"** 放置在只读区域,     
而数组是存储在栈上的, 程序结束后占空间会被回收, 返回的指针将会是野指针
#### 7.无符号整型和有符号整型相加
    #include <stdio.h>
    int main(void)
    {
        unsigned int a = 6;
        int b = -20;
        (a + b > 6) ? puts(">6) : puts("<=6")
    }

1. 隐式类型转换
2. 数字以补码的形式在内存中存储
#### 8.大小端模式以及代码判别
    #include "stdio.h"

    int main(void)
    {
        union Test
        {
            unsigned int n;
            char arr[4];
        };

        union Test num;
        num.n = 0x12345678;
        for (int i = 0; i < 4; i++)
            printf("&arr[%d] = %p, arr[%d] = %#x\n", i, &num.arr[i], i, num.arr[i]);
        return ;
    }
**大端模式**：数据的低位放在内存高地址中，数据的高位放在内存低地址中     
**小端模式**：数据的低位放在内存低地址中，数据的高位放在内存高地址中     








## Notes
    1. 符号结合性：右左原则
