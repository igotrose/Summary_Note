# 数组

## 柔性数组

柔性数组通常指的是在结构体中定义一个具有可变长度的数组，这个数组的长度是在运行时确定的，而且其长度必须是结构体的最后一个成员。  
使用柔性数组可以实现一种更灵活的内存布局，允许动态调整数组的大小。

#### 柔性数组定义声明 
    typedef struct FlexibleArray
    {
        int length;
        int data[]; // 柔性数组
    }FA;
#### 柔性数组创建
    FA* CreateFA(int length)
    {   
        FA* fa = (FA*)malloc(sizeof(FA) + length * size(int));
        assert(fa);
        fa->length = length;
        return fa;
    }
    // 在分配内存时，因sizeof只返回结构体的大小并没有计算柔性数组的大小，所以要添加柔性数组的大小
    
## 动态数组