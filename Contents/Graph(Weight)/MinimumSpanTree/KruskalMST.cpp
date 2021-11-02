#include <bits/stdc++.h>

#include "Edge.h"
using namespace std;

//陣列大小為傳入的數量n(通常是圖的頂點數量)
// Quick Union + rank + path compression
class UnionFind {
   private:
    int* rank;
    int* parent;  // parent[i]表示第i个元素所指向的父节点
    int count;    // 数据个数
   public:
    // 构造函数
    UnionFind(int count) {
        parent = new int[count];
        rank = new int[count];
        this->count = count;
        for (int i = 0; i < count; i++) {
            parent[i] = i;
            rank[i] = 1;
        }
    }
    // 析构函数
    ~UnionFind() {
        delete[] parent;
        delete[] rank;
    }
    // 查找过程, 查找元素p所对应的集合编号
    // O(h)复杂度, h为树的高度
    int find(int p) {
        // path compression 1
        while (p != parent[p]) {
            parent[p] = parent[parent[p]];
            p = parent[p];
        }
        return p;
    }
    // 查看元素p和元素q是否所属一个集合
    // O(h)复杂度, h为树的高度
    bool isConnected(int p, int q) {
        return find(p) == find(q);
    }
    // 合并元素p和元素q所属的集合
    // O(h)复杂度, h为树的高度
    void unionElements(int p, int q) {
        int pRoot = find(p);
        int qRoot = find(q);
        if (pRoot == qRoot)
            return;
        // 根据两个元素所在树的元素个数不同判断合并方向
        // 将元素个数少的集合合并到元素个数多的集合上
        if (rank[pRoot] < rank[qRoot]) {
            parent[pRoot] = qRoot;
        } else if (rank[qRoot] < rank[pRoot]) {
            parent[qRoot] = pRoot;
        } else {  // rank[pRoot] == rank[qRoot]
            parent[pRoot] = qRoot;
            rank[qRoot] += 1;  // 此时, 我维护rank的值
        }
    }
};

// Kruskal算法
template <typename Graph, typename Weight>
class KruskalMST {
   private:
    vector<Edge<Weight>> mst;  // 最小生成树所包含的所有边
    Weight mstWeight;          // 最小生成树的权值

   public:
    // 构造函数, 使用Kruskal算法计算graph的最小生成树
    KruskalMST(Graph& graph) {
        // 将图中的所有边存放到一个最小堆中
        priority_queue<Edge<Weight>> pq(Edge<Weight>, vector<Edge<Weight>>, greater<Edge<Weight>>);
        for (int i = 0; i < graph.V(); i++) {
            typename Graph::adjIterator adj(graph, i);
            for (Edge<Weight>* e = adj.begin(); !adj.end(); e = adj.next())
                if (e->v() < e->w())
                    pq.push(*e);
        }

        // 创建一个并查集, 来查看已经访问的节点的联通情况
        UnionFind uf = UnionFind(graph.V());
        while (!pq.isEmpty() && mst.size() < graph.V() - 1) {
            // 从最小堆中依次从小到大取出所有的边
            Edge<Weight> e = pq.pop();
            pq.pop();
            // 如果该边的两个端点是联通的, 说明加入这条边将产生环, 扔掉这条边
            if (uf.isConnected(e.v(), e.w()))
                continue;

            // 否则, 将这条边添加进最小生成树, 同时标记边的两个端点联通
            mst.push_back(e);
            uf.unionElements(e.v(), e.w());
        }

        mstWeight = mst[0].wt();
        for (int i = 1; i < mst.size(); i++)
            mstWeight += mst[i].wt();
    }
    ~KruskalMST() {}
    // 返回最小生成树的所有边
    vector<Edge<Weight>> mstEdges() {
        return mst;
    };
    // 返回最小生成树的权值
    Weight result() {
        return mstWeight;
    };
};
