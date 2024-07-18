#ifndef MOVE_SEMANTICS_H
#define MOVE_SEMANTICS_H
#include <vector>
#include <algorithm>


/* 移动语义的演示 */
/**
 * 将字符串数组中的小写字符全部转换为大写字符，并保存到另一个数组中作为返回值返回
 **/
std::vector<std::string> upper_string(const std::vector<std::string> & vstr) {
    std::vector<std::string> temp(vstr);
    for (auto & x:temp) {
        std::transform(x.begin(), x.end(), x.begin(), [](char c) { return std::toupper(c); } );
    }
    return temp;
}

void test_copy_constructor() {
    using namespace std;
    vector<string> v_str({
        "You Ka",
        "Mo, Zi, yu",
        "Hello, World!"
    });
    vector<string> v_str_copy1(v_str);
    vector<string> v_str_copy2(upper_string(v_str));
    for (auto x:v_str_copy2) {
        std::cout << x << endl;
    }
}

#endif // MOVE_SEMANTICS_H