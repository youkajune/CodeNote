#ifndef CLIENT_H_
#define CLIENT_H_
typedef class Client {
private:
    long arrive_time;// 顾客到达时间
    int process_time;// 顾客处理时间
public:
    Client() { arrive_time = process_time = 0; }
    Client(long at, int pt) { arrive_time = at; process_time = pt; }

    void set(long at); // 设置顾客到达时间以及处理时间
    long get_arrive_time() const { return arrive_time; };
    int get_process_time() const { return process_time; };
} Item;

class Queue {
    struct Node {
        Item item;
        Node * next;
    };
    enum {SIZE = 10}; // 队列的项目数

private:
    Node * front; // 头指针
    Node * rear; // 尾指针
    int num; // 队列中元素的数目
    const int size; // 队列中最大可以有多少元素

public:
    Queue(int qsize = SIZE);
    ~Queue();
    bool isEmpty() const; // 队列是否为空
    bool isFull() const; // 队列是否为满
    int getCount() const; // 获取队列中元素数目
    bool add(const Item &); // 往队列中添加元素
    bool remove(Item &); // 从队列中删除元素

private:
    Queue(const Queue & q) : size(q.size) {}
    Queue & operator=(const Queue & q) { return *this;}
};
#endif // CLIENT_H_