#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 9999
#define MAX 50   // maximum number of cities

// Function to find city index by name
int getCityIndex(char cities[][50], int n, char name[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(cities[i], name) == 0)
            return i;
    }
    return -1;
}

// Function to find vertex with minimum distance
int minDistance(int dist[], int visited[], int n) {
    int min = INF, min_index = -1;
    for (int v = 0; v < n; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Dijkstra algorithm
void dijkstra(int graph[MAX][MAX], int n, int src, int dest, char cities[][50]) {
    int dist[MAX], visited[MAX], parent[MAX];

    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = minDistance(dist, visited, n);
        if (u == -1)
            break;
        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    // Print path
    printf("\n==============================\n");
    printf("   Shortest Path Information\n");
    printf("==============================\n");

    printf("\nPath: ");
    int path[MAX], index = 0;
    for (int v = dest; v != -1; v = parent[v])
        path[index++] = v;

    for (int i = index - 1; i >= 0; i--) {
        printf("%s", cities[path[i]]);
        if (i != 0)
            printf(" -> ");
    }

    printf("\nTotal Distance = %d km\n", dist[dest]);
}

int main() {
    int n, graph[MAX][MAX];
    char cities[MAX][50];

    printf("\n==============================\n");
    printf("   Dynamic City Path Finder\n");
    printf("==============================\n");

    printf("\nEnter number of cities: ");
    scanf("%d", &n);

    // Input city names
    printf("\nEnter city names:\n");
    for (int i = 0; i < n; i++) {
        printf("City %d: ", i + 1);
        scanf("%s", cities[i]);
    }

    // Input distances
    printf("\nEnter distance between cities (in km):\n");
    printf("If no direct path, enter 0.\n\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)
                graph[i][j] = 0;
            else {
                printf("Distance %s -> %s: ", cities[i], cities[j]);
                scanf("%d", &graph[i][j]);
            }
        }
    }

    char srcName[50], destName[50];
    printf("\nEnter Source City: ");
    scanf("%s", srcName);
    printf("Enter Destination City: ");
    scanf("%s", destName);

    int src = getCityIndex(cities, n, srcName);
    int dest = getCityIndex(cities, n, destName);

    if (src == -1 || dest == -1) {
        printf("\nInvalid city name entered!\n");
        return 0;
    }

    dijkstra(graph, n, src, dest, cities);

    return 0;
}
