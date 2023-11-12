#include "client.h"
#include <cstdlib>
// 错误的构造函数声明, 错误原因在于 size 成员是 const, 可以被初始化, 但不能被赋值
//Queue::Queue(int qsize) {
//    size = qsize;
//    front = rear = nullptr;
//    num = 0;
//}

// 正确的构造函数声明
//Queue::Queue(int qsize) : size(qsize) {
//    front = rear = nullptr;
//    num = 0;
//}

// 成员初始化列表
Queue::Queue(int qsize) : size(qsize), front(nullptr), rear(nullptr), num(0) {}

// 删除队列中剩余的元素
Queue::~Queue() {
    Node * temp;
    while (front != nullptr) {
        temp = front;
        front = front->next;
        delete temp;
        num--;
    }
    rear = nullptr;
}

bool Queue::isEmpty() const {
    return num == 0;
}

bool Queue::isFull() const {
    return num == size;
}

int Queue::getCount() const {
    return num;
}

bool Queue::add(const Item & item) {
    // 队列已满不能添加元素
    if (isFull())
        return false;

    Node * node = new Node;
    node->item = item;
    node->next = nullptr;

    // 如果队列是空的, 不需要连接Node, 只需要将头指针置为添加的元素即可
    if (!num)
        front = node;
    else
        rear->next = node;
    rear = node;
    num++;
    return true;
}

bool Queue::remove(Item & item) {
    // 空队列不能删除元素
    if (!num)
        return false;

    Node * temp = front;
    item = temp->item;

    front = front->next;
    delete temp;
    num--;

    // 如果删除元素之后队列为空，将尾指针置为 null
    if (!num)
        rear = nullptr;
    return true;
}

void Client::set(long at) {
    arrive_time = at;
    process_time = std::rand() % 3 + 1;
}