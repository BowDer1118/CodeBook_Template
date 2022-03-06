#include <bits/stdc++.h>
using namespace std;
//節點從0開始(適用於無向圖)
//備註:如果圖為無向圖且包含負權邊 則必定有負權環
struct Edge {
    int f, t, wt;
    Edge() {}
    Edge(int a, int b, int c) {
        f = a;
        t = b;
        wt = c;
    }
};

int V, E;                 //節點與邊數
const int maxN = 100000;  //最多maxN個節點
vector<vector<Edge>> G(maxN);
vector<int> distTo(maxN);  //到節點i的權重
bool hasNegtiveCycle;
Edge e;

void init() {
    for (int i = 0; i < V; i++) {
        G[i].clear();
        distTo[i] = 0x3f3f3f;
    }
}

bool detectHasCycle() {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < G[i].size(); j++) {
            e = G[i][j];
            if (distTo[e.f] + e.wt < distTo[e.t]) {
                return true;
            }
        }
    }
    return false;
}

void bellmanFord(int s) {  //從s點開始
    distTo[s] = 0;
    //執行節點-1次鬆弛
    for (int pass = 1; pass < V; pass++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < G[i].size(); j++) {
                e = G[i][j];
                if (distTo[e.f] + e.wt < distTo[e.t]) {
                    distTo[e.t] = distTo[e.f] + e.wt;
                }
            }
        }
    }
    //檢測負權環
    hasNegtiveCycle = detectHasCycle();
}

int main() {
    scanf("%d %d", &V, &E);
    init();
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &e.f, &e.t, &e.wt);
        G[e.f].push_back(e);
    }
    bellmanFord(0);  //從節點0開始
    if (!hasNegtiveCycle) {
        for (int i = 0; i < V; i++) {
            printf("%d ", distTo[i]);
        }
        printf("\n");
    } else {
        printf("Has Negtive Cycle.");
    }
    return 0;
}