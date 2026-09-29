#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

void append(Node **head, int value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    if (newNode == NULL)
    {
        printf("Bellek ayrilamadi!\n");
        return;
    }

    newNode->data = value;
    newNode->next = NULL;

    if (*head == NULL)
    {
        *head = newNode;
        return;
    }

    Node *current = *head;

    while (current->next != NULL)
    {
        current = current->next;
    }

    current->next = newNode;
}

Node *findMiddle(Node *head)
{
    if (head == NULL)
    {
        return NULL;
    }

    Node *slow = head;
    Node *fast = head;

    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

void printList(Node *head)
{
    while (head != NULL)
    {
        printf("%d", head->data);

        if (head->next != NULL)
        {
            printf(" -> ");
        }

        head = head->next;
    }

    printf("\n");
}

void clear(Node **head)
{
    Node *current = *head;

    while (current != NULL)
    {
        Node *temp = current;
        current = current->next;
        free(temp);
    }

    *head = NULL;
}

int main()
{
    Node *head = NULL;

    append(&head, 10);
    append(&head, 20);
    append(&head, 30);
    append(&head, 40);
    append(&head, 50);
    append(&head, 60);

    printf("Liste: ");
    printList(head);

    Node *middle = findMiddle(head);

    if (middle != NULL)
    {
        printf("Orta dugum: %d\n", middle->data);
    }
    else
    {
        printf("Liste bos.\n");
    }

    clear(&head);

    return 0;
}