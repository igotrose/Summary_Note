# 单链表的基本操作

## 单链表的结构
    typedef struct SingleLinkedList 
    {
        struct SingleLinkedList* next;  // 地址域
        int element;                    // 数据域
    }SLL;
链表的一个节点包含了数据域和地址域，数据域存放地址，地址域存放下一个节点的地址。 为了方便，将结构体类型重命名了 
## 单链表的表头
    SLL* CreatHeader()
    {
        SLL* p = malloc(sizeof(SLL));
        if (p == NULL)
        {
            perror("p:");       // 判断空间是否申请成功
            exit(1);            
        }
        p->next = NULL;
        return p;
    }
这是单链表表头的创建，定义并开辟一个结构体指针，因为是表头并且没有任何东西元素，所以需要将表头的节点指向NULL。

## 单链表的空表判断
    void JudgeIsEmpty(SLL* header)
    {
        assert(header);
        if (header->next == NULL)
        {
            printf("this is an empty single linked list\n");
        }
        else
        {
            printf("this isn't an empty single linked list\n");
        }
    }
这是单链表的空表判断，如果表头的数据域指向NULL，说明这个单链表为空。

## 单链表的头插
    void InsertFront(SLL* header, int x)      
    {
        assert(header);
        SLL* tmp = (SLL*)malloc(sizeof(SLL));
        if (tmp == NULL)
        {
            perror("p:");   
        }
        tmp->element = x;
        tmp->next = header->next;
        header->next = tmp;
    }
这是单链表的头插操作，函数需要传入表头指针和想要插入的元素，创建一个交换节点，对其数据域赋值，然后把交换节点更新为表头。

## 单链表的尾插
    void InsertTail(SLL* header, int x)
    {
        assert(header);
        SLL* tmp = (SLL*)malloc(sizeof(SLL));
        if(tmp == NULL)
        {
            perror("tmp:");
            exit(1);
        }
        tmp->element = x;
        tmp->next = NULL;
        SLL* p = header;
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = tmp;
    }
这是链表的尾插操作，需要在链表尾部创建一个临时节点，然会使用创建一个结构体指针将整个链表的和临时节点进行链接。

## 单链表的查询
    SLL* Find(SLL* header, int x)
    {
        assert(header);
        SLL* p = header->next;
        while (p != NULL && p->element != x)
        {
            p = p->next;
        }
        return p;
    }
这是单链表的查询操作，传入表头指针和需要查询的元素，遍历链表，找到返回需要查询的元素的地质域，没找到返回NULL。

## 单链表的删除
    void Delete(SLL* header, int x)
    {
        assert(header);
        SLL* p = Find(header, x);
        SLL* pre = header;
        while (pre->next != p)
        {
            pre = pre->next;
        }
        if (p != NULL)
        {
            pre->next = p->next;
            free(p);
        }
        else
        {
            printf("the element you want to delete is not exist!\n");
        }
    }
这是单链表的删除操作，需要找到要删除的节点，和前置节点。将前置节点的地址域赋值为删除节点的地址域，并释放内存。

## 单链表的修改
    void Modify(SLL* header, int x, int y)
    {
        assert(header);
        SLL* p = header;
        while(p != NULL)
        {
            if (p->element == x)
            {
                p->element = y;
                break;
            }
            else
            {
                p = p->next;            
            }
        }
    }
这是单链表的修改，遍历链表找到想要修改的元素，修改赋值。

## 单链表的打印
    void PrintList(SLL* header)
    {
        assert(header);
        SLL* p = header->next;
        while (p != NULL)
        {
            printf("%d ", p->element);
            p = p->next;
        }
        printf("\n");
    }
这是单链表的打印，遍历打印没啥好说。