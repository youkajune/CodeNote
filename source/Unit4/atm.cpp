#include "client.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
const int MIN_PER_HOURS = 60;

// 在循环中判断当前循环是否有新顾客到来
bool isNewClient(double x) {
    return x * std::rand() / RAND_MAX < 1;
}

int main(int args, char* arg[]) {
    int queue_size, hours;
    double perhour;
    std::cout << "Please input maximum size of Queue:\n";
    std::cin >> queue_size;
    std::cout << "Please input number of simulation hours:\n";
    std::cin >> hours;
    std::cout << "Please input average number of client per hour:\n";
    std::cin >> perhour;

    int cycle = hours * MIN_PER_HOURS; // 循环的轮次, 一轮等于一分钟
    double min_per_client = 1.0 * MIN_PER_HOURS / perhour; // 平均每个顾客到达的时间


    Queue queue(queue_size); // 创建队列
    Item temp; // 临时对象
    long turnaways = 0; // 由于队列满了被拒绝的人数
    long clients = 0; // 记录排队的顾客总数目
    long served = 0; // 模拟期间的服务次数
    long sum_queue = 0; // 累积长度
    long wait_time = 0; // 顾客处理时间
    long queue_wait = 0; // 顾客总的等待时间

    for(int i = 0; i < cycle; i++) {
        if(isNewClient(min_per_client)) {
            // 本轮循环有新顾客到来
            if(queue.isFull()) {
                // 此时队列是满的, 将拒绝该顾客
                turnaways++;
            } else {
                // 此时队列没有满, 顾客入队
                clients++;
                temp.set(i);
                queue.add(temp);
            }
        }
        if (wait_time <= 0 && !queue.isEmpty()) {
            // 当前顾客处理完毕, 从队列中选取下一个服务的顾客
            queue.remove(temp);
            wait_time = temp.get_process_time();
            queue_wait += i - temp.get_arrive_time(); // 已经服务完的顾客总的等待时间需要加上最新被选中的顾客等待的时间
            served++; // ATM 服务顾客的次数加 Unit1
        }
        if (wait_time > 0)
            wait_time--;
        sum_queue += queue.getCount();
    }

    // 展示统计的信息
    if (clients > 0) {
        std::cout << clients << " clients arrived.\n";
        std::cout << served << " clients use ATM.\n";
        std::cout << turnaways << " clients leave.\n";
        std::cout << "Queue average size is " << (double) sum_queue / cycle << std::endl;
        std::cout << "Client average wait time is " << (double) queue_wait / served << std::endl;
    } else
        std::cout << "No clients.\n";
    std::cout << "Finished.\n";
    return 0;
}