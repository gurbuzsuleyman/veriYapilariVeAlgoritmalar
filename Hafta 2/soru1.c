#include <stdio.h>

struct Node
{
    int data;
    struct Node *next;
};

int main()
{
    struct Node node;
    node.data = 10;
    node.next = NULL;

    printf("%d -> NULL\n", node.data);
    return 0;
}