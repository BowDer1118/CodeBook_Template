#include <bits/stdc++.h>
using namespace std;

//節點從1號開始
const int maxN = 100000 + 5;  // maxN個節點
struct Edge {
    int v, wt;
    Edge(int a, int c) {
        v = a;
        wt = c;
    }
    Edge() {}
};

vector<Edge> g[maxN];
vector<bool> visied(maxN);
vector<int> dis(maxN);

struct Info {
    int v;
    int wt;
    Info(int a, int b) : v(a), wt(b) {}
    Info() {}

    bool operator<(const Info &i) const {
        return wt > i.wt;
    }
};

priority_queue<Info> pq;

void init() {
    for (int i = 0; i < maxN; i++) {
        g[i].clear();
        visied[i] = false;
        dis[i] = 0x3f3f3f;
    }
    while (!pq.empty()) {
        pq.pop();
    }
}

void dijkstra(int s) {
    Info info;
    dis[s] = 0;
    visied[s] = true;
    pq.push({s, 0});

    while (!pq.empty()) {
        info = pq.top();
        pq.pop();
        visied[info.v] = true;
        if (dis[info.v] > info.wt) {
            dis[info.v] = info.wt;
        }
        for (auto e : g[info.v]) {
            if (!visied[e.v]) {
                pq.push({e.v, dis[info.v] + e.wt});
            }
        }
    }
}

int m, n, ta, tb, tc;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    while (cin >> m >> n) {
        init();
        while (n--) {
            cin >> ta >> tb >> tc;
            g[ta].push_back({tb, tc});
            g[tb].push_back({ta, tc});
        }
        dijkstra(1);  //從1號節點開始
    }
    return 0;
}