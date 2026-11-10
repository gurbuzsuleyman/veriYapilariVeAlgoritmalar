#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
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
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

Node *insertBST(Node *root, int data)
{
    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insertBST(root->left, data);
    else if (data > root->data)
        root->right = insertBST(root->right, data);

    return root;
}

int height(Node *root)
{
    if (root == NULL)
        return 0;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int balanceFactor(Node *root)
{
    if (root == NULL)
        return 0;

    return height(root->left) - height(root->right);
}

Node *rotateLeft(Node *root)
{
    Node *newRoot = root->right;
    Node *temp = newRoot->left;

    newRoot->left = root;
    root->right = temp;

    return newRoot;
}

void inorder(Node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
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

int main()
{
    Node *root = NULL;

    int numbers[] = {10, 20, 30};

    for (int i = 0; i < 3; i++)
    {
        root = insertBST(root, numbers[i]);

        printf("%d eklendi. BF(kok) = %d\n",
               numbers[i], balanceFactor(root));

        if (balanceFactor(root) == -2 &&
            root->right != NULL &&
            balanceFactor(root->right) <= 0)
        {

            printf("RR dengesizligi: Sol rotasyon!\n");

            root = rotateLeft(root);
        }
    }

    printf("Kok: %d\n", root->data);

    printf("Inorder: ");
    inorder(root);

    printf("\nPreorder: ");
    preorder(root);

    printf("\n");

    return 0;
}
