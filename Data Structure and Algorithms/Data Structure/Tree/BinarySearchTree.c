#include <assert.h>
#include <malloc.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct BinarySearchTree
{
    int element;
    struct BinarySearchTree* left;
    struct BinarySearchTree* right;
}BST;

BST* MakeEmpty(BST* root)
{
    if (root != NULL) 
    {
        MakeEmpty(root->left);
        MakeEmpty(root->right);
        free(root);
    }
    return NULL;
}

BST* Insert(int element, BST* root)
{
    if(root == NULL)
    {
        root = (BST*)malloc(sizeof(BST));
        assert(root);
        root->element = element;
        root->left = root->right = NULL;
    }
    else if (root->element < element) 
        root->right = Insert(element, root->right);        
    else if (root->element > element)
        root->left = Insert(element, root->left);
    return root;
}

BST* Find(BST* root, int element)
{
    if(root == NULL)
        return NULL;
    if(element < root->element)
        return Find(root->left, element);
    else if (element > root->element)
        return Find(root->right, element);
    else
        return root;
}

BST* FindMax(BST* root)
{
    if (root == NULL) 
        return NULL;
    else if (root->right == NULL)
        return root;
    else
        return FindMax(root->right);
}

BST* FindMin(BST* root)
{
    if (root == NULL) 
        return NULL;
    else if (root->left == NULL)
        return root;
    else
        return FindMin(root->left);
}

BST* Delete(BST* root, int element)
{
    BST* tmp;
    if(root == NULL)
        perror(" root ");
    else if (element < root->element)
        root->left = Delete(root->left, element);
    else if (element > root->element)
        root->right = Delete(root->right, element);
    else if (root->left && root->right)
    {
        tmp = FindMin(root->right);
        root->element = tmp->element;
        root->right = Delete(root->right, element); 
    }
    else
    {
        tmp = root;
        if(root->left == NULL)
            root = root->right;
        else if (root->right == NULL)
            root = root->left;
        free(tmp);
    }
    return root;
}

void Inorder(BST* node)
{
    if (node == NULL)
        return;
    Inorder(node->left);
    printf("%d ", node->element);
    Inorder(node->right);
}

int main()
{
    int arr[] = {100, 50, 70, 200, 300, 500, 20, 10, 120, 75, 220};
    int sz = sizeof(arr) / sizeof(arr[0]);
    
    BST* root = Insert(arr[0], NULL);
    for (int i = 1; i < sz; i++) 
        Insert(arr[i], root);
    
    Inorder(root);

    if (Find(root, 70)) 
        printf("\nfound the num %d\n", Find(root, 70)->element);
    else
        printf("not found\n");
    
    printf("the maxnum if %d \n", FindMax(root)->element);
    printf("the minnum if %d \n", FindMin(root)->element);

    // Delete(root, 100);
    Inorder(root);
    
    return 0;
}