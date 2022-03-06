#include <bits/stdc++.h>
using namespace std;

// bit陣列索引從1開始
const int maxN = 100000 + 5;  // bit最大容量
int bit[maxN];
//放入的資料量
int dataSize;

//更新bit[x]的值(加d)
void update(int x, int d) {
    while (x <= dataSize) {
        bit[x] += d;
        x += x & (-x);
    }
}
//前綴和[1,x]
int query(int x) {
    int ret = 0;
    while (x) {
        ret += bit[x];
        x -= x & (-x);
    }
    return ret;
}

// 區間和 [l,r]
int rSum(int l, int r) {
    return query(r) - query(l - 1);
}

int main() {
    memset(bit, 0, sizeof(bit));
    vector<int> v = {0x3f3f3f, 1, 2, 3, 4, 5};
    dataSize = v.size() - 1;  // v[0]不使用
    for (int i = 1; i < v.size(); i++) {  //放入v[1,5]
        update(i, v[i]);
    }
    printf("%d\n", rSum(2, 4));  // v[2,4]=2+3+4=9
    return 0;
}
