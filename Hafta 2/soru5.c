#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

int main()
{
    struct Node n1 = {10, NULL}, n2 = {20, NULL}, n3 = {30, NULL}, n4 = {40, NULL};
    n1.next = &n2;
    n2.next = &n3;
    n3.next = &n4;
    struct Node *head = &n1;

    int count = 0;
    struct Node *current = head;

    while (current != NULL)
    {
        count++;
        current = current->next;
    }

    printf("Listedeki eleman sayisi: %d\n", count);
    return 0;
}