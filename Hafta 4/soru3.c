#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PrintJob
{
    char fileName[50];
    struct PrintJob *next;
} PrintJob;

typedef struct Queue
{
    PrintJob *front, *rear;
} Queue;

void enqueuePrintJob(Queue *q, char *fileName)
{
    PrintJob *job = malloc(sizeof *job);
    if (!job)
    {
        puts("Bellek ayrilamadi.");
        return;
    }

    snprintf(job->fileName, sizeof job->fileName, "%s", fileName);
    job->next = NULL;

    if (q->rear)
        q->rear->next = job;
    else
        q->front = job;

    q->rear = job;
    printf("Kuyruga eklendi: %s\n", job->fileName);
}

void processNextJob(Queue *q)
{
    if (!q->front)
    {
        puts("Kuyruk bos, yazdirilacak dosya yok.");
        return;
    }

    PrintJob *job = q->front;
    printf("Yazdiriliyor: %s\n", job->fileName);

    q->front = job->next;
    if (!q->front)
        q->rear = NULL;
    free(job);
}

void showQueue(Queue q)
{
    if (!q.front)
    {
        puts("Kuyruk bos.");
        return;
    }

    printf("Kuyruk: ");
    for (PrintJob *job = q.front; job; job = job->next)
        printf("%s%s", job->fileName, job->next ? " -> " : "\n");
}

int main(void)
{
    Queue q = {NULL, NULL};
    char giris[50];

    while (1)
    {
        printf("\n1) Yeni dosya ekle\n2) Yazdir\n"
               "3) Kuyrugu goster\n0) Cikis\nSecim: ");

        if (!fgets(giris, sizeof giris, stdin))
            break;
        giris[strcspn(giris, "\n")] = '\0';

        if (strcmp(giris, "1") == 0)
        {
            printf("Dosya adi: ");
            if (!fgets(giris, sizeof giris, stdin))
                break;
            giris[strcspn(giris, "\n")] = '\0';

            if (giris[0])
                enqueuePrintJob(&q, giris);
            else
                puts("Dosya adi bos olamaz.");
        }
        else if (strcmp(giris, "2") == 0)
            processNextJob(&q);
        else if (strcmp(giris, "3") == 0)
            showQueue(q);
        else if (strcmp(giris, "0") == 0)
            break;
        else
            puts("Gecersiz secim.");
    }

    while (q.front)
    {
        PrintJob *job = q.front;
        q.front = job->next;
        free(job);
    }
    return 0;
}