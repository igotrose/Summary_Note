#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>

typedef struct ExpressionTreeNode
{
    char st;
    struct ExpressionTreeNode* left;
    struct ExpressionTreeNode* right; 
}ETN;

typedef struct Stack 
{
    struct Stack* next;
    ETN* node;
}Stack;

Stack* CreateStack()
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    assert(stack);
    stack->next = NULL;
    return stack;
}

void Push(Stack* root, ETN* node)
{
    assert(root);
    Stack* p = root;
    while (p->next != NULL)
    {
        p = p->next;
    }
    Stack* tmp = (Stack*)malloc(sizeof(Stack));
    assert(tmp);
    tmp->next = NULL;
    tmp->node = node;
    p->next = tmp;
}

ETN* Pop(Stack* root)
{
    assert(root);
    Stack* pre = root;
    Stack* p = root;
    while (p->next != NULL)
    {
        p = p->next;
    }
    while (pre->next != p)
    {
        pre = pre->next;
    }
    ETN* node = p->node;
    pre->next = NULL;
    free(p);
    return node;
}

ETN* CreateETN(char data)
{
    ETN* node = (ETN*)malloc(sizeof(ETN));
    node->st = data;
    node->left = node->right = NULL; 
    return node;
}

ETN* BuildPostfixExpressionTree(char* posfix)
{
    Stack* s = CreateStack();
    int index = 0;
    while (posfix[index] != '\0')
    {
        if (posfix[index] != '\0' && (posfix[index] == '+' || posfix[index] == '-' || posfix[index] == '*' || posfix[index] == '/' ))
        {
            ETN* tmp = CreateETN(posfix[index++]);
            ETN* last = Pop(s);
            ETN* front = Pop(s);
            tmp->left = front;
            tmp->right = last;
            Push(s, tmp);
        }
        else
        {
            Push(s, CreateETN(posfix[index++]));
        }
    }
    ETN* root = Pop(s);
    free(s);
    return root;
}

void PostOrder(ETN* root)
{
    if (root == NULL)
    {
        return;
    }
    PostOrder(root->left);
    PostOrder(root->right);
    printf("%c", root->st);
    
}

int main()
{
    char posfix[] = "abc*+de*f+g*+"; 
    char infix[] = "a+b*c+d*e+f*g";
    char prefix[] = "++a*bc*+*defg";
    ETN* postfix = BuildPostfixExpressionTree(posfix);
    PostOrder(postfix);
    return 0;
}