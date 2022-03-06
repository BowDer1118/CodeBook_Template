#include <bits/stdc++.h>
using namespace std;

const int maxN = 100000;
int V, E;           //有V個節點E個邊
int G[maxN][maxN];  // adjacency matrix
int d[maxN][maxN];  // 最短路徑長度

void floyd_warshall() {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            d[i][j] = G[i][j];
        }
    }

    for (int i = 0; i < V; i++) {
        d[i][i] = 0;
    }

    for (int k = 0; k < V; k++) {
        // 嘗試每一個中繼點
        for (int i = 0; i < V; i++) {
            // 計算每一個i點與每一個j點
            for (int j = 0; j < V; j++) {
                if (d[i][k] + d[k][j] < d[i][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                }
            }
        }
    }
}

int main() {
    int ta, tb, tc;
    while (~scanf("%d %d", &V, &E)) {
        memset(G, 0, sizeof(G));
        memset(d, 0, sizeof(d));
        for (int i = 0; i < E; i++) {
            scanf("%d %d %d", &ta, &tb, &tc);
            G[ta][tb] = tc;
            G[tb][ta] = tc;
        }
        floyd_warshall();
        //輸出所有點對點的權重
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                printf("V[%d] to V[%d] dis=%d\n", i, j, d[i][j]);
            }
        }
    }
    return 0;
}