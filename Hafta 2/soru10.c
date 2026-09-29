#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

int main()
{
    struct Node *head = (struct Node *)malloc(sizeof(struct Node));
    struct Node *n2 = (struct Node *)malloc(sizeof(struct Node));
    struct Node *n3 = (struct Node *)malloc(sizeof(struct Node));
    struct Node *n4 = (struct Node *)malloc(sizeof(struct Node));

    head->data = 10;
    head->next = n2;
    n2->data = 20;
    n2->next = n3;
    n3->data = 30;
    n3->next = n4;
    n4->data = 40;
    n4->next = NULL;

    int silinecek;
    printf("Silmek istediginiz degeri girin: ");
    scanf("%d", &silinecek);

    struct Node *temp = head;
    struct Node *prev = NULL;

    if (temp != NULL && temp->data == silinecek)
    {
        head = temp->next;
        free(temp);
    }
    else
    {
        while (temp != NULL && temp->data != silinecek)
        {
            prev = temp;
            temp = temp->next;
        }

        if (temp != NULL)
        {
            prev->next = temp->next;
            free(temp);
        }
        else
        {
            printf("Deger listede bulunamadi!\n");
        }
    }

    struct Node *current = head;
    while (current != NULL)
    {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");

    return 0;
}