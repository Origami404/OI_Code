
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::min;
using std::swap;

constexpr int data_size = 31;
int data[data_size];

void init_data() {
    std::memset(data, 0, sizeof(data));
    for (int i = -data_size / 2, j = 0; j < data_size; i++, j++) {
        data[j] = i;
    }
}
void random() {
    std::random_shuffle(data, data + data_size);
}
bool test_data() {
    cout << "Now is testing: ";
    bool is_right = true;
    int line = 0;
    for (line = 1; line < data_size && is_right; line++) {
        is_right = is_right && (data[line - 1] <= data[line]);
    }
    if (!is_right)
        cout << "DO NOT MATCH IN LINE: " << line << endl;

    else {
        cout << "OK" << endl;
    }

    return is_right;
}
void print_data() {
    
    for (int i = 0; i < data_size; i++) {
        cout << std::setw(4) << data[i];
    }
    cout << endl;
    
}
void test(int (*func)()) {
    random();
    cout << func() << endl;
    test_data();
}
// 冒泡排序, O(n^2)
// https://zh.wikipedia.org/wiki/%E5%86%92%E6%B3%A1%E6%8E%92%E5%BA%8F
int bubble_sort() {
    cout << "Now is bubble_sort." << endl;
    int tot = 0, swap_count = 0;
    print_data();
    do {
        swap_count = 0;
        for (int i = 0; i < data_size; i++) {
            if (data[i] > data[i + 1]) {
                swap(data[i], data[i + 1]);
                tot++;
                swap_count++;
            }
        }
        print_data();
        // cout << "Now SC: " << swap_count << endl;
    } while (swap_count != 0);
    return tot;
}

int merge(int* ns, int begin, int cur, int end) {
    int tot = 0;
    for (int i = begin, j = cur, t = begin; i < cur || j < end; t++) {
        if (j >= end ||
            (i < cur &&
             data[i] <=
                 data[j])) {  // 如果j那一半出界，那么直接复制i；否则若i还有就比较
            ns[t] = data[i++];
        } else {
            ns[t] = data[j++];
        }
        tot++;
        // ns[t++] = (i >= cur &&j<end) ||  ns[i] <= ns[j] ? data[j++] :
        // data[i++];
    }
    for (int i = begin; i < end; i++) {
        data[i] = ns[i];
    }
    return tot;
}
// 归并排序递归版
int& merge_sort_recursive(int begin, int end, int* ns, int& tot) {
    if (end - begin == 1)
        return tot;
    //分治！
    int cur = begin + (end - begin) / 2;
    merge_sort_recursive(begin, cur, ns, tot);
    merge_sort_recursive(cur, end, ns, tot);
    // cout << "cur:" << cur << endl;
    // 归并！
    tot += merge(ns, begin, cur, end);

    print_data();
    return tot;
}

int merge_sort2() {
    int tot = 0;
    int tmp[data_size];
    for (int len = 2; len <= data_size; len *= 2) {
        int range_begin = 0;
        // 每个区间都来一遍
        for (; range_begin + len < data_size; range_begin += len) {
            tot += merge(tmp, range_begin, range_begin + len / 2,
                         range_begin + len);
        }
        // 可能最后还有凑不够一个区间的
        tot += merge(tmp, range_begin, range_begin + len / 2, data_size);
        print_data();
    }
    // 最后也可能也凑不上的哦
    tot += merge(tmp, 0, data_size / 2, data_size);
    return tot;
}
int merge_sort1() {
    cout << "Now is merge_sort_recursive." << endl;
    int space[data_size], tot = 0;
    memset(space, 0, data_size);
    int ret = merge_sort_recursive(0, data_size, space, tot);

    return ret;
}
int quick_sort() {
    return 0;
}

int main() {
    init_data();
    test(bubble_sort);
    test(merge_sort1);
    test(merge_sort2);

    return 0;
}
