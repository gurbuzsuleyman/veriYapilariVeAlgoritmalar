#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

void insertAt(Node **head, int value, int position)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    if (newNode == NULL)
    {
        printf("Bellek ayrilamadi!\n");
        return;
    }

    newNode->data = value;
    newNode->next = NULL;

    if (position <= 0 || *head == NULL)
    {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    Node *current = *head;
    int index = 0;

    while (current->next != NULL &&
           index < position - 1)
    {
        current = current->next;
        index++;
    }

    newNode->next = current->next;
    current->next = newNode;
}

void deleteAt(Node **head, int position)
{
    if (*head == NULL || position < 0)
    {
        return;
    }

    if (position == 0)
    {
        Node *temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }

    Node *current = *head;
    int index = 0;

    while (current->next != NULL &&
           index < position - 1)
    {
        current = current->next;
        index++;
    }

    if (current->next == NULL)
    {
        return;
    }

    Node *temp = current->next;
    current->next = temp->next;

    free(temp);
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

    insertAt(&head, 10, 0);
    insertAt(&head, 20, 1);
    insertAt(&head, 30, 2);

    printf("Baslangic listesi: ");
    printList(head);

    insertAt(&head, 15, 1);

    printf("15 eklendikten sonra: ");
    printList(head);

    insertAt(&head, 40, 100);

    printf("40 eklendikten sonra: ");
    printList(head);

    insertAt(&head, 5, -2);

    printf("5 eklendikten sonra: ");
    printList(head);

    deleteAt(&head, 2);

    printf("2. pozisyon silindikten sonra: ");
    printList(head);

    deleteAt(&head, 100);

    printf("Gecersiz silme sonrasi: ");
    printList(head);

    clear(&head);

    return 0;
}