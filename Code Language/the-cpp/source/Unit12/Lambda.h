#ifndef LAMBDA_H
#define LAMBDA_H

#include <functional>
#include <algorithm>
#include <cmath>


int test_Lambda() {

    std::function<int(int, int)> fadd = [](int x, int y) { return x+y; };
    int result = fadd(2, 3);
    std::cout << "Result: " << result << std::endl;

    return 0;
}

/**
 * �жϲ��� x �Ƿ�ɱ� 3 ����
 **/
bool f3(int x) {
    return x % 3 == 0;
}

/**
 * �жϲ��� x �Ƿ�ɱ� 13 ����
 **/
bool f13(int x) {
    return x % 13 == 0;
}

/**
 * �������ֺ������󣺺���ָ�롢��������Lambda Ϊ STL �㷨������Ϣ��ʾ��
 * Ҫ������һ������ 1000 ������������б����ж����ж���Ԫ�ؿɱ� 3 ����������Ԫ�ؿɱ� 13 ������
 **/
int test_3_functor() {
    using namespace std;
    // ���� 1000 ������������б�
    vector<int> vint(1000);
    generate(vint.begin(), vint.end(), rand);

    int count3 = 0; // ��¼�ɱ� 3 ������Ԫ����Ŀ
    int count13 = 0; // ��¼�ɱ� 3 ������Ԫ����Ŀ
    // ����ָ���ʵ��
    count3 = count_if(vint.begin(), vint.end(), f3);
    count13 = count_if(vint.begin(), vint.end(), f13);
    cout << "count3: " << count3 << ", count13: " << count13 << endl;

    count3 = 0;
    count13 = 0;
    // ��������ʵ��
    /**
    * ���� operator()() �����������ɼ�������
    **/
    class f_mod {
    private:
        int mod; // ��¼����������
    public:
        f_mod(int x = 1) : mod(x) {}
        bool operator()(int x) { return x % mod == 0; }
    };
    count3 = count_if(vint.begin(), vint.end(), f_mod(3));
    count13 = count_if(vint.begin(), vint.end(), f_mod(13));
    cout << "count3: " << count3 << ", count13: " << count13 << endl;

    count3 = 0;
    count13 = 0;
    // Lambda ��ʵ�� 1
    count3 = count_if(vint.begin(), vint.end(), [](int x) { return x % 3 == 0; });
    count13 = count_if(vint.begin(), vint.end(), [](int x) { return x % 13 == 0; });
    cout << "count3: " << count3 << ", count13: " << count13 << endl;

    count3 = 0;
    count13 = 0;
    // Lambda ��ʵ�� 2
    for_each(vint.begin(), vint.end(), [&](int x) { count3 += (x % 3 == 0); count13 += (x % 13 == 0); });
    cout << "count3: " << count3 << ", count13: " << count13 << endl;
    return 0;
}

template<typename T, typename F>
T use_f(T t, F f) {
    static int count = 0;
    count++;
    std::cout << "use_f count = " << count
              << ", &count = " << &count << " ";
    return f(t);
}

double f1(double x) { return 2.0 * x; }
double f2(double x) { return 1.0 + x; }

class F1 {
private:
    double d;
public:
    F1(double x = 1.0) : d(x) {}
    double operator()(double x) { return x * d; }
};

class F2 {
private:
    double d;
public:
    F2(double x = 1.0): d(x) {}
    double operator()(double x) { return x + d; }
};
/**
 * չʾģ��ĵ�Ч��
 **/
int test_template_inefficiency() {
    using namespace std;
    double y = 1.2;
    cout << "Function pointer f1: " << use_f(y, f1) << endl;
    cout << "Function pointer f2: " << use_f(y, f2) << endl;
    cout << "Function object  F1: " << use_f(y, F1(8.8)) << endl;
    cout << "Function object  F2: " << use_f(y, F2(8.8)) << endl;
    cout << "Lambda expression 1: " << use_f(y, [](double x) { return x * x; }) << endl;
    cout << "Lambda expression 2: " << use_f(y, [](double x) { return x / 0.5; }) << endl;
    return 0;
}

int test_function() {
    using namespace std;
    double y = 1.2;
    function<double(double)> fdd[6] = {f1, f2, F1(8.8), F2(8.8),
                                       [](double x) { return x * x; },
                                       [](double x) { return x / 0.5;}};
    cout << "Function pointer f1: " << use_f(y, fdd[0]) << endl;
    cout << "Function pointer f2: " << use_f(y, fdd[1]) << endl;
    cout << "Function object  F1: " << use_f(y, fdd[2]) << endl;
    cout << "Function object  F2: " << use_f(y, fdd[3]) << endl;
    cout << "Lambda expression 1: " << use_f(y, fdd[4]) << endl;
    cout << "Lambda expression 2: " << use_f(y, fdd[5]) << endl;
    return 0;
}

template <typename T>
T use_f_mut(T t, std::function<T(T)> f) {
    static int count = 0;
    count++;
    std::cout << "use_f count = " << count
              << ", &count = " << &count << " ";
    return f(t);
}

int test_function_mut() {
    using namespace std;
    double y = 1.2;
    cout << "Function pointer f1: " << use_f_mut<double>(y, f1) << endl;
    cout << "Function pointer f2: " << use_f_mut<double>(y, f2) << endl;
    cout << "Function object  F1: " << use_f_mut<double>(y, F1(8.8)) << endl;
    cout << "Function object  F2: " << use_f_mut<double>(y, F2(8.8)) << endl;
    cout << "Lambda expression 1: " << use_f_mut<double>(y, [](double x) { return x * x; }) << endl;
    cout << "Lambda expression 2: " << use_f_mut<double>(y, [](double x) { return x / 0.5; }) << endl;
    return 0;
}

#endif // LAMBDA_H