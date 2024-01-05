#ifndef FILERANDOMIO_H
#define FILERANDOMIO_H

#include <iomanip>

const int NAME_LEN = 20;

struct plant {
    char name[NAME_LEN]; // 行星名字
    double weight; // 行星质量
    double g; // 重力加速度
};

/**
 * 简单演示二进制读写，以及 fstream 对象仅有一个文件指针
 **/
int test_file_random_io_simple() {
    std::fstream finout;
    std::string fileName = "RandomReadAndWriteFile.txt";
    finout.open(fileName, std::ios_base::in | std::ios_base::out | std::ios_base::binary);
    if (!finout.is_open()) {
        std::cerr << "Open file failed.\n" << std::endl;
        exit(EXIT_FAILURE);
    }
    plant p1 = { "Neptune", 1.0241, 11.15 };
    finout.write((char *) &p1, sizeof p1);
    std::cout << "Input point: " << finout.tellg() << ", Output point: " << finout.tellp() << std::endl;

    finout.seekg(0);
    plant p2;
    finout.read((char *) &p2, sizeof p2);
    std::cout << p2.name << " " << p2.weight << " " << p2.g << std::endl;
    finout.close();
    return 0;
}

/** 为随机读写程序准备初始数据 */
void test_init_data() {
    using namespace std;
    int n = 0;
    plant pl;
    fstream finout("PlantsRecord.txt", ios_base::in | ios_base::out | ios_base::binary);
    plant pl1 = {"Mercury", 3.3011, 3.70};
    plant pl2 = {"Venus", 48.675, 8.87};
    plant pl3 = {"Earth", 59.7237, 9.798};
    plant pl4 = {"Mars", 6.4171, 3.71};
    plant pl5 = {"Jupiter", 18982, 24.79};
    plant pl6 = {"Saturn", 5683.4, 10.44};
    plant pl7 = {"Uranus", 868.1, 8.87};
    plant pl8 = {"Neptune", 1024.1, 11.15};

    finout.write((char *) &pl1, sizeof pl);
    finout.write((char *) &pl2, sizeof pl);
    finout.write((char *) &pl3, sizeof pl);
    finout.write((char *) &pl4, sizeof pl);
    finout.write((char *) &pl5, sizeof pl);
    finout.write((char *) &pl6, sizeof pl);
    finout.write((char *) &pl7, sizeof pl);
    finout.write((char *) &pl8, sizeof pl);
    finout.close();
}

// 去除控制台输入中的多余的字符
inline void eatline() { while(std::cin.get() != '\n') continue; }
const char * file = "PlantsRecord.txt";

int test_file_random_io() {
    using namespace std;

    plant pl; // 用于读取、修改、写入记录
    fstream finout(file, ios_base::in | ios_base::out | ios_base::binary);

    /** 在操作之前，先展示文件已有内容，也是供用户查看，选择需要修改的记录 */
    int pn; // plant 记录数量
    if (!finout.is_open()) {
        cerr << file << " can not be opened.\n";
        exit(EXIT_FAILURE);
    }

    cout << "Here are the current contents of the \"" << file << "\" file:\n";
    finout.seekg(0); // 将文件指针重置为开头
    // 循环读取文件中的记录，并输出到控制台上
    while (finout.read((char *) &pl, sizeof pl)) {
        // 文件指针随读取自动移动
        cout << pn++ << ": " << setw(NAME_LEN) << pl.name
             << setprecision(0) << setw(12) << pl.weight
             << setprecision(2) << setw(6) << pl.g << endl;
    }
    if (finout.eof())
        finout.clear(); // 清除 eof flag，方便后续使用
    else {
        cerr << "Error in reading " << file << ".\n"; // 其他读取错误
        exit(EXIT_FAILURE);
    }

    /** 指定需要修改的记录 */
    cout << "Enter the record number you wish to change: ";
    long rec;
    cin >> rec; // 用户输入指定需要修改的记录
    eatline(); // 清除剩余字符
    if (rec < 0 || rec >= pn) {
        cerr << "Invalid record number. Bye!\n";
        exit(EXIT_FAILURE);
    }
    streampos place = rec * sizeof pl; // 定位指定记录的位置
    finout.seekg(place); // 移动文件指针到指定位置
    if (finout.fail()) {
        cerr << "Error on attempted seek.\n"; // 查询时发送错误
        exit(EXIT_FAILURE);
    }
    finout.read((char *) &pl, sizeof pl); // 将记录读取出来
    // 将用户指定的记录显示于控制台上
    cout << "Your selection:\n";
    cout << rec << ": " << setw(NAME_LEN) << pl.name
         << setprecision(0) << setw(12) << pl.weight
         << setprecision(2) << setw(6) << pl.g << endl;

    /** 与用户互动，问询修改后的数据应是什么 */
    cout << "Enter plant name: ";
    cin.get(pl.name, NAME_LEN);
    eatline();
    cout << "Enter planetary weight: ";
    cin >> pl.weight;
    cout << "Enter planet's acceleration of gravity: ";
    cin >> pl.g;
    eatline();

    /** 将数据写回文件 */
    finout.seekp(place); // 将指针移回记录位置
    finout.write((char *) &pl, sizeof pl) << flush; // 将数据写回文件，并刷新输出流
    if (finout.fail()) {
        cerr << "Error on attempted write.\n"; // 写文件时发送错误
        exit(EXIT_FAILURE);
    }

    /** 再次将文件数据展示出来 */
    cout << "Here are the current contents of the \"" << file << "\" file:\n";
    pn = 0;
    finout.seekg(0); // 将文件指针移回开头
    while (finout.read((char *) &pl, sizeof pl)) {
        cout << pn++ << ": " << setw(NAME_LEN) << pl.name
             << setprecision(0) << setw(12) << pl.weight
             << setprecision(2) << setw(6) << pl.g << endl;
    }
    finout.close();
    cout << "Done.\n";
    return 0;
}

#endif // FILERANDOMIO_H