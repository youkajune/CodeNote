#ifndef ANIMAL_H_
#define ANIMAL_H_
#include <iostream>
class Person {
private:
    std::string name;
    long authenciation_id;
public:
    Person(const std::string str, long id);
    ~Person();
    void doSomeThings() const;
    void walk() const;
    const std::string & getName() const;
    std::string & getName();
};

class Student:public Person {
private:
    long stu_id; // 学号
    std::string college; // 学院
public:
    Student(const std::string name, long id, const std::string col, long s_id);
    Student(const Person & person, std::string col, long s_id);
    ~Student();
    void study() const;
};
#endif // ANIMAL_H_