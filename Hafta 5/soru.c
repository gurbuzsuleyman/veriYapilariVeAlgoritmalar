#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Hasta {
    int id;
    char isim[50];
    char durum[20];
    struct Hasta *sonraki;
} Hasta;

typedef struct {
    Hasta *bas;
    Hasta *son;
} Kuyruk;

typedef struct {
    Hasta *ust;
} Yigin;

typedef struct {
    Hasta *bas;
    Hasta *son;
} Gecmis;

Hasta *hastaOlustur(int id, char isim[]) {
    Hasta *yeni = malloc(sizeof(Hasta));

    if (yeni == NULL) {
        printf("Bellek ayrilamadi.\n");
        exit(1);
    }

    yeni->id = id;
    strcpy(yeni->isim, isim);
    strcpy(yeni->durum, "bekliyor");
    yeni->sonraki = NULL;

    return yeni;
}

void enqueue(Kuyruk *kuyruk, Hasta *hasta) {
    hasta->sonraki = NULL;

    if (kuyruk->bas == NULL) {
        kuyruk->bas = hasta;
        kuyruk->son = hasta;
    } else {
        kuyruk->son->sonraki = hasta;
        kuyruk->son = hasta;
    }
}

Hasta *dequeue(Kuyruk *kuyruk) {
    if (kuyruk->bas == NULL) {
        printf("Bekleme kuyrugu bos.\n");
        return NULL;
    }

    Hasta *hasta = kuyruk->bas;
    kuyruk->bas = hasta->sonraki;

    if (kuyruk->bas == NULL) {
        kuyruk->son = NULL;
    }

    hasta->sonraki = NULL;
    return hasta;
}

void push(Yigin *yigin, Hasta *hasta) {
    strcpy(hasta->durum, "muayenede");
    hasta->sonraki = yigin->ust;
    yigin->ust = hasta;
}

Hasta *pop(Yigin *yigin) {
    if (yigin->ust == NULL) {
        printf("Muayene odasinda hasta yok.\n");
        return NULL;
    }

    Hasta *hasta = yigin->ust;
    yigin->ust = hasta->sonraki;
    hasta->sonraki = NULL;

    return hasta;
}

void gecmiseEkle(Gecmis *gecmis, Hasta *hasta) {
    strcpy(hasta->durum, "tamamlandi");
    hasta->sonraki = NULL;

    if (gecmis->bas == NULL) {
        gecmis->bas = hasta;
        gecmis->son = hasta;
    } else {
        gecmis->son->sonraki = hasta;
        gecmis->son = hasta;
    }
}

void hastalariListele(Hasta *bas) {
    if (bas == NULL) {
        printf("Hasta yok.\n");
        return;
    }

    Hasta *gecici = bas;

    while (gecici != NULL) {
        printf("Hasta ID: %d, Isim: %s, Durum: %s\n",
               gecici->id, gecici->isim, gecici->durum);
        gecici = gecici->sonraki;
    }
}

void gecmisiListele(Gecmis *gecmis) {
    printf("--- Tamamlanan Hastalar ---\n");
    hastalariListele(gecmis->bas);
}

void tumunuListele(char baslik[], Kuyruk *kuyruk,
                   Yigin *yigin, Gecmis *gecmis) {
    printf("\n=== %s ===\n", baslik);

    printf("--- Bekleyen Hastalar ---\n");
    hastalariListele(kuyruk->bas);

    printf("--- Muayene Odasindaki Hastalar ---\n");
    hastalariListele(yigin->ust);

    gecmisiListele(gecmis);
}

void bellegiTemizle(Hasta *bas) {
    while (bas != NULL) {
        Hasta *sonraki = bas->sonraki;
        free(bas);
        bas = sonraki;
    }
}

int main() {
    Kuyruk kuyruk = {NULL, NULL};
    Yigin yigin = {NULL};
    Gecmis gecmis = {NULL, NULL};
    Hasta *hasta;

    enqueue(&kuyruk, hastaOlustur(1, "Ahmet"));
    enqueue(&kuyruk, hastaOlustur(2, "Mehmet"));
    enqueue(&kuyruk, hastaOlustur(3, "Ayse"));

    tumunuListele("Baslangic Durumu", &kuyruk, &yigin, &gecmis);

    printf("\n=== Hasta Aktarim Islemleri ===\n");

    hasta = dequeue(&kuyruk);
    if (hasta != NULL) {
        push(&yigin, hasta);
        printf("%s muayeneye alindi.\n", hasta->isim);
    }

    hasta = pop(&yigin);
    if (hasta != NULL) {
        gecmiseEkle(&gecmis, hasta);
        printf("%s'in muayenesi tamamlandi.\n", hasta->isim);
    }

    hasta = dequeue(&kuyruk);
    if (hasta != NULL) {
        push(&yigin, hasta);
        printf("%s muayeneye alindi.\n", hasta->isim);
    }

    hasta = pop(&yigin);
    if (hasta != NULL) {
        gecmiseEkle(&gecmis, hasta);
        printf("%s'in muayenesi tamamlandi.\n", hasta->isim);
    }

    tumunuListele("Tum Islemler Sonrasi", &kuyruk, &yigin, &gecmis);

    bellegiTemizle(kuyruk.bas);
    bellegiTemizle(yigin.ust);
    bellegiTemizle(gecmis.bas);

    return 0;
}
