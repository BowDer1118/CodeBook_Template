#include <bits/stdc++.h>
using namespace std;
// Kruskal (MST) 節點從0號開始
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

const int maxN = 100000 + 5;  // maxN個節點
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

int m, n, ta, tb, tc, weight;

int main() {
    while (~scanf("%d %d", &m, &n)) {
        for (int i = 0; i < n; i++) {
            scanf("%d %d %d", &ta, &tb, &tc);
            edges.push_back({ta, tb, tc});
        }
        sort(edges.begin(), edges.end());
        for (int i = 0; i <= m; i++) {
            parent[i] = -1;
        }
        weight = 0;
        for (auto e : edges) {
            ta = do_find(e.v);
            tb = do_find(e.w);
            if (ta != tb) {
                weight += e.wt;
                do_union(ta, tb);
            }
        }
        printf("%d\n", weight);
    }
    return 0;
}