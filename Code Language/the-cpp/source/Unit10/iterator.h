#ifndef ITERATOR_H
#define ITERATOR_H

#include <iterator>
#include <iostream>
#include <vector>
#include <string>

/**
 * 演示以下迭代器的使用
 * istream_iterator/ostream_iterator
 * reverse_iterator
 * back_insert_iterator/front_insert_iterator/insert_iterator
 **/

void test_istream_iterator() {
    using namespace std;
    int array[10] = { 8, 22, 344, 8, 99, 3, 10, 5, 487, 2};
    vector<int> vec(10);
    // copy elem from array to vector.
    copy(array, array+10, vec.begin());

    // create an ostream iterator
    ostream_iterator<int, char> outIt(cout, " ");
    cout << "Copy elem from array to output: ";
    // copy elem from vector to output
    copy(vec.begin(), vec.end(), outIt);
    cout << endl;
}


void test_reverse_iterator() {
    using namespace std;
    vector<int> vec = { 8, 22, 344, 8, 99, 3, 10, 5, 487, 2};
    ostream_iterator<int, char> outIt(cout, " ");

    // 隐式使用 reverse_iterator
    cout << "Reverse vector to output(Implicit): ";
    copy(vec.rbegin(), vec.rend(), outIt);
    cout << endl;

    cout << "Reverse vector to output(Explicit): ";
    // 显式使用 reverse_iterator
    for (vector<int>::reverse_iterator vri = vec.rbegin(); vri != vec.rend(); vri++) {
        cout << *vri << " ";
    }
    cout << endl;
}

void test_insert_iterator() {
    using namespace std;
    int i1[4] = {11, 13, 14, 10};
    int i2[2] = {26, 24};
    int i3[4] = {38, 33, 39, 36};
    vector<int> vec(4);

    copy(i1, i1+4, vec.begin());
    for (int x:vec) cout << x << " ";
    cout << endl;

    copy(i2, i2+2, back_insert_iterator<vector<int>> (vec));
    for (int x:vec) cout << x << " ";
    cout << endl;

    copy(i3, i3 + 4, insert_iterator<vector<int>>(vec, vec.begin()));
    for (int x:vec) cout << x << " ";
    cout << endl;
}

void test_STL_iterator() {
    test_istream_iterator();
    test_reverse_iterator();
    test_insert_iterator();
}

#endif // ITERATOR_H