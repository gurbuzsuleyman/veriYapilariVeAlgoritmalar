#include <stdio.h>
#include <ctype.h>

#define N 6
#define INF 9999

void addEdge(int graph[N][N], int u, int v, int w)
{
    graph[u][v] = w;
    graph[v][u] = w;
}

int dijkstra(int graph[N][N], int src, int dist[N], int path[N], int printTable)
{
    int known[N] = {0};

    for (int i = 0; i < N; i++)
    {
        dist[i] = INF;
        path[i] = -1;
    }
    dist[src] = 0;

    if (printTable)
    {
        printf("\n--- Kok Dugum %c Icin Dijkstra Adim Tablosu ---\n", 'A' + src);
        printf("%-6s | %-8s | %-10s | %-6s\n", "Dugum", "Known", "Distance", "Path");
        printf("----------------------------------------\n");
    }

    for (int step = 0; step < N; step++)
    {
        int u = -1;
        int minDist = INF;

        for (int i = 0; i < N; i++)
        {
            if (!known[i] && dist[i] < minDist)
            {
                minDist = dist[i];
                u = i;
            }
        }

        if (u == -1)
            break;
        known[u] = 1;

        for (int v = 0; v < N; v++)
        {
            if (!known[v] && graph[u][v] > 0 && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                path[v] = u;
            }
        }

        if (printTable)
        {
            printf("Adim %d (Secilen: %c):\n", step + 1, 'A' + u);
            for (int i = 0; i < N; i++)
            {
                if (dist[i] == INF)
                {
                    printf("  %-4c | %-8d | %-10s | %-6c\n", 'A' + i, known[i], "INF", '-');
                }
                else
                {
                    printf("  %-4c | %-8d | %-10d | %-6c\n", 'A' + i, known[i], dist[i], path[i] == -1 ? '-' : 'A' + path[i]);
                }
            }
            printf("----------------------------------------\n");
        }
    }

    int totalCost = 0;
    for (int i = 0; i < N; i++)
    {
        if (dist[i] != INF)
        {
            totalCost += dist[i];
        }
    }
    return totalCost;
}

void printRoute(int src, int dest, int dist[N], int path[N])
{
    if (dist[dest] == INF)
    {
        printf("%c -> %c arasi yol yok.\n", 'A' + src, 'A' + dest);
        return;
    }

    int stack[N];
    int top = 0;
    int curr = dest;

    while (curr != -1)
    {
        stack[top++] = curr;
        curr = path[curr];
    }

    printf("%c -> %c En Kisa Rota (Maliyet: %d): ", 'A' + src, 'A' + dest, dist[dest]);
    for (int i = top - 1; i >= 0; i--)
    {
        printf("%c", 'A' + stack[i]);
        if (i > 0)
            printf(" -> ");
    }
    printf("\n");
}

int main()
{
    int graph[N][N] = {0};

    addEdge(graph, 0, 1, 7);
    addEdge(graph, 0, 2, 5);
    addEdge(graph, 0, 5, 1);
    addEdge(graph, 1, 2, 1);
    addEdge(graph, 1, 3, 1);
    addEdge(graph, 1, 4, 3);
    addEdge(graph, 2, 3, 2);
    addEdge(graph, 2, 4, 1);
    addEdge(graph, 3, 5, 7);
    addEdge(graph, 4, 5, 2);

    char kokChar;
    printf("Kok dugumu giriniz (A-F): ");
    scanf(" %c", &kokChar);

    int kok = toupper(kokChar) - 'A';
    if (kok < 0 || kok >= N)
        kok = 0;

    int dist[N], path[N];
    dijkstra(graph, kok, dist, path, 1);

    printf("\n--- Gorev 2: Kok Dugum A Icin Rota Ciktisi ---\n");
    dijkstra(graph, 0, dist, path, 0);
    printRoute(0, 1, dist, path);
    printRoute(0, 3, dist, path);

    printf("\n--- Gorev 3: Merkezi Dugum Analizi ---\n");
    int costs[N];
    int minTotalCost = INF;

    for (int i = 0; i < N; i++)
    {
        costs[i] = dijkstra(graph, i, dist, path, 0);
        printf("Kok Dugum %c -> En Kisa Yol Toplam Maliyeti: %d\n", 'A' + i, costs[i]);
        if (costs[i] < minTotalCost)
        {
            minTotalCost = costs[i];
        }
    }

    printf("\nEn Merkezi Dugum(ler) (Minimum Maliyet = %d): ", minTotalCost);
    int first = 1;
    for (int i = 0; i < N; i++)
    {
        if (costs[i] == minTotalCost)
        {
            if (!first)
                printf(", ");
            printf("%c", 'A' + i);
            first = 0;
        }
    }
    printf("\n");

    return 0;
}