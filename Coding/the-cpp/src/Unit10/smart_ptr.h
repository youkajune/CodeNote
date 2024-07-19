/**
 * ������ʾ��������ָ��ʹ�õ� Report ���ͷ�ļ�
 **/

#ifndef SMART_PTR_H
#define SMART_PTR_H

#include <string>
#include <iostream>
#include <algorithm>

class Report {
private:
    std::string str;
public:
    Report(const std::string s) : str(s) {
        std::cout << "Report object created!\n";
    }

    virtual ~Report() {
        std::cout << "Report object deleted!\n";
    }

    void comment() const {
        std::cout << str << std::endl;
    }
};


/**
 * ��ʾ auto_ptr��unique_ptr��shared_ptr ����������ָ���ʹ��
 **/
void test_stmart_ptr() {
    {
        std::auto_ptr<Report> ps(new Report("using auto_ptr"));
        ps->comment();
    }
    {
        std::unique_ptr<Report> ps(new Report("using unique_ptr"));
        ps->comment();
    }
    {
        std::shared_ptr<Report> ps(new Report("using shared_ptr"));
        ps->comment();
    }
}

/**
 * ��ʾһ�������� auto_ptr ������
 **/
void test_no_auto_ptr() {
    std::auto_ptr<std::string> films[5] = {
            std::auto_ptr<std::string>(new std::string("Fowl Balls")),
            std::auto_ptr<std::string>(new std::string("Duck Walks")),
            std::auto_ptr<std::string>(new std::string("Chicken Runs")),
            std::auto_ptr<std::string>(new std::string("Turkey Errors")),
            std::auto_ptr<std::string>(new std::string("Goose Eggs"))
    };
    std::auto_ptr<std::string> pwin; // #1
    pwin = films[2]; // films[2] ��ʧ����Ȩ

    std::cout << "The nominees for best avian baseball film are\n";
    for (int i = 0; i < 5; ++i) {
        std::cout << *films[i] << std::endl; // ���� films[2] ��������Ϊ #1 ���ʹ�� films[2] ��ʧ���������Ȩ
    }
    std::cout << "The winner is " << *pwin << "!\n";
    std::cin.get();
}

std::unique_ptr<int> make_int(int n) {
    return std::unique_ptr<int>(new int(n));
}

void show(std::unique_ptr<int> & pi) { // ע���������Ҫ������
    std::cout << *pi << ' ';
}

/**
 * ��ʾһ�� unique_ptr ����ȷʹ��
 **/
void test_unique_ptr() {
    int size = 10;
    srand(time(0));
    std::vector<std::unique_ptr<int>> vp(size);

    for (int i = 0; i < vp.size(); ++i) {
        vp[i] = make_int(rand()%100);
    }

    vp.push_back(make_int(rand()%100));
    std::for_each(vp.begin(), vp.end(), show); // for_each() in header file <algorithm>
}

#endif // SMART_PTR_H
