#ifndef RTTI_H
#define RTTI_H

#include <iostream>

class Grand {
private:
    int hold;
public:
    Grand(int h = 0) : hold(h) { }
    virtual ~Grand() = default;
    virtual void Speak() const { std::cout << "I am a Grand class.\n"; }
    virtual int Value() const { return hold; }
};

class Superb : public Grand {
public:
    Superb(int h = 0) : Grand(h) { }
    virtual ~Superb() = default;
    virtual void Speak() const { std::cout << "I am a Superb class.\n"; }
    virtual void Say() const { std::cout << "I hold the Superb value of " << Value() << "!.\n"; }
};

class Magnificent : public Superb {
private:
    char ch;
public:
    Magnificent(int hold = 0, char c = 'A') : Superb(hold), ch(c) { }
    virtual ~Magnificent() = default;
    virtual void Speak() const { std::cout << "I am a Magnificent class.\n"; }
    virtual void Say() const { std::cout << "I hold the character " << ch << " and the integer " << Value() << "!\n"; }
};

#endif // RTTI_H
