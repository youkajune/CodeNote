#ifndef INITIALIZER_LIST_TEST
#define INITIALIZER_LIST_TEST


double sum(std::initializer_list<double> il) {
    double sum = 0;
    for (auto t = il.begin(); t != il.end(); t++)
        sum += *t;
    return sum;
}

void test_initializer_list() {
    double total = sum({2.5, 3.3, 4.8});
    std::cout << total;
}

#endif // INITIALIZER_LIST_TEST
