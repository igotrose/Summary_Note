#include<stdio.h>
#include<stdlib.h>

typedef struct BinaryBalanceTree
{
    int val;
    int height;
    struct BinaryBalanceTree* left;
    struct BinaryBalanceTree* right;
}Node;

Node* CreateNode(int val)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->val = val;
    node->height = 1;
    node->right = node->left = NULL;
    return node;
}

Node* Find(Node* root, int target, int* count)
{
    Node* current = root;
    while (current != NULL)
    {
        if (current->val > target)
        {
            (*count)++;
            current = current->left;
        }
        else if (current->val < target)
        {
            (*count)++;
            current = current->right;
        }
        else
            return current;
    }
    return NULL;
}

int Max(int a, int b)
{
    return (a > b) ? a: b;
}

int Height(Node* root)
{
    if (root == NULL)
        return 0;
    return root->height;
}

int GetBalance(Node* node)
{
    if (node == NULL)
        return 0;
    return Height(node->left) - Height(node->right);
}

Node* FindMin(Node* node)
{
    if (node == NULL)
        return NULL;
    else if (node->left == NULL)
        return node;
    else
        return FindMin(node->right);
}

Node* LeftRotate(Node* node) 
{
    Node* newnode = node->right;
    Node* T2 = newnode->left;

    // 执行旋转
    newnode->left = node;
    node->right = T2;

    // 更新节点高度
    node->height = Max(Height(node->left), Height(node->right)) + 1;
    newnode->height = Max(Height(newnode->left), Height(newnode->right)) + 1;

    return newnode; // 返回新的根节点
}
 
Node* RightRotate(Node* node) 
{
    Node* newnode = node->left;
    Node* T2 = newnode->right;
 
    // 执行旋转
    newnode->right = node;
    node->left = T2;

    // 更新节点高度
    node->height = Max(Height(node->left), Height(node->right)) + 1;
    newnode->height = Max(Height(newnode->left), Height(newnode->right)) + 1;

    return newnode; // 返回新的根节点
}

Node* InsertNode(Node* node, int val) 
{
    // 执行标准的BST插入
    if (node == NULL)
        return CreateNode(val);

    if (val < node->val)
        node->left = InsertNode(node->left, val);
    else if (val > node->val)
        node->right = InsertNode(node->right, val);
    else // 重复的数据不允许插入
        return node;

    // 更新节点高度
    node->height = 1 + Max(Height(node->left), Height(node->right));

    // 获取节点的平衡因子
    int balance = GetBalance(node);

    // 如果节点不平衡，进行相应的旋转操作
    // 左-左
    if (balance > 1 && GetBalance(node->left) > 0)
        return RightRotate(node);

    // 右-右
    if (balance < -1 && GetBalance(node->right) < 0)
        return LeftRotate(node);

    // 左-右
    if (balance > 1 && GetBalance(node->left) < 0) 
    {
        node->left = LeftRotate(node->left);
        return RightRotate(node);
    }

    // 右-左
    if (balance < -1 && GetBalance(node->right) > 0) 
    {
        node->right = RightRotate(node->right);
        return LeftRotate(node);
    }

    return node; // 返回未修改的节点
}

Node* DeleteNode(Node* root, int val)
{
    if (root == NULL)
        return root;
    if (root->val > val)
        root->left = DeleteNode(root->left, val);
    else if (root->val < val)
        root->right = DeleteNode(root->right, val);
    else if (root->left && root->right)
    {
        Node* temp = FindMin(root->right);
        root->val = temp->val;
        root->right = DeleteNode(root->right, val);
    }
    else
    {
        Node* temp = root;
        if (root->right == NULL)
            root = root->left;
        else if (root->left == NULL)
            root = root->right;
        free(temp);
    }
    
    int balance = GetBalance(root);

    if (balance > 1 && GetBalance(root->left) >= 0)
        return RightRotate(root);

    if (balance > 1 && GetBalance(root->left) < 0)
    {
        root->left = LeftRotate(root->left);
        return RightRotate(root);
    }
    if (balance < -1 && GetBalance(root->right) <= 0)
        return LeftRotate(root);
    
    if (balance < -1 && GetBalance(root->right) > 0)
    {
        root->right = LeftRotate(root->right);
        return LeftRotate(root);
    }

    return root;
}

void PreOrder(Node* node)
{
    if (node == NULL)
        return;
    printf("%d ", node->val);
    PreOrder(node->left);
    PreOrder(node->right);
}

void MidOrder(Node* node)
{
    if (node == NULL)
        return;
    MidOrder(node->left);
    printf("%d ", node->val);
    MidOrder(node->right);
}

int main()
{
    Node* root = NULL;

    root = InsertNode(root, 10);
    root = InsertNode(root, 20);
    root = InsertNode(root, 30);
    root = InsertNode(root, 40);
    root = InsertNode(root, 50);
    root = InsertNode(root, 60);
    root = InsertNode(root, 70);

    int counter = 0;
    Node* result = Find(root, 70, &counter);
    printf("找了几次:%d\n", counter);
    printf("-------先序遍历结果--------\n");
    PreOrder(root);
    printf("\n-------中序遍历结果--------\n");
    MidOrder(root);
    printf("\n");
     
    return 0;
}                                               