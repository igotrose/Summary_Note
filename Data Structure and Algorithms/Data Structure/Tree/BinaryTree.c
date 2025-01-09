#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef struct BinaryTreeNode
{
    int element;
    struct BinaryTreeNode* left;
    struct BinaryTreeNode* right;
}BTN;

BTN* CreateBTN(int element)
{
    BTN* t = (BTN*)malloc(sizeof(BTN));
    assert(t);
    t->element = element;
    t->left = NULL;
    t->right = NULL;
    return t;
}

void PreOrder(BTN* root)
{
    if (root == NULL)
        return;
    printf("%d ", root->element);
    PreOrder(root->left);
    PreOrder(root->right);    
}

void InOrder(BTN* root)
{    
    if (root == NULL)
        return;
    InOrder(root->left);
    printf("%d ", root->element);
    InOrder(root->right); 
}

void PostOrder(BTN* root)
{    
    if (root == NULL)
        return;
    PostOrder(root->left);
    PostOrder(root->right); 
    printf("%d ", root->element);
}

typedef struct TreeQuene
{
    BTN* data;
    struct TreeQuene* next;
}TQ;

TQ* CreateTQ()
{
    TQ* header = (TQ*)malloc(sizeof(TQ));
    assert(header);
    header->next = NULL;
    return header;
}

void push(TQ* header, BTN* node)
{
    assert(header && node);
    TQ* p = header;
    while (p->next != NULL)
        p = p->next;
    TQ* tmp = (TQ*)malloc(sizeof(TQ));   
    assert(tmp);
    tmp->data = node;
    tmp->next = p->next;
    p->next = tmp;
}

BTN* pop(TQ* header)
{
    assert(header);
    TQ* pre = header->next;
    BTN* val = pre->data;
    header->next = pre->next;
    free(pre);
    return val;
}

void LevelOrder(BTN* root)
{
    if (root == NULL)
        return;
    TQ* tq = CreateTQ();
    push(tq, root);
    while (tq->next != NULL)
    {
        BTN* current = pop(tq);
        printf("%d ", current->element);
        if (current->left != NULL)
            push(tq, current->left);
        if (current->right != NULL)
            push(tq, current->right);
    }
}

void show(TQ* header)
{
    TQ* p = header->next;
    while (p != NULL)
    {
        printf("%d ", p->data->element);
        p = p->next;
    }
    printf("\n");
}

int main()
{
    BTN* n1 = CreateBTN(10);
    BTN* n2 = CreateBTN(20);
    BTN* n3 = CreateBTN(50);
    BTN* n4 = CreateBTN(30);
    BTN* n5 = CreateBTN(40);
    BTN* n6 = CreateBTN(60);
    BTN* n7 = CreateBTN(70);

    n1->left = n2;
    n1->right = n3;
    n2->left = n4;
    n2->right = n5;
    n5->left = n6;
    n5->right = n7;

    PostOrder(n1);
    // LevelOrder(n1);
    return 0;
}
