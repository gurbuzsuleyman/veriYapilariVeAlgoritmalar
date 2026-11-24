#include <stdio.h>
#include <stdbool.h>

#define N 6

void grafAnaliz(int kenarlar[][2], int kenarSayisi)
{
    int adj[N][N] = {0};

    for (int i = 0; i < kenarSayisi; i++)
    {
        int u = kenarlar[i][0] - 1;
        int v = kenarlar[i][1] - 1;
        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    printf("Komsuluk Matrisi (%dx%d):\n", N, N);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ", adj[i][j]);
        }
        printf("\n");
    }

    int genelDerece = 0;
    printf("\nDugum Dereceleri:\n");
    for (int i = 0; i < N; i++)
    {
        int derece = 0;
        for (int j = 0; j < N; j++)
        {
            derece += adj[i][j];
        }
        genelDerece += derece;
        printf("Dugum %d derecesi: %d\n", i + 1, derece);
    }
    printf("Grafin Genel Derecesi: %d\n", genelDerece);

    int mesafe[N];
    for (int i = 0; i < N; i++)
    {
        mesafe[i] = -1;
    }

    int kuyruk[N];
    int on = 0, arka = 0;

    mesafe[0] = 0;
    kuyruk[arka++] = 0;

    while (on < arka)
    {
        int u = kuyruk[on++];
        for (int v = 0; v < N; v++)
        {
            if (adj[u][v] == 1 && mesafe[v] == -1)
            {
                mesafe[v] = mesafe[u] + 1;
                kuyruk[arka++] = v;
            }
        }
    }

    printf("\nUzaklik ve Renk/Parite Tablosu (Baslangic: Dugum 1):\n");
    for (int i = 0; i < N; i++)
    {
        printf("Dugum %d -> Uzaklik: %d | Parite/Renk: %d (%s)\n",
               i + 1, mesafe[i], mesafe[i] % 2,
               (mesafe[i] % 2 == 0) ? "Cift / Mavi" : "Tek / Kirmizi");
    }

    bool bipartite = true;
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            if (adj[i][j] == 1 && (mesafe[i] % 2 == mesafe[j] % 2))
            {
                bipartite = false;
            }
        }
    }

    if (bipartite)
    {
        printf("\nSonuc: Graf Iki Parcalidir (Bipartite).\n");
    }
    else
    {
        printf("\nSonuc: Graf Iki Parcali Degildir (Bipartite Degil).\n");
    }
}

int main()
{
    int kenarlar1[7][2] = {
        {1, 2}, {1, 4}, {2, 3}, {3, 4}, {3, 6}, {4, 5}, {5, 6}};
    printf("=== 1. DURUM: ORIJINAL GRAF ===\n");
    grafAnaliz(kenarlar1, 7);

    int kenarlar2[8][2] = {
        {1, 2}, {1, 4}, {2, 3}, {3, 4}, {3, 6}, {4, 5}, {5, 6}, {2, 4}};
    printf("\n=== 2. DURUM: (2, 4) KENARI EKLENDIKTEN SONRA ===\n");
    grafAnaliz(kenarlar2, 8);

    return 0;
}