#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    int height;
    struct Node *left;
    struct Node *right;
} Node;

Node *createNode(int data)
{
    Node *newNode = malloc(sizeof(Node));

    if (newNode == NULL)
    {
        printf("Bellek hatasi!");
        exit(1);
    }

    newNode->data = data;
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

int height(Node *node)
{
    if (node == NULL)
        return 0;

    return node->height;
}

int balanceFactor(Node *node)
{
    if (node == NULL)
        return 0;

    return height(node->left) - height(node->right);
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

Node *rotateRight(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + max(height(y->left),
                        height(y->right));

    x->height = 1 + max(height(x->left),
                        height(x->right));

    return x;
}

Node *rotateLeft(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + max(height(x->left),
                        height(x->right));

    y->height = 1 + max(height(y->left),
                        height(y->right));

    return y;
}

Node *insertAVL(Node *root, int key)
{

    if (root == NULL)
        return createNode(key);

    if (key < root->data)
        root->left = insertAVL(root->left, key);

    else if (key > root->data)
        root->right = insertAVL(root->right, key);

    else
        return root;

    root->height = 1 + max(height(root->left),
                           height(root->right));

    int bf = balanceFactor(root);

    if (bf > 1 && key < root->left->data)
        return rotateRight(root);

    if (bf < -1 && key > root->right->data)
        return rotateLeft(root);

    if (bf > 1 && key > root->left->data)
    {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (bf < -1 && key < root->right->data)
    {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

void preorder(Node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void runTest(char *name, int numbers[])
{
    Node *root = NULL;

    for (int i = 0; i < 3; i++)
    {
        root = insertAVL(root, numbers[i]);
    }

    printf("%s\n", name);
    printf("Kok: %d\n", root->data);

    printf("Preorder: ");
    preorder(root);

    printf("\n\n");
}

int main()
{

    int A[] = {30, 20, 10};
    int B[] = {10, 20, 30};
    int C[] = {30, 10, 20};
    int D[] = {10, 30, 20};

    runTest("A (LL)", A);
    runTest("B (RR)", B);
    runTest("C (LR)", C);
    runTest("D (RL)", D);

    return 0;
}
