#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Word
{
    char text[50];
    struct Word *next;
} Word;

void showWords(Word *top)
{
    if (!top)
        return;
    showWords(top->next);
    printf("%s ", top->text);
}

int main(void)
{
    Word *top = NULL, *temp;
    char komut[10], kelime[50];

    while (1)
    {
        printf("\nIslem (add / undo / show / exit): ");
        if (scanf("%9s", komut) != 1)
            break;

        if (strcmp(komut, "add") == 0)
        {
            printf("Kelime gir: ");
            if (scanf("%49s", kelime) != 1)
                break;

            temp = malloc(sizeof *temp);
            if (!temp)
                break;
            strcpy(temp->text, kelime);
            temp->next = top;
            top = temp;
        }
        else if (strcmp(komut, "undo") == 0)
        {
            if (!top)
                puts("Geri alinacak kelime yok.");
            else
            {
                temp = top;
                top = top->next;
                free(temp);
            }
        }
        else if (strcmp(komut, "show") == 0)
        {
            showWords(top);
            putchar('\n');
        }
        else if (strcmp(komut, "exit") == 0)
            break;
        else
            puts("Gecersiz komut.");
    }

    while (top)
    {
        temp = top;
        top = top->next;
        free(temp);
    }
    return 0;
}
