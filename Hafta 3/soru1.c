#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

void addOrdered(Node **head, int value)
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

    if (value < (*head)->data)
    {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    Node *current = *head;

    while (current->next != NULL &&
           current->next->data < value)
    {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}

void removeNode(Node **head, int value)
{
    if (*head == NULL)
    {
        return;
    }

    if ((*head)->data == value)
    {
        Node *temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }

    Node *current = *head;

    while (current->next != NULL &&
           current->next->data != value)
    {
        current = current->next;
    }

    if (current->next != NULL)
    {
        Node *temp = current->next;
        current->next = temp->next;
        free(temp);
    }
}

int count(Node *head)
{
    int sayac = 0;

    while (head != NULL)
    {
        sayac++;
        head = head->next;
    }

    return sayac;
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

    addOrdered(&head, 23);
    addOrdered(&head, 11);
    addOrdered(&head, 5);
    addOrdered(&head, 9);
    addOrdered(&head, 6);
    addOrdered(&head, 4);
    addOrdered(&head, 12);
    addOrdered(&head, 24);

    printf("Liste: ");
    printList(head);

    printf("Eleman sayisi: %d\n", count(head));

    removeNode(&head, 9);

    printf("9 silindikten sonra: ");
    printList(head);

    clear(&head);

    printf("Clear sonrasi eleman sayisi: %d\n", count(head));

    return 0;
}