#include <bits/stdc++.h>
using namespace std;

//data indexes reverse 陣列邊界都是以[1,capacity]處理--->陣列大小為(capacity+1)

// 最大索引堆
template <typename Item>
class IndexMaxHeap {
   private:
    Item *data;    // 最大索引堆中的数据
    int *indexes;  // 最大索引堆中的索引, indexes[x] = i 表示索引i在x的位置
    int *reverse;  // 最大索引堆中的反向索引, reverse[i] = x 表示索引i在x的位置
    int count;
    int capacity;
    // 索引堆中, 数据之间的比较根据data的大小进行比较, 但实际操作的是索引
    void shiftUp(int k) {
        while (k > 1 && data[indexes[k / 2]] < data[indexes[k]]) {
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
            if (j + 1 <= count && data[indexes[j + 1]] > data[indexes[j]])
                j += 1;

            if (data[indexes[k]] >= data[indexes[j]])
                break;

            swap(indexes[k], indexes[j]);
            reverse[indexes[k]] = k;
            reverse[indexes[j]] = j;
            k = j;
        }
    }

   public:
    // 构造函数, 构造一个空的索引堆, 可容纳capacity个元素
    IndexMaxHeap(int capacity) {
        data = new Item[capacity + 1];
        indexes = new int[capacity + 1];
        reverse = new int[capacity + 1];
        for (int i = 0; i <= capacity; i++)
            reverse[i] = 0;

        count = 0;
        this->capacity = capacity;
    }
    ~IndexMaxHeap() {
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
    // 向最大索引堆中插入一个新的元素, 新元素的索引为i, 元素为item
    // 传入的i对用户而言,是从0索引的
    void insert(int i, Item item) {
        i += 1;
        data[i] = item;
        indexes[count + 1] = i;
        reverse[i] = count + 1;
        count++;
        shiftUp(count);
    }

    // 从最大索引堆中取出堆顶元素, 即索引堆中所存储的最大数据
    Item extractMax() {
        Item ret = data[indexes[1]];
        swap(indexes[1], indexes[count]);
        reverse[indexes[count]] = 0;
        count--;

        if (count) {
            reverse[indexes[1]] = 1;
            shiftDown(1);
        }

        return ret;
    }

    // 从最大索引堆中取出堆顶元素的索引
    int extractMaxIndex() {
        int ret = indexes[1] - 1;
        swap(indexes[1], indexes[count]);
        reverse[indexes[count]] = 0;
        count--;
        if (count) {
            reverse[indexes[1]] = 1;
            shiftDown(1);
        }
        return ret;
    }
    // 获取最大索引堆中的堆顶元素
    Item getMax() {
        return data[indexes[1]];
    }
    // 获取最大索引堆中的堆顶元素的索引
    int getMaxIndex() {
        return indexes[1] - 1;
    }
    // 看索引i所在的位置是否存在元素
    bool contain(int i) {
        return reverse[i + 1] != 0;
    }
    // 获取最大索引堆中索引为i的元素
    Item getItem(int i) {
        return data[i + 1];
    }

    // 将最大索引堆中索引为i的元素修改为newItem
    void change(int i, Item newItem) {
        i += 1;
        data[i] = newItem;
        shiftUp(reverse[i]);
        shiftDown(reverse[i]);
    }
};