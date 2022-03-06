#include <bits/stdc++.h>
using namespace std;

// bit陣列索引從1開始
const int maxN = 100000 + 5;  // bit容量
const int dataSize = 5;       //資料大小 arr[0,5)--->bit[1,5]
int bit[maxN];

int query(int x) {
    // query prefix sum in BIT
    int ret = 0;
    while (x) {
        ret += bit[x];
        x -= x & (-x);
    }
    return ret;
}

//更新bit[x]的值
void update(int x, int d) {
    while (x <= dataSize) {
        bit[x] += d;
        x += x & (-x);
    }
}

// 區間和 [l,r]
int rSum(int l, int r) {
    return query(r) - query(l - 1);
}

int main() {
    memset(bit, 0, sizeof(bit));
    int arr[dataSize] = {1, 2, 3, 4, 5};
    for (int i = 0; i < dataSize; i++) {
        update(i + 1, arr[i]);  // arr[i]放bit[i+1]的位置
    }
    printf("%d\n", rSum(2, 4));  // arr[2,4]=2+3+4
    return 0;
}