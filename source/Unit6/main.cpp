#include "Contains.h"
#include "PrivateExtend.h"
#include "MultipleInheritance.h"
#include "ClassTemplate.h"
#include <iostream>
#include <cstring>

// ����˽�м̳�
void testPrivateExtend();
// ���Զ��ؼ̳еĻ��� Worker��Waiter��Singer
void testBase();
// ���Զ��ؼ̳�
void testMultipleInheritance();
// ������ģ��
void testClassTemplate();
// ���Դ���ʹ��ָ���ָ��ջ
void testErrPointStack1();
// ���Դ���ʹ��ָ���ָ��ջ
void testErrPointStack2();
// ���Դ���ʹ��ָ���ָ��ջ
void testErrPointStack3();
// ���Է����Ͳ���������ģ����
void testArrayTemplate();
// ����Pairģ��(�����ģ��)
void testPairTemplate();
// ���Գ�Աģ��
void testMemberTemplate();
// ����ģ����Ϊ��һ��ģ��Ĳ���
void testTemplateParam();
// ���Է�ģ����Ԫ
void testTemplateFriend1();
// ����Լ��ģ����Ԫ
void testTemplateFriend2();
// ���Է�Լ��ģ����Ԫ
void testTemplateFriend3();
int main() {
//    std::cout << "Test Private Extend:\n";
//    testPrivateExtend();
//    std::cout << std::endl << std::endl;
//    std::cout << "Test Multiple Inheritance Base Class:\n" << std::endl;
//    testBase();
//    std::cout << "Test Multiple Inheritance:\n";
//    testMultipleInheritance();
//    std::cout << "Test Class Template:\n";
//    testClassTemplate();
//    testErrPointStack1();
//    testErrPointStack2();
//    testErrPointStack3();
//    std::cout << "Test Array Template:\n" << std::endl;
//    testArrayTemplate();
//    testPairTemplate();
//    testMemberTemplate();
//    testTemplateParam();
//    testTemplateFriend1();
//    testTemplateFriend2();
    testTemplateFriend3();
    return 0;
}

void testPrivateExtend() {
    Person1 p11 = Person1("Contains Object.");
    Person1 p12 = Person1("ABC DEF.");
    Person1 p13;
    std::cout << "Test of getName(): p11 - " << p11.getName() << std::endl;
    std::cout << "Test of getSize(): p11 - " << p11.getSize() << std::endl;
    std::cout << "Test of getName(): p12 - " << p12.getName() << std::endl;
    std::cout << "Test of getSize(): p12 - " << p12.getSize() << std::endl;
    std::cout << "Test of getName(): p13 - " << p13.getName() << std::endl;
    std::cout << "Test of getSize(): p13 - " << p13.getSize() << std::endl;
    std::cout << "Test of operator<(): p11 < p12 - " << (p11 < p12) << std::endl;
    std::cout << "Test of operator<(): p11 < p13 - " << (p11 < p13) << std::endl;
    std::cout << "Test of operator<(): p12 < p13 - " << (p12 < p13) << std::endl;
    std::cout << p11 << std::endl << p12 << std::endl << p13 << std::endl << std::endl;

    Person2 p21 = Person2("Private Extend.");
    Person2 p22 = Person2("GHI JKL.");
    Person2 p23;
    std::cout << "Test of getName(): p21 - " << p21.getName() << std::endl;
    std::cout << "Test of getSize(): p21 - " << p21.getSize() << std::endl;
    std::cout << "Test of getName(): p22 - " << p22.getName() << std::endl;
    std::cout << "Test of getSize(): p22 - " << p22.getSize() << std::endl;
    std::cout << "Test of getName(): p23 - " << p23.getName() << std::endl;
    std::cout << "Test of getSize(): p23 - " << p23.getSize() << std::endl;
    std::cout << "Test of operator<(): p21 < p22 - " << (p21 < p22) << std::endl;
    std::cout << "Test of operator<(): p21 < p23 - " << (p21 < p23) << std::endl;
    std::cout << "Test of operator<(): p22 < p23 - " << (p22 < p23) << std::endl;
    std::cout << p21 << std::endl << p22 << std::endl << p23 << std::endl << std::endl;
}

void testBase() {
    Waiter bob = Waiter("Bob Apple", 314L, 5);
    Singer youka = Singer("Shen Zhou", 803L, 5);
    Waiter w_temp;
    Singer s_temp;

    const int NUM = 4;
    Worker * p_work[NUM] = {&bob, &youka, &w_temp, &s_temp};
    // ���� w_temp �� s_temp
    for (int i = 2; i < NUM; i++) {
        p_work[i]->set();
    }
    // չʾ������Ϣ
    for (int i = 0; i < NUM; i++) {
        p_work[i]->show();
        std::cout << std::endl;
    }
}

void testMultipleInheritance() {
    const int SIZE = 5;
    Worker * arr[SIZE];
    // ������˵���Ϣ
    int num;
    for (num = 0; num < SIZE; ++num) {
        char choice;
        std::cout << "Input Employee category:\n"
                  << "w: waiter, s: singer, t: singing waiter, q: quit\n";
        std::cin >> choice;
        while (std::strchr("wstq", choice) == NULL) {
//        while (choice != 'w' || choice != 's' || choice != 't' || choice != 'q') {
            std::cout << "Please enter w,s,t,q: " << std::endl;
            std::cin >> choice;
        }
        if (choice == 'q')
            break;
        switch (choice) {
            case 'w':
                arr[num] = new Waiter();
                break;
            case 's':
                arr[num] = new Singer();
                break;
            case 't':
                arr[num] = new SingingWaiter();
                break;
        }
        std::cin.get();
        arr[num]->set();
    }
    // չʾ���˵���Ϣ
    std::cout << "Show employee information: \n";
    for (int i = 0; i < num; ++i) {
        arr[i]->show();
        std::cout << std::endl;
    }
    for (int i = 0; i < num; ++i) {
        delete arr[i];
    }
    std::cout << "End.\n";
}

void testClassTemplate() {
    StackV1<std::string> st; // ������Stack<std::string>::StackV1()�����ɿյ�Stack
    std::cout << "StackV1 is Empty? " << (st.isEmpty() ? "True" : "False") << std::endl;
    std::string str[10] = {"YouKa", "MoRu", "XuShang", "YiFei", "ZiFeng",
                       "ZiCheng", "MiBin", "HeMing", "SaiHei", "DaLing"};
    for (int i = 0; i < 10; ++i) {
        st.push(str[i]);
    }
    std::cout << "StackV1 is Full? " << (st.isFull() ? "True" : "False") << std::endl;
    std::cout << "StackV1 add a string: " << (st.push("world") ? "True" : "False") << std::endl;
    std::string temp;
    for (int i = 0; i < 10; ++i) {
        std::cout << "StackV1 remove top string: " << (st.pop(temp) ? "True" : "False") << ". String is " << temp << std::endl;
    }
    std::cout << (st.pop(temp) ? "True" : "False") << std::endl;
    std::string input;
    std::cout << "Please input a string to add it to StackV1:";
    std::cin >> input;
    std::cout << "StackV1 add string: " << (st.push(input) ? "True" : "False") << ". " << input << std::endl;
}

void testErrPointStack1() {
    StackV1<char *> st; // ������Stack<std::string>::StackV1()�����ɿյ�Stack
    char * input;
    std::cout << "Please input a string to add it to StackV1:";
    std::cin >> input; // ������������ʱ���������Ϊû�д����洢�ַ����Ŀռ�
    std::cout << "StackV1 add string: " << (st.push(input) ? "True" : "False") << ". " << input << std::endl;
    st.pop(input);
}

void testErrPointStack2() {
    StackV1<char *> st; // ������Stack<std::string>::StackV1()�����ɿյ�Stack
    char input[40];
    std::cout << "Please input a string to add it to StackV1:";
    std::cin >> input;
    std::cout << "StackV1 add string: " << (st.push(input) ? "True" : "False") << ". " << input << std::endl;
//    st.pop(input);// �������鲻�ܱ���ֵ
    std::cout << "Please input a string to add it to StackV1:";
    std::cin >> input;
    std::cout << "StackV1 add string: " << (st.push(input) ? "True" : "False") << ". " << input << std::endl;
    char * temp;
    st.pop(temp);
    std::cout << "StackV1 pop: " << temp << std::endl;
    st.pop(temp);
    std::cout << "StackV1 pop: " << temp << std::endl;
}

void testErrPointStack3() {
    StackV1<char *> st; // ������Stack<std::string>::StackV1()�����ɿյ�Stack
    char * input = new char[40];
    std::cout << "Please input a string to add it to StackV1:";
    std::cin >> input;
    std::cout << "StackV1 add string: " << (st.push(input) ? "True" : "False") << ". " << input << std::endl;
    std::cout << "Please input a string to add it to StackV1:";
    std::cin >> input;
    std::cout << "StackV1 add string: " << (st.push(input) ? "True" : "False") << ". " << input << std::endl;
    st.pop(input);
    std::cout << "StackV1 pop: " << input << std::endl;
    st.pop(input);
    std::cout << "StackV1 pop: " << input << std::endl;
}

void testArrayTemplate() {
    using std::cout;
    using std::endl;
    Array<int, 10> sum; // ����͵�����
    Array<double, 10> average; // ����ƽ��ֵ������
    Array<Array<int, 5>, 10> arr; // ����Ԫ�صĶ�ά���� arr[10][Unit5]
    
    int i, j;
    for (i = 0; i < 10; ++i) {
        sum[i] = 0;
        for (j = 0; j < 5; j++) {
            // Ϊ����Ԫ�ظ�ֵ
            arr[i][j] = (i + 1) * (j + 1);
            // ����sum����
            sum[i] += arr[i][j];
        }
        average[i] = (double) sum[i] / 10;
    }
    for (i = 0; i < 10; ++i) {
        for (j = 0; j < 5; ++j) {
            cout.width(2);
            cout << arr[i][j] << " ";
        }
        cout << ": sum = ";
        cout.width(3);
        cout << sum[i] << ", average = " << average[i] << endl;
    }
    cout << "Finish.\n";
}

void testPairTemplate() {
    using std::cout;
    using std::endl;
    using std::string;
    Pair<string, int> ratings[4] = {
       Pair<string, int>("The one", 4),
       Pair<string, int>("The two", 5),
       Pair<string, int>("The three", 2),
       Pair<string , int>("XYZ", 190)
    };
    int num = sizeof ratings / sizeof (Pair<string, int>);
    cout << "Rating: Eatery\n";
    for (int i = 0; i < num; ++i) {
        cout << ratings[i].second() << ": "
             << ratings[i].first() << endl;
    }
    ratings[3].first() = "ABC";
    ratings[3].second() = 22;
    cout << ratings[3].second() << ": " << ratings[3].first() << endl;
}

void testMemberTemplate() {
    MemberTemplate<double> guy(3.5, 3);
    std::cout << "T was set to double\n";

    guy.show();
    std::cout << "V was set to T, which is double, the V was set to int\n";

    std::cout << guy.memberFunc(10, 2.3) << std::endl;
    std::cout << "U was set to int\n";

    std::cout << guy.memberFunc(10.0, 2.3) << std::endl;
    std::cout << "U was set to double\n";

    std::cout << "Finished.\n";
}

void testTemplateParam() {
    using std::cout;
    using std::cin;
    using std::endl;

    Crab<StackV2> c1;
    int i[3] = { 50, 25, 60 };
    double d[3] = { 22.48, 33.87, 19.12 };
    for (int j = 0; j < 3; ++j) {
        c1.push(i[j], d[j]);
    }
    int temp_int;
    double temp_double;
    while (c1.pop(temp_int, temp_double))
        cout << temp_int << ", " << temp_double << endl;
    cout << "Finished.\n";
}

void testTemplateFriend1() {
    using std::cout;
    using std::endl;
    cout << "No objects declared now: \n";
    counts(); // ��ӡģ�����������

    Friend1<int> rfi1(7); // ����һ������int���͵�Friend1�����
    cout << "After rfi1 declared: \n";
    counts();

    Friend1<int> rfi2(23);
    cout << "After rfi2 declared: \n";
    counts();

    Friend1<double> rfd1(22.2);
    cout << "After rfd1 declared: \n";
    counts();

    reports(rfi1);
    reports(rfi2);
    reports(rfd1);
    cout << "Finished.\n";
}

void testTemplateFriend2() {
    count<int>();
    Friend2<int> rfi1(10);
    Friend2<int> rfi2(20);
    Friend2<double> rfd1(1.05);
    report(rfi1);
    report(rfi2);
    report(rfd1);
    count<int>();
    count<double>();
}

void testTemplateFriend3() {
    counts<int>();
    Friend3<int> rfi1(10);
    Friend3<int> rfi2(20);
    Friend3<double> rfd1(10.6);
    counts<int>();
    counts<double>();
    std::cout << "rfi1, rfi2: ";
    show(rfi1, rfi2);
    std::cout << "rfd1, rfi2: ";
    show(rfd1, rfi2);
}