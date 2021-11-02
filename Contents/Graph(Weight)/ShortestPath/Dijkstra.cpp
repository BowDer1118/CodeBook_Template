#include <bits/stdc++.h>

#include "Edge.h"

using namespace std;

//data indexes reverse 陣列大小都是capacity大小+1

// 最小索引堆
template <typename Item>
class IndexMinHeap {
   private:
    Item *data;    // 最小索引堆中的数据
    int *indexes;  // 最小索引堆中的索引, indexes[x] = i 表示索引i在x的位置
    int *reverse;  // 最小索引堆中的反向索引, reverse[i] = x 表示索引i在x的位置
    int count;
    int capacity;
    // 索引堆中, 数据之间的比较根据data的大小进行比较, 但实际操作的是索引
    void shiftUp(int k) {
        while (k > 1 && data[indexes[k / 2]] > data[indexes[k]]) {
            swap(indexes[k / 2], indexes[k]);
            reverse[indexes[k / 2]] = k / 2;
            reverse[indexes[k]] = k;
            k /= 2;
        }
    }
    // 索引堆中, 数据之间的比较根据data的大小进行比较, 但实际操作的是索引
    void shiftDown(int k) {
        while (2 * k <= count) {
            int j = 2 * k;
            if (j + 1 <= count && data[indexes[j]] > data[indexes[j + 1]])
                j += 1;
            if (data[indexes[k]] <= data[indexes[j]])
                break;
            swap(indexes[k], indexes[j]);
            reverse[indexes[k]] = k;
            reverse[indexes[j]] = j;
            k = j;
        }
    }

   public:
    // 构造函数, 构造一个空的索引堆, 可容纳capacity个元素
    IndexMinHeap(int capacity) {
        data = new Item[capacity + 1];
        indexes = new int[capacity + 1];
        reverse = new int[capacity + 1];
        for (int i = 0; i <= capacity; i++)
            reverse[i] = 0;
        count = 0;
        this->capacity = capacity;
    }
    ~IndexMinHeap() {
        delete[] data;
        delete[] indexes;
        delete[] reverse;
    }
    // 返回索引堆中的元素个数
    int size() {
        return count;
    }
    // 返回一个布尔值, 表示索引堆中是否为空
    bool isEmpty() {
        return count == 0;
    }
    // 向最小索引堆中插入一个新的元素, 新元素的索引为i, 元素为item
    // 传入的i对用户而言,是从0索引的
    void insert(int index, Item item) {
        index += 1;
        data[index] = item;
        indexes[count + 1] = index;
        reverse[index] = count + 1;
        count++;
        shiftUp(count);
    }

    // 从最小索引堆中取出堆顶元素, 即索引堆中所存储的最小数据
    Item extractMin() {
        Item ret = data[indexes[1]];
        swap(indexes[1], indexes[count]);
        reverse[indexes[count]] = 0;
        reverse[indexes[1]] = 1;
        count--;
        shiftDown(1);
        return ret;
    }

    // 从最小索引堆中取出堆顶元素的索引
    int extractMinIndex() {
        int ret = indexes[1] - 1;
        swap(indexes[1], indexes[count]);
        reverse[indexes[count]] = 0;
        reverse[indexes[1]] = 1;
        count--;
        shiftDown(1);
        return ret;
    }

    // 获取最小索引堆中的堆顶元素
    Item getMin() {
        return data[indexes[1]];
    }

    // 获取最小索引堆中的堆顶元素的索引
    int getMinIndex() {
        return indexes[1] - 1;
    }

    // 看索引i所在的位置是否存在元素
    bool contain(int index) {
        return reverse[index + 1] != 0;
    }

    // 获取最小索引堆中索引为i的元素
    Item getItem(int index) {
        return data[index + 1];
    }

    // 将最小索引堆中索引为i的元素修改为newItem
    void change(int index, Item newItem) {
        index += 1;
        data[index] = newItem;
        shiftUp(reverse[index]);
        shiftDown(reverse[index]);
    }
};

// Dijkstra算法求最短路径
template <typename Graph, typename Weight>
class Dijkstra {
   private:
    Graph &G;                     // 图的引用
    int s;                        // 起始点
    Weight *distTo;               // distTo[i]存储从起始点s到i的最短路径长度
    bool *marked;                 // 标记数组, 在算法运行过程中标记节点i是否被访问
    vector<Edge<Weight> *> from;  // from[i]记录最短路径中, 到达i点的边是哪一条
   public:
    // 构造函数, 使用Dijkstra算法求最短路径
    Dijkstra(Graph &graph, int s) : G(graph) {
        // 算法初始化
        assert(s >= 0 && s < G.V());
        this->s = s;
        distTo = new Weight[G.V()];
        marked = new bool[G.V()];
        for (int i = 0; i < G.V(); i++) {
            distTo[i] = Weight();
            marked[i] = false;
            from.push_back(NULL);
        }
        // 使用索引堆记录当前找到的到达每个顶点的最短距离
        IndexMinHeap<Weight> ipq(G.V());
        // 对于其实点s进行初始化
        distTo[s] = Weight();
        from[s] = new Edge<Weight>(s, s, Weight());
        ipq.insert(s, distTo[s]);
        marked[s] = true;
        while (!ipq.isEmpty()) {
            int v = ipq.extractMinIndex();
            // distTo[v]就是s到v的最短距离
            marked[v] = true;
            // 对v的所有相邻节点进行更新
            typename Graph::adjIterator adj(G, v);
            for (Edge<Weight> *e = adj.begin(); !adj.end(); e = adj.next()) {
                int w = e->other(v);
                // 如果从s点到w点的最短路径还没有找到
                if (!marked[w]) {
                    // 如果w点以前没有访问过,
                    // 或者访问过, 但是通过当前的v点到w点距离更短, 则进行更新
                    if (from[w] == NULL || distTo[v] + e->wt() < distTo[w]) {
                        distTo[w] = distTo[v] + e->wt();
                        from[w] = e;
                        if (ipq.contain(w))
                            ipq.change(w, distTo[w]);
                        else
                            ipq.insert(w, distTo[w]);
                    }
                }
            }
        }
    }

    // 析构函数
    ~Dijkstra() {
        delete[] distTo;
        delete[] marked;
        delete from[0];
    }

    // 返回从s点到w点的最短路径长度
    Weight shortestPathTo(int w) {
        return distTo[w];
    }
    // 判断从s点到w点是否联通
    bool hasPathTo(int w) {
        return marked[w];
    }
    // 寻找从s到w的最短路径, 将整个路径经过的边存放在vec中
    void shortestPath(int w, vector<Edge<Weight>> &vec) {
        // 通过from数组逆向查找到从s到w的路径, 存放到栈中
        stack<Edge<Weight> *> s;
        Edge<Weight> *e = from[w];
        while (e->v() != this->s) {
            s.push(e);
            e = from[e->v()];
        }
        s.push(e);
        // 从栈中依次取出元素, 获得顺序的从s到w的路径
        while (!s.empty()) {
            e = s.top();
            vec.push_back(*e);
            s.pop();
        }
    }

    // 打印出从s点到w点的路径
    void showPath(int w) {
        vector<Edge<Weight>> vec;
        shortestPath(w, vec);
        for (int i = 0; i < vec.size(); i++) {
            cout << vec[i].v() << " -> ";
            if (i == vec.size() - 1)
                cout << vec[i].w() << endl;
        }
    }
};
