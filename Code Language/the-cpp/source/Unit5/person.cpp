#include "person.h"

Person::Person(const std::string str, long id) {
    name = str;
    this->authenciation_id = id;
}

Person::~Person() {
    std::cout << name << " destructor." << std::endl;
}

void Person::doSomeThings() const {
    std::cout << name << " do some things.\n";
}

void Person::walk() const {
    std::cout << name << " walk.\n";
}

const std::string & Person::getName() const {
    return name;
}

std::string & Person::getName() {
    return name;
}

// 错误的构造函数
//Student::Student(const std::string name, long id, const std::string col, long s_id) {
//    Person(name, id);
//    college = col;
//    stu_id = s_id;
//}

// 正确的构造函数
Student::Student(std::string name, long id, std::string col, long s_id) : Person(name, id), college(col), stu_id(s_id) {}

Student::Student(const Person & person, std::string col, long s_id) : Person(person){
    college = col;
    stu_id = s_id;
}

Student::~Student() {
    std::cout << getName() << " destructor.\n";
}

void Student::study() const {
    std::cout << getName() << " study in " << college << std::endl;
}