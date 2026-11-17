#include <stdio.h>

#define N 5

char sehirler[N] = {'A', 'B', 'C', 'D', 'E'};

int graf[N][N] = {0};
int ziyaret[N] = {0};

void baglantiEkle(int a, int b) {
    graf[a][b] = 1;
    graf[b][a] = 1;
}

void BFS(int baslangic) {
    int kuyruk[N];
    int bas = 0, son = 0;

    for (int i = 0; i < N; i++)
        ziyaret[i] = 0;

    ziyaret[baslangic] = 1;
    kuyruk[son++] = baslangic;

    printf("BFS: ");

    while (bas < son) {
        int dugum = kuyruk[bas++];

        printf("%c ", sehirler[dugum]);

        for (int i = 0; i < N; i++) {
            if (graf[dugum][i] == 1 && !ziyaret[i]) {
                ziyaret[i] = 1;
                kuyruk[son++] = i;
            }
        }
    }
    printf("\n");
}

void DFS(int dugum) {
    ziyaret[dugum] = 1;

    printf("%c ", sehirler[dugum]);

    for (int i = 0; i < N; i++) {
        if (graf[dugum][i] == 1 && !ziyaret[i]) {
            DFS(i);
        }
    }
}

int main() {

    baglantiEkle(0, 1); // A-B
    baglantiEkle(0, 3); // A-D
    baglantiEkle(1, 2); // B-C
    baglantiEkle(1, 4); // B-E
    baglantiEkle(3, 4); // D-E

    printf("Graf Baglantilari:\n");
    printf("A - B\n");
    printf("A - D\n");
    printf("B - C\n");
    printf("B - E\n");
    printf("D - E\n\n");

    BFS(0);

    for (int i = 0; i < N; i++)
        ziyaret[i] = 0;

    printf("DFS: ");
    DFS(0);

    return 0;
}
