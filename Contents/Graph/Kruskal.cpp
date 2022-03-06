#include <bits/stdc++.h>
using namespace std;

//節點從0號開始
struct Edge {
    int v, w, wt;
    Edge(int a, int b, int c) {
        v = a;
        w = b;
        wt = c;
    }
    bool operator<(const Edge &e) const {
        return wt < e.wt;
    }
};

const int maxN = 100000 + 5;  // 最多maxN個節點
int V, E;                     //有V個節點E條鞭
int parent[maxN];
vector<Edge> edges;

int do_find(int p) {
    while (parent[p] >= 0) {
        p = parent[p];
    }
    return p;
}

void do_union(int p, int q) {
    if (parent[p] > parent[q]) {
        parent[q] += parent[p];
        parent[p] = q;
    } else {
        parent[p] += parent[q];
        parent[q] = p;
    }
}

void init() {
    edges.clear();
    for (int i = 0; i < V; i++) {
        parent[i] = -1;
    }
}

int kruskal() {
    sort(edges.begin(), edges.end());
    int mstWeight = 0;
    int pRoot, qRoot;
    for (auto e : edges) {
        pRoot = do_find(e.v);
        qRoot = do_find(e.w);
        if (pRoot != qRoot) {
            mstWeight += e.wt;
            do_union(pRoot, qRoot);
        }
    }
    return mstWeight;
}

int main() {
    int ta, tb, tc;
    while (~scanf("%d %d", &V, &E)) {
        init();
        for (int i = 0; i < E; i++) {
            scanf("%d %d %d", &ta, &tb, &tc);
            edges.push_back({ta, tb, tc});
        }
        printf("%d\n", kruskal());
    }
    return 0;
}
