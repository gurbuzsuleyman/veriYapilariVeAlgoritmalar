#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Song
{
    char name[50];
    struct Song *next, *prev;
} Song;

void satirOku(char *s, int boyut)
{
    int c;

    if (!fgets(s, boyut, stdin))
    {
        s[0] = '\0';
        return;
    }

    if (strchr(s, '\n'))
        s[strcspn(s, "\n")] = '\0';
    else
        while ((c = getchar()) != '\n' && c != EOF)
            ;
}

int main(void)
{
    Song *head = NULL, *current = NULL;
    char giris[30], isim[50];
    int secim, uzunluk;

    while (1)
    {
        printf("\n--- Muzik Calar ---\n"
               "1. Sarki ekle\n"
               "2. Sarki sil\n"
               "3. Sonraki sarki\n"
               "4. Onceki sarki\n"
               "5. Listeyi goster\n"
               "0. Cikis\n"
               "Seciminiz: ");

        satirOku(giris, sizeof(giris));

        if (sscanf(giris, " %d %n", &secim, &uzunluk) != 1 ||
            giris[uzunluk] != '\0')
        {
            puts("Gecersiz secim.");
            continue;
        }

        switch (secim)
        {
        case 1:
        {
            printf("Sarki adi: ");
            satirOku(isim, sizeof(isim));

            if (!isim[0])
            {
                puts("Sarki adi bos olamaz.");
                break;
            }

            Song *yeni = malloc(sizeof *yeni);
            if (!yeni)
            {
                puts("Bellek ayrilamadi.");
                break;
            }

            strcpy(yeni->name, isim);
            yeni->next = NULL;
            yeni->prev = NULL;

            if (!head)
                head = current = yeni;
            else
            {
                Song *son = head;
                while (son->next)
                    son = son->next;
                son->next = yeni;
                yeni->prev = son;
            }

            printf("Sarki eklendi: %s\n", isim);
            break;
        }

        case 2:
        {
            printf("Silinecek sarki adi: ");
            satirOku(isim, sizeof(isim));

            Song *s = head;
            while (s && strcmp(s->name, isim))
                s = s->next;

            if (!s)
            {
                puts("Sarki bulunamadi.");
                break;
            }

            if (current == s)
                current = s->next ? s->next : s->prev;

            if (s->prev)
                s->prev->next = s->next;
            else
                head = s->next;

            if (s->next)
                s->next->prev = s->prev;

            free(s);
            puts("Sarki silindi.");
            break;
        }

        case 3:
            if (!current)
                puts("Liste bos.");
            else if (!current->next)
                printf("Son sarkidasiniz: %s\n", current->name);
            else
            {
                current = current->next;
                printf("Calan sarki: %s\n", current->name);
            }
            break;

        case 4:
            if (!current)
                puts("Liste bos.");
            else if (!current->prev)
                printf("Ilk sarkidasiniz: %s\n", current->name);
            else
            {
                current = current->prev;
                printf("Calan sarki: %s\n", current->name);
            }
            break;

        case 5:
            if (!head)
                puts("Liste bos.");
            else
            {
                puts("\nSarki listesi:");
                for (Song *s = head; s; s = s->next)
                    printf("%s%s\n", s->name,
                           s == current ? "  <- secili" : "");
            }
            break;

        case 0:
            while (head)
            {
                Song *sonraki = head->next;
                free(head);
                head = sonraki;
            }
            puts("Program kapatildi.");
            return 0;

        default:
            puts("Gecersiz secim.");
        }
    }
}
