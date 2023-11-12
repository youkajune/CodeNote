#include <iostream>
#include <new>
#include <cstdlib> // for exit(), EXIT_FAILURE

using namespace std;

struct Big {
    double stuff[20000];
};

int main() {
    Big* pb;
    // new 的异常处理
//    try {
//        cout << "尝试申请一大块内存:\n";
//        pb = new Big[100000]; // 100000 * 20000 * 8 = 16 000 000 000 Bytes
//        cout << "最新申请结果:\n";
//    } catch (bad_alloc & ba) {
//        cout << "申请失败，捕获异常: " << ba.what() << endl;
//        exit(EXIT_FAILURE);
//    }
    // new 的空指针处理
    pb = new (std::nothrow) Big[100000];
    if (pb == nullptr) {
        cout << "申请失败.\n ";
        exit(EXIT_FAILURE);
    }
    cout << "内存空间申请成功\n";
    pb[0].stuff[0] = 4;
    cout << pb[0].stuff[0] << endl;
    delete [] pb;
    return 0;
}