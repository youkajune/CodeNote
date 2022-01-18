#include "stock2.h"

int main(int argc, char** args) {
    Stock arr[5] = {
        Stock(), // 手动调用默认构造函数
        Stock("Stock1", 3, 2.5),
        Stock(arr[1])
    };
    return 0;
}